#include "Wave.h"



namespace Engine
{
	struct RIFFHeader
	{
		Byte	ID[4];		// Must be "RIFF"
		UInt32	size;		// The value should be the file size(*.wav) - 8
		Byte	format[4];	// Must be "WAVE"
	};


	struct FormatBlock
	{
		Byte	ID[4];	// Must be "fmt "
		UInt32	size;	// The value should be sizeof(FormatBlock) - 8
		UInt16	formatTag;
		UInt16	channelCount;
		UInt32	samplesPerSecond;
		UInt32	averageBytesPerSecond;
		UInt16	blockAlign;
		UInt16	bitsPerSample;
	};


	struct DataBlock
	{
		Byte	ID[4];	// Must be "data"
		UInt32	size;	// Indicate the size in bytes of the audio track
	};


	static constexpr SizeType RIFFHeaderSize			= sizeof(RIFFHeader);
	static constexpr SizeType FormatBlockSize			= sizeof(FormatBlock);
	static constexpr SizeType DataBlockSize				= sizeof(DataBlock);
	static constexpr SizeType DefaultAudioTrackOffset	= RIFFHeaderSize + FormatBlockSize + DataBlockSize;


	SizeType Wave::GetFormatTag(AudioClip::DataStoreType type)
	{
		return type != AudioClip::DataStoreType::Float32 ? FormatTag_PCM : FormatTag_IEEE_Float;
	}

	AudioClip::DataStoreType Wave::GetDataStoreType(SizeType formatTag, SizeType bitDepth)
	{
		if ( formatTag == FormatTag_PCM )
			switch (bitDepth)
			{
			case  8: return AudioClip::DataStoreType::UInt8;
			case 16: return AudioClip::DataStoreType::Int16;
			case 32: return AudioClip::DataStoreType::Int32;
			}

		return AudioClip::DataStoreType::Float32;
	}

	Bool Wave::IsValid(const Void* buffer, SizeType byteCount)
	{
		if ( byteCount < DefaultAudioTrackOffset )
			return false;

		{
			auto descriptor = reinterpret_cast<const RIFFHeader*>(buffer);

			if ( !MemoryEqual( descriptor->ID, "RIFF", 4 ) )
				return false;

			if ( byteCount != descriptor->size + 8 )
				return false;

			if ( !MemoryEqual( descriptor->format, "WAVE", 4 ) )
				return false;
		}

		{
			auto descriptor = reinterpret_cast<const FormatBlock*>( reinterpret_cast<const Byte*>(buffer) + RIFFHeaderSize );

			if ( !MemoryEqual( descriptor->ID, "fmt ", 4 ) )
				return false;

			if (
				descriptor->formatTag != FormatTag_PCM			&&
				descriptor->formatTag != FormatTag_IEEE_Float
				)
				return false;
		}

		return true;
	}

	Memory<Byte> Wave::Encode(const AudioClip& audioClip)
	{
		SizeType totalSize = audioClip.storage.GetCount() + DefaultAudioTrackOffset;
		Memory<Byte> result(totalSize);
		{
			MemoryCopy(
				audioClip.storage.GetBuffer(),
				result.GetBuffer() + DefaultAudioTrackOffset,
				audioClip.storage.GetCount()
			);

			{
				auto descriptor		= reinterpret_cast<RIFFHeader*>( result.GetBuffer() );
				descriptor->size	= totalSize - 8;

				MemoryCopy( "RIFF", descriptor->ID, 4 );
				MemoryCopy( "WAVE", descriptor->format, 4 );
			}

			{
				auto descriptor						= reinterpret_cast<FormatBlock*>( result.GetBuffer() + RIFFHeaderSize );
				descriptor->size					= FormatBlockSize - 8;
				descriptor->formatTag				= GetFormatTag( audioClip.type );
				descriptor->channelCount			= audioClip.channelCount;
				descriptor->samplesPerSecond		= audioClip.sampleRate;
				descriptor->averageBytesPerSecond	= audioClip.sampleRate * audioClip.audioFrameSize;
				descriptor->blockAlign				= audioClip.audioFrameSize;
				descriptor->bitsPerSample			= AudioClip::GetBitDepth( audioClip.type );

				MemoryCopy( "fmt ", descriptor->ID, 4 );
			}

			{
				auto descriptor		= reinterpret_cast<DataBlock*>( result.GetBuffer() + RIFFHeaderSize + FormatBlockSize );
				descriptor->size	= audioClip.storage.GetCount();

				MemoryCopy( "data", descriptor->ID, 4 );
			}
		}

		return result;
	}

	AudioClip Wave::Decode(const Void* buffer, SizeType byteCount)
	{
		ASSERT( IsValid(buffer, byteCount), "This is not a valid wave file representation" );


		auto formatBlock = reinterpret_cast<const FormatBlock*>( reinterpret_cast<const Byte*>(buffer) + RIFFHeaderSize );

		const DataBlock* dataBlock	= nullptr;
		SizeType offset				= RIFFHeaderSize + ( formatBlock->size + 8 );

		while ( DataBlockSize + offset <= byteCount )
		{
			dataBlock = reinterpret_cast<const DataBlock*>( reinterpret_cast<const Byte*>(buffer) + offset );
			if ( MemoryEqual( dataBlock->ID, "data", 4 ) )
				break;

			offset += DataBlockSize + dataBlock->size;
		}

		{
			AudioClip result( GetDataStoreType( formatBlock->formatTag, formatBlock->bitsPerSample ), dataBlock->size, formatBlock->samplesPerSecond, formatBlock->channelCount );
			MemoryCopy( dataBlock + 1, result.storage.GetBuffer(), dataBlock->size );

			return result;
		}
	}
}