#pragma once

#include "String.h"



namespace Engine
{
	template<typename T> String<T> Substring(const T* rawString, SizeType startIndex, SizeType count, Int32 length);
	template<typename T> String<T> Substring(const String<T>& string, SizeType startIndex, SizeType count);

	template<typename T> String<T> Substring(const T* rawString, SizeType startIndex, Int32 length);
	template<typename T> String<T> Substring(const String<T>& string, SizeType startIndex);


#pragma region Details

	template<typename T>
	String<T> Substring(const T* rawString, SizeType startIndex, SizeType count, Int32 length)
	{
		if ( length == -1 )
			length = StringLength(rawString);

		Span<T> temporary( count + 1 );
		SetNullForRawString(temporary);

		Memory::Copy( rawString + startIndex, temporary.GetBuffer(), sizeof(T) * count );

		return temporary;
	}

	template<typename T>
	String<T> Substring(const String<T>& string, SizeType startIndex, SizeType count)
	{
		return Substring( string.GetBuffer(), startIndex, count, string.GetCount() );
	}

	template<typename T>
	String<T> Substring(const T* rawString, SizeType startIndex, Int32 length)
	{
		if ( length == -1 )
			length = StringLength(rawString);

		return Substring( rawString, startIndex, length - startIndex, length );
	}

	template<typename T>
	String<T> Substring(const String<T>& string, SizeType startIndex)
	{
		return Substring( string.GetBuffer(), startIndex, string.GetCount() );
	}

#pragma endregion
}