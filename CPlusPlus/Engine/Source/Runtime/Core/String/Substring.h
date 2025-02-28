#pragma once

#include "String.h"



namespace Engine
{
	template<typename T> String<T> Substring(const T* string, SizeType index, SizeType count, Int32 length);
	template<typename T> String<T> Substring(const String<T>& string, SizeType index, SizeType count);

	template<typename T> String<T> Substring(const T* string, SizeType index, Int32 length);
	template<typename T> String<T> Substring(const String<T>& string, SizeType index);


#pragma region Details

	template<typename T>
	String<T> Substring(const T* string, SizeType index, SizeType count, Int32 length)
	{
		if ( length == -1 )
			length = StringLength(string);

		Memory<T> result( count + 1 );
		SetNullTerminator(result);

		MemoryCopy( string + index, result.GetBuffer(), sizeof(T) * count );

		return result;
	}

	template<typename T>
	String<T> Substring(const String<T>& string, SizeType index, SizeType count)
	{
		return Substring( string.GetBuffer(), index, count, string.GetCount() );
	}

	template<typename T>
	String<T> Substring(const T* string, SizeType index, Int32 length)
	{
		if ( length == -1 )
			length = StringLength(string);

		return Substring( string, index, length - index, length );
	}

	template<typename T>
	String<T> Substring(const String<T>& string, SizeType index)
	{
		return Substring( string.GetBuffer(), index, string.GetCount() );
	}

#pragma endregion
}