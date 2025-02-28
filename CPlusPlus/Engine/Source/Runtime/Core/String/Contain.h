#pragma once

#include "String.h"



namespace Engine
{
	template<typename T> Bool Contain(const T* string, T search, Int32 length = -1, Int32* outputMatchIndex = nullptr);
	template<typename T> Bool Contain(const String<T>& string, T search, Int32* outputMatchIndex = nullptr);

	template<typename T> Bool Contain(const T* string, const T* search, Int32 length = -1, Int32 searchLength = -1, Int32* outputMatchIndex = nullptr);
	template<typename T> Bool Contain(const String<T>& string, const String<T>& search, Int32* outputMatchIndex = nullptr);


#pragma region Details

	template<typename T>
	Bool Contain(const T* string, T search, Int32 length, Int32* outputMatchIndex)
	{
		return Contain( string, &search, length, 1, outputMatchIndex );
	}

	template<typename T>
	Bool Contain(const String<T>& string, T search, Int32* outputMatchIndex)
	{
		return Contain( string.GetBuffer(), search, string.GetCount(), outputMatchIndex );
	}

	template<typename T>
	Bool Contain(const T* string, const T* search, Int32 length, Int32 searchLength, Int32* outputMatchIndex)
	{
		if ( length == -1 )
			length = StringLength(string);

		if ( searchLength == -1 )
			searchLength = StringLength(search);

		for(SizeType index = 0, end = length - searchLength + 1; index < end; index++)
			if ( MemoryEqual( string + index, search, sizeof(T) * searchLength ) )
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
