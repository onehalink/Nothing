#pragma once

#include "Template.h"



namespace Engine
{
	struct ENGINE_API MemoryOp
	{
		static Void Clear(Void* buffer, SizeType byteCount);
		template<typename T> static Void Clear(T* pointer);
		static Void Copy(const Void* from, Void* to, SizeType byteCount);
		static Bool Equal(const Void* bufferA, const Void* bufferB, SizeType byteCount);
	};


#pragma region Details

	template<typename T>
	Void MemoryOp::Clear(T* pointer)
	{
		static_assert( !TypesAreSame<T, Void>::Value );


		Clear( pointer, sizeof(T) );
	}

#pragma endregion
}