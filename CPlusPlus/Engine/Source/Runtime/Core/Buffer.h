#pragma once

#include "Build.h"
#include "Type.h"

#include "Mathematics/Numeric.h"



namespace Engine::Buffer
{
	ENGINE_API Void Clear(Void* buffer, SizeType byteCount);
	ENGINE_API Void Copy(Void* destination, const Void* source, SizeType byteCount);
	ENGINE_API Bool Equal(const Void* bufferA, const Void* bufferB, SizeType byteCount);
}


namespace Engine
{
	template<typename T> Void MemoryClear(T* buffer, SizeType count = 1);
	template<typename T> Void MemoryCopy(Void* destination, const T* source, SizeType count = 1);
	template<typename T, typename U> Bool MemoryEqual(const T* bufferA, const U* bufferB, SizeType count = 1);


#pragma region Details

	namespace Private::MemoryOp
	{
		template<typename T>	constexpr SizeType TypeSize			= sizeof(T);
		template<>				constexpr SizeType TypeSize<Void>	= 1; 
	}


	template<typename T> Void MemoryClear(T* buffer, SizeType count)
	{
		Buffer::Clear( buffer, Private::MemoryOp::TypeSize<T> * count );
	}

	template<typename T>
	Void MemoryCopy(Void* destination, const T* source, SizeType count)
	{
		Buffer::Copy( destination, source, Private::MemoryOp::TypeSize<T> * count );
	}

	template<typename T, typename U>
	Bool MemoryEqual(const T* bufferA, const U* bufferB, SizeType count)
	{
		using namespace Private::MemoryOp;


		return Buffer::Equal( bufferA, bufferB, Minimum( TypeSize<T>, TypeSize<U> ) * count );
	}

#pragma endregion
}