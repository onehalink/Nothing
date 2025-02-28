#pragma once

#include "../../Core.h"



namespace Engine::Windows
{
	class ENGINE_API DirectSound
	{
	public:
		NONCOPYABLE(DirectSound);
		DirectSound(Void* windowHandle, SizeType requiredSoundBufferSize, SizeType waveFormatTag, SizeType channelCount, SizeType samplesPerSecond, SizeType bitsPerSample);
		~DirectSound();



		Void Fill(const Void* buffer, SizeType byteCount);

		Void Play();
		Void Stop();
		Void SetVolumn(RealType volumn);


		SizeType CalculatedWritableBufferSize() const;
	private:
		Void* sound;
		Void* soundBuffer;

		SizeType requiredSoundBufferSize;
		SizeType writePosition;
	};
}