#pragma once

#include "String.h"



namespace Engine
{
	template<typename T> String<T> Insert(const T* rawString, SizeType startIndex, T value, Int32 length = -1);
	template<typename T> String<T> Insert(const String<T>& string, SizeType startIndex, T value);

	template<typename T> String<T> Insert(const T* rawString, SizeType startIndex, const T* value, Int32 length = -1, Int32 valueLength = -1);
	template<typename T> String<T> Insert(const String<T>& string, SizeType startIndex, const String<T> value);


#pragma region Details

	template<typename T>
	String<T> Insert(const T* rawString, SizeType startIndex, T value, Int32 length)
	{
		return Insert( rawString, startIndex, &value, length, 1 );
	}

	template<typename T>
	String<T> Insert(const String<T>& string, SizeType startIndex, T value)
	{
		return Insert( string.GetBuffer(), startIndex, value, string.GetCount() );
	}

	template<typename T>
	String<T> Insert(const T* rawString, SizeType startIndex, const T* value, Int32 length, Int32 valueLength)
	{
		if ( length == -1 )
			length = StringLength(rawString);

		if ( valueLength == -1 )
			valueLength = StringLength(value);

		SizeType count = length + valueLength;

		Span<T> temporary( count + 1 );
		SetNullTerminatorForRawString(temporary);

		Memory::Copy( rawString,				temporary.GetBuffer(),								sizeof(T) * startIndex				);
		Memory::Copy( value,					temporary.GetBuffer() + startIndex,					sizeof(T) * valueLength				);
		Memory::Copy( rawString + startIndex,	temporary.GetBuffer() + startIndex + valueLength,	sizeof(T) * ( length - startIndex )	);

		return temporary;
	}

	template<typename T>
	String<T> Insert(const String<T>& string, SizeType startIndex, const String<T> value)
	{
		return Insert( string.GetBuffer(), startIndex, value.GetBuffer(), string.GetCount(), value.GetCount() );
	}

#pragma endregion
}