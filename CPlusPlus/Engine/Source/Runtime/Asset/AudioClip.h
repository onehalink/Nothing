#pragma once

#include "../Core.h"



namespace Engine
{
	struct ENGINE_API AudioClip
	{
		enum class DataStoreType
		{
			UInt8,
			Int16,
			Int32,
			Float32,
		};


		Span<Byte> storage;

		DataStoreType type;

		SizeType channelCount;
		SizeType bitDepth;		// how many bits used by a L/R audio frame
		SizeType sampleRate;	// how many samples used in a second
		SizeType audioFrameSize;


		AudioClip();
		AudioClip(SizeType preallocated /** in bytes */, DataStoreType type, SizeType channelCount, SizeType sampleRate);
		AudioClip(const AudioClip& other);
		AudioClip(AudioClip&& other);
		~AudioClip();
		

		Void SetAudioFrame(SizeType index, const Void* audioFrame);
		const Void* GetAudioFrame(SizeType index) const;

		RealType Duration() const;


		AudioClip& operator=(const AudioClip& other);
		AudioClip& operator=(AudioClip&& other);

		Void* operator[](SizeType index);
		const Void* operator[](SizeType index) const;
	private:
		Void CopyFrom(const AudioClip& other);
	};
}