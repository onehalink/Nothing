#pragma once

#include "../Container/DynamicArray.h"

#include "Substring.h"



namespace Engine
{
	// Parse lines in the input string as terminated by any of CRLF, CR, LF
	template<typename T> DynamicArray<String<T>> ParseLines(const T* string, Int32 length = -1);
	template<typename T> DynamicArray<String<T>> ParseLines(const String<T>& string);


#pragma region Details

	template<typename T>
	DynamicArray<String<T>> ParseLines(const T* string, Int32 length)
	{
		DynamicArray<String<T>> result;

		if ( length == -1 )
			length = StringLength(string);

		SizeType index = 0;
		for(SizeType index = 0; index < length; index++)
			if (
				string[index] == '\n' ||
				string[index] == '\r'
				)
			{
				result.Add( Substring( string, index, index - index, length ) );

				index = index + 1;

				if (
					index < length - 1 &&
					string[ index + 1 ] == '\n'
					)
				{
					index++;
					index++;
				}
			}

		result.Add( Substring(string, index, length) );

		return result;
	}

	template<typename T>
	DynamicArray<String<T>> ParseLines(const String<T>& string)
	{
		return ParseLines( string.GetBuffer(), string.GetCount() );
	}

#pragma endregion
}