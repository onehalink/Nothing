#include "Buffer.h"



namespace Engine::Buffer
{
	using AlignType = UInt64;


	constexpr SizeType AlignSize = sizeof(AlignType);


	Void Clear(Void* buffer, SizeType byteCount)
	{
		SizeType count	= byteCount / AlignSize;
		SizeType modulo = byteCount % AlignSize;
		SizeType offset = byteCount - modulo;

		for (SizeType index = 0; index < count; ++index)
			reinterpret_cast<AlignType*>(buffer)[index] = AlignType();

		for (SizeType index = 0; index < modulo; ++index)
			reinterpret_cast<Byte*>(buffer)[ index + offset ] = Byte();
	}

	Void Copy(Void* destination, const Void* source, SizeType byteCount)
	{
		SizeType count	= byteCount / AlignSize;
		SizeType modulo = byteCount % AlignSize;
		SizeType offset = byteCount - modulo;

		for (SizeType index = 0; index < count; ++index)
			reinterpret_cast<AlignType*>(destination)[index] = reinterpret_cast<const AlignType*>(source)[index];

		for (SizeType index = 0; index < modulo; ++index)
			reinterpret_cast<Byte*>(destination)[ index + offset ] = reinterpret_cast<const Byte*>(source)[ index + offset ];
	}

	Bool Equal(const Void* bufferA, const Void* bufferB, SizeType byteCount)
	{
		SizeType count	= byteCount / AlignSize;
		SizeType modulo	= byteCount % AlignSize;
		SizeType offset	= byteCount - modulo;

		for (SizeType index = 0; index < count; ++index)
			if (
				reinterpret_cast<const AlignType*>(bufferA)[index] !=
				reinterpret_cast<const AlignType*>(bufferB)[index]
				)
				return false;

		for (SizeType index = 0; index < modulo; ++index)
			if (
				reinterpret_cast<const Byte*>(bufferA)[ index + offset ] !=
				reinterpret_cast<const Byte*>(bufferB)[ index + offset ]
				)
				return false;

		return true;
	}
}