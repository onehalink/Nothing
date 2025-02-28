#pragma once

#include "Engine.h"



namespace Engine::Plugin
{
	ENGINE_API Font LoadFontFromMemory(const Void* buffer, SizeType byteCount);
	ENGINE_API Font LoadFontFromFile(const U8String& path);
}