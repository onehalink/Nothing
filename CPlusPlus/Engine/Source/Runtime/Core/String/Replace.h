#pragma once

#include "Contain.h"



namespace Engine
{
	template<typename T> String<T> Replace(const T* rawString, T search, T replace, Int32 length = -1);
	template<typename T> String<T> Replace(const String<T>& string, T search, T replace);

	template<typename T> String<T> Replace(const T* rawString, const T* search, const T* replace, Int32 length = -1, Int32 searchLength = -1, Int32 replaceLength = -1);
	template<typename T> String<T> Replace(const String<T>& string, const String<T>& search, const String<T>& replace);


#pragma region Details

	template<typename T>
	String<T> Replace(const T* rawString, T search, T replace, Int32 length)
	{
		return Replace( rawString, &search, &replace, length, 1, 1 );
	}

	template<typename T>
	String<T> Replace(const String<T>& string, T search, T replace)
	{
		return Replace( string.GetBuffer(), search, replace, string.GetCount() );
	}

	template<typename T>
	String<T> Replace(const T* rawString, const T* search, const T* replace, Int32 length, Int32 searchLength, Int32 replaceLength)
	{
		if ( length == -1 )
			length = StringLength(rawString);

		if ( searchLength == -1 )
			searchLength == StringLength(search);

		if ( replace == -1 )
			replaceLength == StringLength(replace);

		SizeType startIndex = 0;
		if (
			length < searchLength ||
			!Contain( rawString, search, length, searchLength, &startIndex )
			)
			return String<T>(rawString);

		SizeType count = length - searchLength + replaceLength;

		Memory<T> temporary( count + 1 );
		SetNullForRawString(temporary);

		MemoryOp::Copy( rawString,	temporary.GetBuffer(),				sizeof(T) * startIndex		);
		MemoryOp::Copy( replace,		temporary.GetBuffer() + startIndex, sizeof(T) * replaceLength	);

		SizeType offset = startIndex + searchLength;
		MemoryOp::Copy( rawString + offset, temporary.GetBuffer() + startIndex + replaceLength, sizeof(T) * ( length - offset ) );

		return temporary;
	}

	template<typename T>
	String<T> Replace(const String<T>& string, const String<T>& search, const String<T>& replace)
	{
		return Replace( string.GetBuffer(), search.GetBuffer(), replace.GetBuffer(), string.GetCount(), search.GetCount(), replace.GetCount() );
	}

#pragma endregion
}