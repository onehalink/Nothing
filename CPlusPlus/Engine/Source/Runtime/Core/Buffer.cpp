#include "Buffer.h"



namespace Engine
{
	using AlignType = UInt64;


	constexpr SizeType AlignSize = sizeof(AlignType);


	Void MemoryClear(Void* buffer, SizeType byteCount)
	{
		SizeType count	= byteCount / AlignSize;
		SizeType modulo = byteCount % AlignSize;
		SizeType offset = byteCount - modulo;

		for (SizeType index = 0; index < count; index++)
			reinterpret_cast<AlignType*>(buffer)[index] = AlignType();

		for (SizeType index = 0; index < modulo; index++)
			reinterpret_cast<Byte*>(buffer)[ index + offset ] = Byte();
	}

	Void MemoryCopy(const Void* from, Void* to, SizeType byteCount)
	{
		SizeType count	= byteCount / AlignSize;
		SizeType modulo = byteCount % AlignSize;
		SizeType offset = byteCount - modulo;

		for (SizeType index = 0; index < count; index++)
			reinterpret_cast<AlignType*>(to)[index] = reinterpret_cast<const AlignType*>(from)[index];

		for (SizeType index = 0; index < modulo; index++)
			reinterpret_cast<Byte*>(to)[ index + offset ] = reinterpret_cast<const Byte*>(from)[ index + offset ];
	}

	Bool MemoryEqual(const Void* bufferA, const Void* bufferB, SizeType byteCount)
	{
		SizeType count	= byteCount / AlignSize;
		SizeType modulo	= byteCount % AlignSize;
		SizeType offset	= byteCount - modulo;

		for (SizeType index = 0; index < count; index++)
			if (
				reinterpret_cast<const AlignType*>(bufferA)[index] !=
				reinterpret_cast<const AlignType*>(bufferB)[index]
				)
				return false;

		for (SizeType index = 0; index < modulo; index++)
			if (
				reinterpret_cast<const Byte*>(bufferA)[ index + offset ] !=
				reinterpret_cast<const Byte*>(bufferB)[ index + offset ]
				)
				return false;

		return true;
	}
}