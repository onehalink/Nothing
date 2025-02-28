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

			if ( !MemoryOp::Equal( descriptor->ID, "RIFF", 4 ) )
				return false;

			if ( byteCount != descriptor->size + 8 )
				return false;

			if ( !MemoryOp::Equal( descriptor->format, "WAVE", 4 ) )
				return false;
		}

		{
			auto descriptor = reinterpret_cast<const FormatBlock*>( reinterpret_cast<const Byte*>(buffer) + RIFFHeaderSize );

			if ( !MemoryOp::Equal( descriptor->ID, "fmt ", 4 ) )
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
		Memory<Byte> ret(totalSize);
		{
			MemoryOp::Copy(
				audioClip.storage.GetBuffer(),
				ret.GetBuffer() + DefaultAudioTrackOffset,
				audioClip.storage.GetCount()
			);

			{
				auto descriptor		= reinterpret_cast<RIFFHeader*>( ret.GetBuffer() );
				descriptor->size	= totalSize - 8;

				MemoryOp::Copy( "RIFF", descriptor->ID, 4 );
				MemoryOp::Copy( "WAVE", descriptor->format, 4 );
			}

			{
				auto descriptor						= reinterpret_cast<FormatBlock*>( ret.GetBuffer() + RIFFHeaderSize );
				descriptor->size					= FormatBlockSize - 8;
				descriptor->formatTag				= GetFormatTag( audioClip.type );
				descriptor->channelCount			= audioClip.channelCount;
				descriptor->samplesPerSecond		= audioClip.sampleRate;
				descriptor->averageBytesPerSecond	= audioClip.sampleRate * audioClip.audioFrameSize;
				descriptor->blockAlign				= audioClip.audioFrameSize;
				descriptor->bitsPerSample			= AudioClip::GetBitDepth( audioClip.type );

				MemoryOp::Copy( "fmt ", descriptor->ID, 4 );
			}

			{
				auto descriptor		= reinterpret_cast<DataBlock*>( ret.GetBuffer() + RIFFHeaderSize + FormatBlockSize );
				descriptor->size	= audioClip.storage.GetCount();

				MemoryOp::Copy( "data", descriptor->ID, 4 );
			}
		}

		return ret;
	}

	AudioClip Wave::Decode(const Void* buffer, SizeType byteCount)
	{
		auto formatBlock = reinterpret_cast<const FormatBlock*>( reinterpret_cast<const Byte*>(buffer) + RIFFHeaderSize );

		const DataBlock* dataBlock	= nullptr;
		SizeType offset				= RIFFHeaderSize + ( formatBlock->size + 8 );

		while ( DataBlockSize + offset <= byteCount )
		{
			dataBlock = reinterpret_cast<const DataBlock*>( reinterpret_cast<const Byte*>(buffer) + offset );
			if ( MemoryOp::Equal( dataBlock->ID, "data", 4 ) )
				break;

			offset += DataBlockSize + dataBlock->size;
		}

		{
			AudioClip ret( GetDataStoreType( formatBlock->formatTag, formatBlock->bitsPerSample ), dataBlock->size, formatBlock->samplesPerSecond, formatBlock->channelCount );
			MemoryOp::Copy( dataBlock + 1, ret.storage.GetBuffer(), dataBlock->size );

			return ret;
		}
	}
}