#pragma once

#include "Macro.h"
#include "Type.h"



namespace Engine
{
	ENGINE_API Void MemoryClear(Void* buffer, SizeType byteCount);
	ENGINE_API Void MemoryCopy(const Void* from, Void* to, SizeType byteCount);
	ENGINE_API Bool MemoryEqual(const Void* bufferA, const Void* bufferB, SizeType byteCount);


	template<typename T>
	Void MemoryClear(T* pointer)
	{
		MemoryClear( pointer, sizeof(T) );
	}
}