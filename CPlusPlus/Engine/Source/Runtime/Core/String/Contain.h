#pragma once

#include "String.h"



namespace Engine
{
	template<typename T> Bool Contain(const T* rawString, T search, Int32 length = -1, Int32* outputMatchIndex = nullptr /** optional */);
	template<typename T> Bool Contain(const String<T>& string, T search, Int32* outputMatchIndex = nullptr);

	template<typename T> Bool Contain(const T* rawString, const T* search, Int32 length = -1, Int32 searchLength = -1, Int32* outputMatchIndex = nullptr);
	template<typename T> Bool Contain(const String<T>& string, const String<T>& search, Int32* outputMatchIndex = nullptr);


#pragma region Details

	template<typename T>
	Bool Contain(const T* rawString, T search, Int32 length, Int32* outputMatchIndex)
	{
		return Contain( rawString, &search, length, 1, outputMatchIndex );
	}

	template<typename T>
	Bool Contain(const String<T>& string, T search, Int32* outputMatchIndex)
	{
		return Contain( string.GetBuffer(), search, string.GetCount(), outputMatchIndex );
	}

	template<typename T>
	Bool Contain(const T* rawString, const T* search, Int32 length, Int32 searchLength, Int32* outputMatchIndex)
	{
		if ( length == -1 )
			length = StringLength(rawString);

		if ( searchLength == -1 )
			searchLength = StringLength(search);

		if ( length < searchLength )
			return false;

		SizeType end = length - searchLength;
		for(SizeType index = 0; index <= end; index++)
			if ( Memory::Equal( rawString + index, search, sizeof(T) * searchLength ) )
			{
				if (outputMatchIndex)
					*outputMatchIndex = index;

				return true;
			}

		return false;
	}

	template<typename T>
	Bool Contain(const String<T>& string, const String<T>& search, Int32* outputMatchIndex)
	{
		return Contain( string.GetBuffer(), search.GetBuffer(), string.GetCount(), search.GetCount(), outputMatchIndex );
	}

#pragma endregion
}
