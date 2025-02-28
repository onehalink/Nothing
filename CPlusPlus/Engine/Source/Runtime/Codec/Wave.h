#pragma once

// Encode/Decode uncompressed wave file(with extension ".wav")

#include "../Asset/AudioClip.h"



namespace Engine
{
	struct ENGINE_API Wave
	{
		static Bool IsValid(const Void* buffer, SizeType byteCount);

		static Span<Byte> Encode(const AudioClip& audioClip);
		static AudioClip Decode(const Void* buffer, SizeType byteCount);
	};
}