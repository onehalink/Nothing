#pragma once

#include "String.h"



namespace Engine
{
	template<typename T> String<T> Remove(const T* string, SizeType index, SizeType count, Int32 length);
	template<typename T> String<T> Remove(const String<T>& string, SizeType index, SizeType count);

	template<typename T> String<T> Remove(const T* string, SizeType index, Int32 length);
	template<typename T> String<T> Remove(const String<T>& string, SizeType index);


#pragma region Details

	template<typename T>
	String<T> Remove(const T* string, SizeType index, SizeType count, Int32 length)
	{
		if ( length == -1 )
			length = StringLength(string);

		Memory<T> result( length - count + 1 );
		SetNullTerminator(result);

		MemoryCopy( string,							result.GetBuffer(),					sizeof(T) * index						);
		MemoryCopy( string + index + count,	result.GetBuffer() + index,	sizeof(T) * ( length - index - count )	);

		return result;
	}

	template<typename T>
	String<T> Remove(const String<T>& string, SizeType index, SizeType count)
	{
		return Remove( string.GetBuffer(), index, count, string.GetCount() );
	}

	template<typename T>
	String<T> Remove(const T* string, SizeType index, Int32 length)
	{
		if ( length == -1 )
			length = StringLength(string);

		return Remove( string, index, length - index, length );
	}

	template<typename T>
	String<T> Remove(const String<T>& string, SizeType index)
	{
		return Remove( string.GetBuffer(), index, string.GetCount() );
	}

#pragma endregion
}