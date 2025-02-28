#include "AudioClip.h"



namespace Engine
{
	AudioClip::AudioClip()
	{
		MemoryOp::Clear(this);
	}

	AudioClip::AudioClip(DataStoreType type, SizeType preallocatedSize, SizeType sampleRate, SizeType channelCount)
	{
		storage = Memory<Byte>(preallocatedSize);

		this->type			= type;
		this->sampleRate	= sampleRate;
		this->channelCount	= channelCount;

		audioFrameSize	= ( GetBitDepth(type) / 8 ) * channelCount;
	}

	AudioClip::AudioClip(const AudioClip& other)
	{
		CopyFrom(other);
	}

	AudioClip::AudioClip(AudioClip&& other)
	{
		SwapWith(other);
	}

	AudioClip::~AudioClip()
	{

	}

	Void AudioClip::SetAudioFrame(SizeType index, const Void* audioFrame)
	{
		MemoryOp::Copy( audioFrame, ( *this )[index], audioFrameSize );
	}

	const Void* AudioClip::GetAudioFrame(SizeType index) const
	{
		return ( *this )[index];
	}

	AudioClip AudioClip::ConvertDataStoreType(DataStoreType specific) const
	{
		Action<Float32*, const Void*> OpA = [](Float32*, const Void*) {};
		switch (type)
		{
		case DataStoreType::UInt8:
			if ( channelCount == 1 )
				OpA = [](Float32* output, const Void* data)
				{
					UInt8 value = *reinterpret_cast<const UInt8*>(data);

					output[0] = static_cast<Float32>(value) / NumericLimit<UInt8>::Maximum * 2 - 1;
				};
			else
				OpA = [](Float32* output, const Void* data)
				{
					UInt8 value0 = reinterpret_cast<const UInt8*>(data)[0];
					UInt8 value1 = reinterpret_cast<const UInt8*>(data)[1];

					output[0] = static_cast<Float32>(value0) / NumericLimit<UInt8>::Maximum * 2 - 1;
					output[1] = static_cast<Float32>(value1) / NumericLimit<UInt8>::Maximum * 2 - 1;
				};
			break;
		case DataStoreType::Int16:
			if ( channelCount == 1 )
				OpA = [](Float32* output, const Void* data)
				{
					Int16 value = *reinterpret_cast<const Int16*>(data);
					Int32 remap = static_cast<Int32>(value) - NumericLimit<Int16>::Minimum;

					output[0] = static_cast<Float32>(remap) / NumericLimit<UInt16>::Maximum * 2 - 1;
				};
			else
				OpA = [](Float32* output, const Void* data)
				{
					Int16 value0 = reinterpret_cast<const Int16*>(data)[0];
					Int16 value1 = reinterpret_cast<const Int16*>(data)[1];
					Int32 remap0 = static_cast<Int32>(value0) - NumericLimit<Int16>::Minimum;
					Int32 remap1 = static_cast<Int32>(value1) - NumericLimit<Int16>::Minimum;

					output[0] = static_cast<Float32>(remap0) / NumericLimit<UInt16>::Maximum * 2 - 1;
					output[1] = static_cast<Float32>(remap1) / NumericLimit<UInt16>::Maximum * 2 - 1;
				};
			break;
		case DataStoreType::Int32:
			if ( channelCount == 1 )
				OpA = [](Float32* output, const Void* data)
				{
					Int32 value = *reinterpret_cast<const Int32*>(data);
					Int64 remap = static_cast<Int64>(value) - NumericLimit<Int32>::Minimum;

					output[0] = static_cast<Float32>(remap) / NumericLimit<UInt32>::Maximum * 2 - 1;
				};
			else
				OpA = [](Float32* output, const Void* data)
				{
					Int32 value0 = reinterpret_cast<const Int32*>(data)[0];
					Int32 value1 = reinterpret_cast<const Int32*>(data)[1];
					Int64 remap0 = static_cast<Int64>(value0) - NumericLimit<Int32>::Minimum;
					Int64 remap1 = static_cast<Int64>(value1) - NumericLimit<Int32>::Minimum;

					output[0] = static_cast<Float32>(remap0) / NumericLimit<UInt32>::Maximum * 2 - 1;
					output[1] = static_cast<Float32>(remap1) / NumericLimit<UInt32>::Maximum * 2 - 1;
				};
			break;
		case DataStoreType::Float32:
			if ( channelCount == 1 )
				OpA = [](Float32* output, const Void* data)
				{
					MemoryOp::Copy( data, output, sizeof(Float32) * 1 );
				};
			else
				OpA = [](Float32* output, const Void* data)
				{
					MemoryOp::Copy( data, output, sizeof(Float32) * 2 );
				};
			break;
		}

		Action<Void*, const Float32*> OpB = [](Void*, const Float32*) {};
		switch (specific)
		{
		case DataStoreType::UInt8:
			if ( channelCount == 1 )
				OpB = [](Void* output, const Float32* data)
				{
					*reinterpret_cast<UInt8*>(output) = ( *data + 1 ) / 2 * NumericLimit<UInt8>::Maximum;
				};
			else
				OpB = [](Void* output, const Float32* data)
				{
					reinterpret_cast<UInt8*>(output)[0] = ( data[0] + 1 ) / 2 * NumericLimit<UInt8>::Maximum;
					reinterpret_cast<UInt8*>(output)[1] = ( data[1] + 1 ) / 2 * NumericLimit<UInt8>::Maximum;
				};
			break;
		case DataStoreType::Int16:
			if ( channelCount == 1 )
				OpB = [](Void* output, const Float32* data)
				{
					*reinterpret_cast<Int16*>(output) = ( *data + 1 ) / 2 * NumericLimit<UInt16>::Maximum + NumericLimit<Int16>::Minimum;
				};
			else
				OpB = [](Void* output, const Float32* data)
				{
					reinterpret_cast<Int16*>(output)[0] = ( data[0] + 1 ) / 2 * NumericLimit<UInt16>::Maximum + NumericLimit<Int16>::Minimum;
					reinterpret_cast<Int16*>(output)[1] = ( data[1] + 1 ) / 2 * NumericLimit<UInt16>::Maximum + NumericLimit<Int16>::Minimum;
				};
			break;
		case DataStoreType::Int32:
			if ( channelCount == 1 )
				OpB = [](Void* output, const Float32* data)
				{
					*reinterpret_cast<Int32*>(output) = ( *data + 1 ) / 2 * NumericLimit<UInt32>::Maximum + NumericLimit<Int32>::Minimum;
				};
			else
				OpB = [](Void* output, const Float32* data)
				{
					reinterpret_cast<Int32*>(output)[0] = ( data[0] + 1 ) / 2 * NumericLimit<UInt32>::Maximum + NumericLimit<Int32>::Minimum;
					reinterpret_cast<Int32*>(output)[1] = ( data[1] + 1 ) / 2 * NumericLimit<UInt32>::Maximum + NumericLimit<Int32>::Minimum;
				};
			break;
		case DataStoreType::Float32:
			if ( channelCount == 1 )
				OpB = [](Void* output, const Float32* data)
				{
					MemoryOp::Copy( data, output, sizeof(Float32) * 1 );
				};
			else
				OpB = [](Void* output, const Float32* data)
				{
					MemoryOp::Copy( data, output, sizeof(Float32) * 2 );
				};
			break;
		}

		SizeType samples = Samples();
		AudioClip ret( specific, samples * ( GetBitDepth(specific) / 8 * channelCount ), sampleRate, channelCount );

		Float32 buffer[2];
		for (SizeType index = 0; index < samples; index++)
		{
			OpA( buffer,		(*this)[index]	);
			OpB( ret[index],	buffer			);
		}

		return ret;
	}

