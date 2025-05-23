#pragma once

#include "_Helper.h"
#include "Substring.h"



namespace Engine
{
	// Remove a set of characters from the beginning of this string
	template<typename T> String<T> TrimStart(const T* string, Int32 length = -1);
	template<typename T> String<T> TrimStart(const String<T>& string);

	// Remove a set of characters from the end of this string
	template<typename T> String<T> TrimEnd(const T* string, Int32 length = -1);
	template<typename T> String<T> TrimEnd(const String<T>& string);

	// Trim the whitespace from both ends of the string
	template<typename T> String<T> Trim(const T* string, Bool trimStart = true, Bool trimEnd = true, Int32 length = -1);
	template<typename T> String<T> Trim(const String<T>& string, Bool trimStart = true, Bool trimEnd = true);


#pragma region Details

	template<typename T>
	String<T> TrimStart(const T* string, Int32 length)
	{
		return Trim(string, true, false, length);
	}

	template<typename T>
	String<T> TrimStart(const String<T>& string)
	{
		return TrimStart( string.GetBuffer(), string.GetCount() );
	}

	template<typename T>
	String<T> TrimEnd(const T* string, Int32 length)
	{
		return Trim(string, false, true, length);
	}

	template<typename T>
	String<T> TrimEnd(const String<T>& string)
	{
		return TrimEnd( string.GetBuffer(), string.GetCount() );
	}

	template<typename T>
	String<T> Trim(const T* string, Bool trimStart, Bool trimEnd, Int32 length)
	{
		using namespace Private;


		if ( length == -1 )
			length = StringLength(string);

		SizeType index = 0;
		if(trimStart)
			for(SizeType index = 0; index < length; index++)
				if ( !IsWhitespace( string[index] ) )
				{
					index = index;

					break;
				}

		SizeType count = length - index;
		if(trimEnd)
			for(Int32 index = length - 1; index > index; index--)
				if ( !IsWhitespace( string[index] ) )
				{
					count = ( index + 1 ) - index;

					break;
				}

		return Substring(string, index, count, length);
	}

	template<typename T>
	String<T> Trim(const String<T>& string, Bool trimStart, Bool trimEnd)
	{
		return Trim( string.GetBuffer(), trimStart, trimEnd, string.GetCount() );
	}

#pragma endregion
}