#include "Engine.h"



using namespace Engine;
using namespace Engine::FileSystem;
using namespace Engine::Windows;


int main()
{
	AudioClip audioClip;
	if (auto selected = FileDialog::Open({ InPlace(), "*.wav" }, Path::GetFullQualifiedPathName("."), "Open audio file"))
	{
		auto loaded = File::ReadAllBytes(selected.Value());
		audioClip = Wave::Decode(loaded.GetBuffer(), loaded.GetCount());
	}
	else
		return -1;

	const SizeType ASecond = audioClip.audioFrameSize * audioClip.sampleRate;
	const SizeType SoundBufferSize = ASecond / 4;
	const SizeType HalfSoundBufferSize = SoundBufferSize / 2;

	DirectSound ds(
		nullptr,
		SoundBufferSize,
		Wave::GetFormatTag(audioClip.type),
		audioClip.channelCount,
		audioClip.sampleRate,
		AudioClip::GetBitDepth(audioClip.type)
	);

	ds.Fill(audioClip.storage.GetBuffer(), SoundBufferSize);
	SizeType offset = SoundBufferSize;

	ds.Play();

	while (true)
	{
		SizeType writable = ds.CalculatedWritableBufferSize();
		if (writable > HalfSoundBufferSize)
		{
			SizeType readable = audioClip.storage.GetCount() - offset;
			if (writable > readable)
				writable = readable;

			ds.Fill(audioClip.storage.GetBuffer() + offset, writable);
			offset += writable;

			if (offset == audioClip.storage.GetCount())
				offset = 0;
		}
	}

	return 0;
}