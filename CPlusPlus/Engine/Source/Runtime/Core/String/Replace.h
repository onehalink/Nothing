#pragma once

#include "Contain.h"



namespace Engine
{
	template<typename T> String<T> Replace(const T* string, T search, T replace, Int32 length = -1);
	template<typename T> String<T> Replace(const String<T>& string, T search, T replace);

	template<typename T> String<T> Replace(const T* string, const T* search, const T* replace, Int32 length = -1, Int32 searchLength = -1, Int32 replaceLength = -1);
	template<typename T> String<T> Replace(const String<T>& string, const String<T>& search, const String<T>& replace);


#pragma region Details

	template<typename T>
	String<T> Replace(const T* string, T search, T replace, Int32 length)
	{
		return Replace( string, &search, &replace, length, 1, 1 );
	}

	template<typename T>
	String<T> Replace(const String<T>& string, T search, T replace)
	{
		return Replace( string.GetBuffer(), search, replace, string.GetCount() );
	}

	template<typename T>
	String<T> Replace(const T* string, const T* search, const T* replace, Int32 length, Int32 searchLength, Int32 replaceLength)
	{
		if ( length == -1 )
			length = StringLength(string);

		if ( searchLength == -1 )
			searchLength = StringLength(search);

		if ( replaceLength == -1 )
			replaceLength = StringLength(replace);

		Int32 index = 0;
		if (
			length < searchLength ||
			!Contain( string, search, length, searchLength, &index )
			)
			return String<T>(string);

		Memory<T> result( length - searchLength + replaceLength + 1 );
		SetNullTerminator(result);

		MemoryCopy( string,								result.GetBuffer(),									sizeof(T) * index								);
		MemoryCopy( replace,							result.GetBuffer() + index,					sizeof(T) * replaceLength							);
		MemoryCopy( string + index + searchLength,	result.GetBuffer() + index + replaceLength,	sizeof(T) * ( length - index - searchLength )	);

		return result;
	}

	template<typename T>
	String<T> Replace(const String<T>& string, const String<T>& search, const String<T>& replace)
	{
		return Replace( string.GetBuffer(), search.GetBuffer(), replace.GetBuffer(), string.GetCount(), search.GetCount(), replace.GetCount() );
	}

#pragma endregion
}