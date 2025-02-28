#pragma once

/**
* Encode/Decode uncompressed 24-bit(B8G8R8) or 32-bit(B8G8R8A8) bmp file(with extension ".bmp")
*/

#include "../Asset/Texture.h"



namespace Engine
{
	struct ENGINE_API Bitmap
	{
		static Bool IsValid(const Void* buffer, SizeType byteCount);

		static Span<Byte> Encode(const Texture& texture);
		static Texture Decode(const Void* buffer, SizeType byteCount);
	};
}
