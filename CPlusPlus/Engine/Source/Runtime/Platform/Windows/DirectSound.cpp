#include "DirectSound.h"

#include "Windows.h"

#include <dsound.h>
#pragma comment(lib, "dsound")



namespace Engine::Windows
{
	DirectSound::DirectSound(Void* windowHandle, SizeType requiredSoundBufferSize, SizeType waveFormatTag, SizeType channelCount, SizeType samplesPerSecond, SizeType bitsPerSample)
	{
		if ( !windowHandle )
			windowHandle = GetDesktopWindow();

		IDirectSound* sound = nullptr;
		{
			DirectSoundCreate( nullptr, &sound, nullptr );
			ASSERT( sound, "Invalid parameter" );

			sound->SetCooperativeLevel( reinterpret_cast<HWND>(windowHandle), DSSCL_NORMAL );
		}

		IDirectSoundBuffer* soundBuffer = nullptr;
		{
			const SizeType AudioFrameSize = bitsPerSample / 8 * channelCount;

			WAVEFORMATEX format;
			MemoryClear( &format, sizeof(format) );
			format.wFormatTag		= waveFormatTag;
			format.nChannels		= channelCount;
			format.nSamplesPerSec	= samplesPerSecond;
			format.nAvgBytesPerSec	= AudioFrameSize * samplesPerSecond;
			format.nBlockAlign		= AudioFrameSize;
			format.wBitsPerSample	= bitsPerSample;

			DSBUFFERDESC descriptor;
			MemoryClear( &descriptor, sizeof(descriptor) );
			descriptor.dwSize			= sizeof(DSBUFFERDESC);
			descriptor.dwFlags			= DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLVOLUME;
			descriptor.dwBufferBytes	= requiredSoundBufferSize;
			descriptor.lpwfxFormat		= &format;

			sound->CreateSoundBuffer( &descriptor, &soundBuffer, nullptr );
			ASSERT( sound, "Invalid parameter" );
		}

		this->sound							= sound;
		this->soundBuffer					= soundBuffer;
		this->requiredSoundBufferSize		= requiredSoundBufferSize;
		this->writePosition					= 0;
	}

	DirectSound::~DirectSound()
	{
		auto sound			= reinterpret_cast<IDirectSound*>( this->sound );
		auto soundBuffer	= reinterpret_cast<IDirectSoundBuffer*>( this->soundBuffer );

		if (sound)
			sound->Release();

		if (soundBuffer)
			soundBuffer->Release();
	}

	Void DirectSound::Fill(const Void* buffer, SizeType byteCount)
	{
		if ( byteCount > requiredSoundBufferSize )
			return;

		auto soundBuffer = reinterpret_cast<IDirectSoundBuffer*>( this->soundBuffer );

		DWORD writableBufferSize;

		{
			writableBufferSize = requiredSoundBufferSize - writePosition;
			if ( writableBufferSize > byteCount )
				writableBufferSize = byteCount;

			{
				Void* lockedBuffer;
				DWORD lockedBufferSize;

				soundBuffer->Lock(
					writePosition,
					writableBufferSize,
					&lockedBuffer,
					&lockedBufferSize,
					nullptr,
					nullptr,
					0
				);

				MemoryCopy(buffer, lockedBuffer, lockedBufferSize);

				soundBuffer->Unlock(
					lockedBuffer,
					lockedBufferSize,
					nullptr,
					0
				);
			}

			writePosition += writableBufferSize;
			if ( writePosition == requiredSoundBufferSize )
				writePosition = 0;

			byteCount -= writableBufferSize;
		}

		if ( byteCount != 0 )
		{
			buffer				= reinterpret_cast<const Byte*>(buffer) + writableBufferSize;
			writableBufferSize	= byteCount;

			{
				Void* lockedBuffer;
				DWORD lockedBufferSize;

				soundBuffer->Lock(
					writePosition,
					writableBufferSize,
					&lockedBuffer,
					&lockedBufferSize,
					nullptr,
					nullptr,
					0
				);

				MemoryCopy(buffer, lockedBuffer, lockedBufferSize);

				soundBuffer->Unlock(
					lockedBuffer,
					lockedBufferSize,
					nullptr,
					0
				);
			}

			writePosition += writableBufferSize;
		}
	}

	Void DirectSound::Play()
	{
		reinterpret_cast<IDirectSoundBuffer*>(soundBuffer)->Play( 0, 0, DSBPLAY_LOOPING );
	}

	Void DirectSound::Stop()
	{
		reinterpret_cast<IDirectSoundBuffer*>(soundBuffer)->Stop();
	}

	Void DirectSound::SetVolumn(RealType volumn)
	{
		// todo..
	}

	SizeType DirectSound::CalculatedWritableBufferSize() const
	{
		auto soundBuffer = reinterpret_cast<IDirectSoundBuffer*>( this->soundBuffer );

		DWORD readCursor;
		DWORD writeCursor;
		soundBuffer->GetCurrentPosition(
			&readCursor,
			&writeCursor
		);

		if ( writePosition > readCursor )
			return requiredSoundBufferSize - ( writePosition - readCursor );
	
		return readCursor - writePosition;
	}
}