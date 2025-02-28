#pragma once

#include "Type.h"

#include "Template/SameAsAny.h"



namespace Engine
{
	enum class Endian
	{
		Little,
		Big,

		Native = Little,
	};


	template<typename T>
	constexpr T ByteSwap(T value)
	{
		static_assert( SameAsAny<T, UInt16, UInt32, UInt64>::Value );


		if constexpr ( sizeof(T) == 2 )
			return
				( ( value & 0xFF00 ) >> 8 ) |
				( ( value & 0x00FF ) << 8 );

		if constexpr ( sizeof(T) == 4 )
			return
				( ( value & 0xFF000000 ) >> 24 ) |
				( ( value & 0x00FF0000 ) >>  8 ) |
				( ( value & 0x0000FF00 ) <<  8 ) |
				( ( value & 0x000000FF ) << 24 );

		if constexpr ( sizeof(T) == 8 )
			return
				( ( value & 0xFF00000000000000 ) >> 56 ) |
				( ( value & 0x00FF000000000000 ) >> 40 ) |
				( ( value & 0x0000FF0000000000 ) >> 24 ) |
				( ( value & 0x000000FF00000000 ) >>  8 ) |
				( ( value & 0x00000000FF000000 ) <<  8 ) |
				( ( value & 0x0000000000FF0000 ) << 24 ) |
				( ( value & 0x000000000000FF00 ) << 40 ) |
				( ( value & 0x00000000000000FF ) << 56 );
	}
}