#pragma once

#include "String.h"



namespace Engine
{
	template<typename T> String<T> Remove(const T* rawString, SizeType startIndex, SizeType count, Int32 length);
	template<typename T> String<T> Remove(const String<T>& string, SizeType startIndex, SizeType count);

	template<typename T> String<T> Remove(const T* rawString, SizeType startIndex, Int32 length);
	template<typename T> String<T> Remove(const String<T>& string, SizeType startIndex);


#pragma region Details

	template<typename T>
	String<T> Remove(const T* rawString, SizeType startIndex, SizeType count, Int32 length)
	{
		if ( length == -1 )
			length = StringLength(rawString);

		SizeType size = length - count;

		Span<T> temporary( size + 1 );
		SetNullForRawString(temporary);

		Memory::Copy( rawString, temporary.GetBuffer(), sizeof(T) * startIndex );

		SizeType offset = startIndex + count;
		Memory::Copy( rawString + offset, temporary.GetBuffer() + startIndex, sizeof(T) * ( length - offset ) );

		return temporary;
	}

	template<typename T>
	String<T> Remove(const String<T>& string, SizeType startIndex, SizeType count)
	{
		return Remove( string.GetBuffer(), startIndex, count, string.GetCount() );
	}

	template<typename T>
	String<T> Remove(const T* rawString, SizeType startIndex, Int32 length)
	{
		if ( length == -1 )
			length = StringLength(rawString);

		return Remove( rawString, startIndex, length - startIndex, length );
	}

	template<typename T>
	String<T> Remove(const String<T>& string, SizeType startIndex)
	{
		return Remove( string.GetBuffer(), startIndex, string.GetCount() );
	}

#pragma endregion
}