	RealType AudioClip::Duration() const
	{
		return static_cast<RealType>( Samples() ) / sampleRate;
	}

	SizeType AudioClip::Samples() const
	{
		return storage.GetCount() / audioFrameSize;
	}

	SizeType AudioClip::GetBitDepth(DataStoreType type)
	{
		switch (type)
		{
		case DataStoreType::UInt8:		return 8;
		case DataStoreType::Int16:		return 16;
		case DataStoreType::Int32:
		case DataStoreType::Float32:	return 32;
		default: return 0;
		}
	}

	AudioClip& AudioClip::operator=(const AudioClip& other)
	{
		CopyFrom(other);

		return *this;
	}

	AudioClip& AudioClip::operator=(AudioClip&& other)
	{
		SwapWith(other);

		return *this;
	}

	Void* AudioClip::operator[](SizeType index)
	{
		return storage.GetBuffer() + audioFrameSize * index;
	}

	const Void* AudioClip::operator[](SizeType index) const
	{
		return storage.GetBuffer() + audioFrameSize * index;
	}

	Void AudioClip::CopyFrom(const AudioClip& other)
	{
		storage = other.storage;

		type			= other.type;
		sampleRate		= other.sampleRate;
		channelCount	= other.channelCount;
		audioFrameSize	= other.audioFrameSize;
	}

	Void AudioClip::SwapWith(AudioClip& other)
	{
		storage = Move( other.storage );

		Swap( &type,			&other.type				);
		Swap( &sampleRate,		&other.sampleRate		);
		Swap( &channelCount,	&other.channelCount		);
		Swap( &audioFrameSize,	&other.audioFrameSize	);
	}
}