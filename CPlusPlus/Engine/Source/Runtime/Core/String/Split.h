#pragma once

#include "../Container/DynamicArray.h"

#include "Substring.h"



namespace Engine
{
	template<typename T> DynamicArray<String<T>> Split(const T* rawString, T delimiter, Int32 length = -1);
	template<typename T> DynamicArray<String<T>> Split(const String<T>& string, T delimiter);

	template<typename T> DynamicArray<String<T>> Split(const T* rawString, const T* delimiters, Int32 length = -1, Int32 delimiterLength = -1);
	template<typename T> DynamicArray<String<T>> Split(const String<T>& string, const String<T>& delimiters);

#pragma region Details

	template<typename T>
	DynamicArray<String<T>> Split(const T* rawString, T delimiter, Int32 length)
	{
		return Split( rawString, &delimiter, length, 1 );
	}

	template<typename T>
	DynamicArray<String<T>> Split(const String<T>& string, T delimiter)
	{
		return Split( string.GetBuffer(), delimiter, string.GetCount() );
	}

	template<typename T>
	DynamicArray<String<T>> Split(const T* rawString, const T* delimiters, Int32 length, Int32 delimiterLength)
	{
		if ( length == -1 )
			length = StringLength(rawString);

		if ( delimiterLength == -1 )
			delimiterLength = StringLength(delimiters);

		DynamicArray<String<T>> ret;

		SizeType startIndex = 0;
		for(SizeType index = 0; index < length; index++)
			for(SizeType iteration = 0; iteration < delimiterLength; iteration++)
				if ( delimiters[iteration] == rawString[index] )
				{
					ret.Add( Substring( rawString, startIndex, index - startIndex, length ) );

					startIndex = index + 1;
				}

		ret.Add( Substring(rawString, startIndex, length) );

		return ret;
	}

	template<typename T>
	DynamicArray<String<T>> Split(const String<T>& string, const String<T>& delimiters)
	{
		return Split( string.GetBuffer(), delimiters.GetBuffer(), string.GetCount(), delimiters.GetCount() );
	}

#pragma endregion
}