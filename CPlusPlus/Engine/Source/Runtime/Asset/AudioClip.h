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


		Memory<Byte>	storage;
		DataStoreType	type;

		SizeType sampleRate; // how many samples used in a second
		SizeType channelCount;
		SizeType audioFrameSize;


		AudioClip();
		AudioClip(DataStoreType type, SizeType preallocatedSize /** in bytes */, SizeType sampleRate, SizeType channelCount);
		AudioClip(const AudioClip& other);
		AudioClip(AudioClip&& other);
		~AudioClip();
		

		Void SetAudioFrame(SizeType index, const Void* audioFrame);
		const Void* GetAudioFrame(SizeType index) const;

		AudioClip ConvertDataStoreType(DataStoreType specific) const;


		RealType Duration() const;
		SizeType Samples() const;


		static SizeType GetBitDepth(DataStoreType type);


		AudioClip& operator=(const AudioClip& other);
		AudioClip& operator=(AudioClip&& other);

		Void* operator[](SizeType index);
		const Void* operator[](SizeType index) const;
	private:
		Void CopyFrom(const AudioClip& other);
		Void SwapWith(AudioClip& other);
	};
}