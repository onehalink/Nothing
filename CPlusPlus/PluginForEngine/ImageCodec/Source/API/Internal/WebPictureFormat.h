#pragma once

#include "Engine.h"



namespace Engine::Plugin
{
	struct WebPictureFormat
	{
		static Bool IsValid(const Void* buffer, SizeType byteCount);

		static Span<Byte> Encode(const Texture& texture, SizeType imageQualityFactor = 100);
		static Texture Decode(const Void* buffer, SizeType byteCount);
	};
}