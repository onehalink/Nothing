#pragma once

#include "String.h"



namespace Engine
{
	template<typename T> String<T> Insert(const T* string, SizeType index, T value, Int32 length = -1);
	template<typename T> String<T> Insert(const String<T>& string, SizeType index, T value);

	template<typename T> String<T> Insert(const T* string, SizeType index, const T* value, Int32 length = -1, Int32 valueLength = -1);
	template<typename T> String<T> Insert(const String<T>& string, SizeType index, const String<T> value);


#pragma region Details

	template<typename T>
	String<T> Insert(const T* string, SizeType index, T value, Int32 length)
	{
		return Insert( string, index, &value, length, 1 );
	}

	template<typename T>
	String<T> Insert(const String<T>& string, SizeType index, T value)
	{
		return Insert( string.GetBuffer(), index, value, string.GetCount() );
	}

	template<typename T>
	String<T> Insert(const T* string, SizeType index, const T* value, Int32 length, Int32 valueLength)
	{
		if ( length == -1 )
			length = StringLength(string);

		if ( valueLength == -1 )
			valueLength = StringLength(value);

		Memory<T> result( length + valueLength + 1 );
		SetNullTerminator(result);

		MemoryCopy( string,					result.GetBuffer(),								sizeof(T) * index				);
		MemoryCopy( value,					result.GetBuffer() + index,				sizeof(T) * valueLength				);
		MemoryCopy( string + index,	result.GetBuffer() + index + valueLength,	sizeof(T) * ( length - index )	);

		return result;
	}

	template<typename T>
	String<T> Insert(const String<T>& string, SizeType index, const String<T> value)
	{
		return Insert( string.GetBuffer(), index, value.GetBuffer(), string.GetCount(), value.GetCount() );
	}

#pragma endregion
}