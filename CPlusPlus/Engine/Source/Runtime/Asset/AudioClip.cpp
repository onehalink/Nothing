#include "AudioClip.h"



namespace Engine
{
	AudioClip::AudioClip()
	{
		Memory::Clear( this, sizeof(AudioClip) );
	}

	AudioClip::AudioClip(SizeType preallocated, DataStoreType type, SizeType channelCount, SizeType sampleRate)
	{
		storage = Span<Byte>(preallocated);
		
		switch (type)
		{
		case DataStoreType::UInt8:		bitDepth = 8;	break;
		case DataStoreType::Int16:		bitDepth = 16;	break;
		case DataStoreType::Int32:		bitDepth = 32;	break;
		case DataStoreType::Float32:	bitDepth = 32;	break;
		}

		audioFrameSize = ( bitDepth / 8 ) * channelCount;

		this->type			= type;
		this->channelCount	= channelCount;
		this->sampleRate	= sampleRate;
	}

	AudioClip::AudioClip(const AudioClip& other)
	{
		CopyFrom(other);
	}

	AudioClip::AudioClip(AudioClip&& other)
	{
		storage = Move( other.storage );

		type			= other.type;
		channelCount	= other.channelCount;
		bitDepth		= other.bitDepth;
		sampleRate		= other.sampleRate;
		audioFrameSize	= other.audioFrameSize;
	}

	AudioClip::~AudioClip()
	{

	}

	Void AudioClip::SetAudioFrame(SizeType index, const Void* audioFrame)
	{
		Memory::Copy( audioFrame, ( *this )[index], audioFrameSize );
	}

	const Void* AudioClip::GetAudioFrame(SizeType index) const
	{
		return ( *this )[index];
	}

	RealType AudioClip::Duration() const
	{
		return static_cast<RealType>( storage.GetCount() ) / ( audioFrameSize * sampleRate );
	}

	AudioClip& AudioClip::operator=(const AudioClip& other)
	{
		CopyFrom(other);

		return *this;
	}

	AudioClip& AudioClip::operator=(AudioClip&& other)
	{
		storage = Move( other.storage );

		Swap( &type,			&other.type				);
		Swap( &channelCount,	&other.channelCount		);
		Swap( &bitDepth,		&other.bitDepth			);
		Swap( &sampleRate,		&other.sampleRate		);
		Swap( &audioFrameSize,	&other.audioFrameSize	);

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
		channelCount	= other.channelCount;
		bitDepth		= other.bitDepth;
		sampleRate		= other.sampleRate;
		audioFrameSize	= other.audioFrameSize;
	}
}