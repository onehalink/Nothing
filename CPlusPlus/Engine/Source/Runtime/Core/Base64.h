#pragma once

#include "Container/Span.h"



namespace Engine
{
	struct ENGINE_API Base64
	{
		// Convert binary data to base64 encoding text
		static Span<Char8> Encode(const Void* buffer, SizeType byteCount);
		// Convert base64 encoding text to binary data
		static Span<Byte> Decode(const Void* buffer, SizeType byteCount);
	};
}