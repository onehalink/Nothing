#pragma once

#include "CoreMinimal.h"



namespace Engine::Base64
{
	constexpr SizeType GetEncodedLength(SizeType byteCount)
	{
		return DivideRoundUp(byteCount, 3) * 4;
	}
	constexpr SizeType GetDecodedLength(SizeType char8Count)
	{
		return char8Count / 4 * 3;
	}

	// Convert binary data to base64 encoding text
	ENGINE_API Void Encode(Span<Char8> output, ReadOnlySpan<Byte> input);
	// Convert base64 encoding text to binary data
	ENGINE_API Void Decode(Span<Byte> output, ReadOnlySpan<Char8> input);
}