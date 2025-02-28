#pragma once

// Encode/Decode uncompressed 24-bit(B8G8R8) or 32-bit(B8G8R8A8) bmp file(with extension ".bmp")

#include "../Asset/Texture.h"



namespace Engine::Bitmap
{
	ENGINE_API Bool IsValid(ReadOnlySpan<Byte> bytes);

	ENGINE_API Memory<Byte> Encode(const Texture& texture);
	ENGINE_API Texture Decode(ReadOnlySpan<Byte> bytes);
}
