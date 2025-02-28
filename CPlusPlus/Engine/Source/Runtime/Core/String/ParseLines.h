#pragma once

#include "../Container/DynamicArray.h"

#include "Substring.h"



namespace Engine
{
	// Parse lines in the input string as terminated by any of CRLF, CR, LF
	template<typename T> Array<String<T>> ParseLines(const T* rawString, Int32 length = -1);
	template<typename T> Array<String<T>> ParseLines(const String<T>& string);


#pragma region Details

	template<typename T>
	Array<String<T>> ParseLines(const T* rawString, Int32 length)
	{
		if ( length == -1 )
			length = StringLength(rawString);

		Array<String<T>> ret;

		SizeType startIndex = 0;
		for(SizeType index = 0; index < length; index++)
			if (
				rawString[index] == LF ||
				rawString[index] == CR
				)
			{
				ret.Add( Substring( rawString, startIndex, index - startIndex, length ) );

				startIndex = index + 1;

				if (
					index < length - 1 &&
					rawString[ index + 1 ] == LF
					)
				{
					index++;
					startIndex++;
				}
			}

		ret.Add( Substring(rawString, startIndex, length) );

		return ret;
	}

	template<typename T>
	Array<String<T>> ParseLines(const String<T>& string)
	{
		return ParseLines( string.GetBuffer(), string.GetCount() );
	}

#pragma endregion
}