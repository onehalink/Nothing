#include "Engine.h"



using namespace Engine;
using namespace Engine::Windows;


int main()
{
	AudioClip audioClip;
	if (auto selected = FileDialog::Open({ InPlace(), "*.wav" }, Path::GetFullQualifiedPathName("../../../Asset/Audio"), "Open audio file"))
	{
		auto loaded = File::ReadAllBytes(selected.Value());
		audioClip = Wave::Decode(loaded.GetBuffer(), loaded.GetCount());
	}
	else
		return -1;

	const SizeType ASecond = audioClip.audioFrameSize * audioClip.sampleRate;
	const SizeType SoundBufferSize = ASecond / 4;
	const SizeType HalfSoundBufferSize = SoundBufferSize / 2;

	DirectSound directSound(
		nullptr,
		SoundBufferSize,
		Wave::GetFormatTag(audioClip.type),
		audioClip.channelCount,
		audioClip.sampleRate,
		AudioClip::GetBitDepth(audioClip.type)
	);

	directSound.Fill(audioClip.storage.GetBuffer(), SoundBufferSize);
	SizeType offset = SoundBufferSize;

	directSound.Play();

	while (true)
	{
		SizeType writeable = directSound.CalculatedWritableBufferSize();
		if (writeable > HalfSoundBufferSize)
		{
			SizeType readable = audioClip.storage.GetCount() - offset;
			if (writeable > readable)
				writeable = readable;

			directSound.Fill(audioClip.storage.GetBuffer() + offset, writeable);
			offset += writeable;

			if (offset == audioClip.storage.GetCount())
				offset = 0;
		}
	}

	return 0;
}