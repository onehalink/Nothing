#pragma once

#include "Engine.h"



namespace Engine::Plugin
{
	struct ENGINE_PLUGIN_API PortableNetworkGraphics
	{
		static Bool IsValid(const Void* buffer, SizeType byteCount);

		static Span<Byte> Encode(const Texture& texture);
		static Texture Decode(const Void* buffer, SizeType byteCount);
	};
}