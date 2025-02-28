#pragma once

#include "../Container/DynamicArray.h"

#include "Substring.h"



namespace Engine
{
	template<typename T> DynamicArray<String<T>> Split(const T* string, T delimiter, Int32 length = -1);
	template<typename T> DynamicArray<String<T>> Split(const String<T>& string, T delimiter);

	template<typename T> DynamicArray<String<T>> Split(const T* string, const T* delimiter, Int32 length = -1, Int32 delimiterLength = -1);
	template<typename T> DynamicArray<String<T>> Split(const String<T>& string, const String<T>& delimiter);


#pragma region Details

	template<typename T>
	DynamicArray<String<T>> Split(const T* string, T delimiter, Int32 length)
	{
		return Split( string, &delimiter, length, 1 );
	}

	template<typename T>
	DynamicArray<String<T>> Split(const String<T>& string, T delimiter)
	{
		return Split( string.GetBuffer(), delimiter, string.GetCount() );
	}

	template<typename T>
	DynamicArray<String<T>> Split(const T* string, const T* delimiter, Int32 length, Int32 delimiterLength)
	{
		DynamicArray<String<T>> result;

		if ( length == -1 )
			length = StringLength(string);

		if ( delimiterLength == -1 )
			delimiterLength = StringLength(delimiter);

		SizeType index = 0;
		for (SizeType index = 0; index < length; index++)
			for (SizeType iteration = 0; iteration < delimiterLength; iteration++)
				if ( delimiter[iteration] == string[index] )
				{
					result.Add( Substring( string, index, index - index, length ) );

					index = index + 1;
				}

		result.Add( Substring(string, index, length) );

		return result;
	}

	template<typename T>
	DynamicArray<String<T>> Split(const String<T>& string, const String<T>& delimiter)
	{
		return Split( string.GetBuffer(), delimiter.GetBuffer(), string.GetCount(), delimiter.GetCount() );
	}

#pragma endregion
}