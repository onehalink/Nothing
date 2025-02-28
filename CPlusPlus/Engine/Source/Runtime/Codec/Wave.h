#pragma once

// Encode/Decode uncompressed wave file(with extension ".wav")

#include "../Asset/AudioClip.h"



namespace Engine
{
	struct ENGINE_API Wave
	{
		static constexpr SizeType FormatTag_PCM			= 1;
		static constexpr SizeType FormatTag_IEEE_Float	= 3;


		static SizeType GetFormatTag(AudioClip::DataStoreType type);
		static AudioClip::DataStoreType GetDataStoreType(SizeType formatTag, SizeType bitDepth);


		static Bool IsValid(const Void* buffer, SizeType byteCount);

		static Memory<Byte> Encode(const AudioClip& audioClip);
		static AudioClip Decode(const Void* buffer, SizeType byteCount);
	};
}