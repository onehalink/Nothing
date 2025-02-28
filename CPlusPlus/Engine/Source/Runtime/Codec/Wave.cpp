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


	enum FormatTag
	{
		FormatTag_PCM			= 1,
		FormatTag_IEEE_Float	= 3,
	};


	static constexpr SizeType RIFFHeaderSize			= sizeof(RIFFHeader);
	static constexpr SizeType FormatBlockSize			= sizeof(FormatBlock);
	static constexpr SizeType DataBlockSize				= sizeof(DataBlock);
	static constexpr SizeType DefaultAudioTrackOffset	= RIFFHeaderSize + FormatBlockSize + DataBlockSize;


	Bool Wave::IsValid(const Void* buffer, SizeType byteCount)
	{
		if ( byteCount < DefaultAudioTrackOffset )
			return false;

		{
			auto descriptor = reinterpret_cast<const RIFFHeader*>(buffer);

			if ( !Memory::Equal( descriptor->ID, "RIFF", 4 ) )
				return false;

			if ( byteCount != descriptor->size + 8 )
				return false;

			if ( !Memory::Equal( descriptor->format, "WAVE", 4 ) )
				return false;
		}

		{
			auto descriptor = reinterpret_cast<const FormatBlock*>( reinterpret_cast<const Byte*>(buffer) + RIFFHeaderSize );

			if ( !Memory::Equal( descriptor->ID, "fmt ", 4 ) )
				return false;

			if (
				descriptor->formatTag != FormatTag_PCM &&
				descriptor->formatTag != FormatTag_IEEE_Float
				)
				return false;
		}

		return true;
	}

	Span<Byte> Wave::Encode(const AudioClip& audioClip)
	{
		SizeType totalSize = audioClip.storage.GetCount() + DefaultAudioTrackOffset;
		Span<Byte> ret(totalSize);
		{
			Memory::Copy(
				audioClip.storage.GetBuffer(),
				ret.GetBuffer() + DefaultAudioTrackOffset,
				audioClip.storage.GetCount()
			);

			{
				auto descriptor		= reinterpret_cast<RIFFHeader*>( ret.GetBuffer() );
				descriptor->size	= totalSize - 8;

				Memory::Copy( "RIFF", descriptor->ID, 4 );
				Memory::Copy( "WAVE", descriptor->format, 4 );
			}

			{
				using DataStoreType	= AudioClip::DataStoreType;


				UInt16 formatTag;
				switch (audioClip.type)
				{
				case DataStoreType::UInt8:
				case DataStoreType::Int16:
				case DataStoreType::Int32:
					formatTag = FormatTag_PCM;
					break;
				case DataStoreType::Float32:
					formatTag = FormatTag_IEEE_Float;
					break;
				}

				auto descriptor						= reinterpret_cast<FormatBlock*>( ret.GetBuffer() + RIFFHeaderSize );
				descriptor->size					= FormatBlockSize - 8;
				descriptor->formatTag				= formatTag;
				descriptor->channelCount			= audioClip.channelCount;
				descriptor->samplesPerSecond		= audioClip.sampleRate;
				descriptor->averageBytesPerSecond	= audioClip.sampleRate * audioClip.audioFrameSize;
				descriptor->blockAlign				= audioClip.audioFrameSize;
				descriptor->bitsPerSample			= audioClip.bitDepth;

				Memory::Copy( "fmt ", descriptor->ID, 4 );
			}

			{
				auto descriptor		= reinterpret_cast<DataBlock*>( ret.GetBuffer() + RIFFHeaderSize + FormatBlockSize );
				descriptor->size	= audioClip.storage.GetCount();

				Memory::Copy( "data", descriptor->ID, 4 );
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
			if ( Memory::Equal( dataBlock->ID, "data", 4 ) )
				break;

			offset += DataBlockSize + dataBlock->size;
		}

		{
			using DataStoreType = AudioClip::DataStoreType;


			DataStoreType type;
			switch ( formatBlock->formatTag )
			{
			case FormatTag_PCM:
				switch ( formatBlock->bitsPerSample )
				{
				case  8: type = DataStoreType::UInt8; break;
				case 16: type = DataStoreType::Int16; break;
				case 32: type = DataStoreType::Int32; break;
				}
				break;
			case FormatTag_IEEE_Float:
				type = DataStoreType::Float32;
				break;
			}

			AudioClip ret( dataBlock->size, type, formatBlock->channelCount, formatBlock->samplesPerSecond );
			Memory::Copy( dataBlock + 1, ret.storage.GetBuffer(), dataBlock->size );

			return ret;
		}
	}
}