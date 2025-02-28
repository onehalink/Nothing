#pragma once

#include "String.h"



namespace Engine
{
	template<typename T> Int32 FindFirst(const T* rawString, T search, Int32 length = -1);
	template<typename T> Int32 FindFirst(const String<T>& string, T search);

	template<typename T> Int32 FindLast(const T* rawString, T search, Int32 length = -1);
	template<typename T> Int32 FindLast(const String<T>& string, T search, Int32 length = -1);

	template<typename T> Int32 FindFirstOfAny(const T* rawString, const T* search, Int32 length = -1, Int32 searchLength = -1);
	template<typename T> Int32 FindFirstOfAny(const String<T>& string, const String<T>& search);

	template<typename T> Int32 FindLastOfAny(const T* rawString, const T* search, Int32 length = -1, Int32 searchLength = -1);
	template<typename T> Int32 FindLastOfAny(const String<T>& string, const String<T>& search);


#pragma region Details

	template<typename T>
	Int32 FindFirst(const T* rawString, T search, Int32 length)
	{
		return FindFirstOfAny( rawString, &search, length, 1 );
	}

	template<typename T>
	Int32 FindFirst(const String<T>& string, T search)
	{
		return FindFirst( string.GetBuffer(), search, string.GetCount() );
	}

	template<typename T>
	Int32 FindLast(const T* rawString, T search, Int32 length)
	{
		return FindLastOfAny( rawString, &search, length, 1 );
	}

	template<typename T>
	Int32 FindLast(const String<T>& string, T search, Int32 length)
	{
		return FindLast( string.GetBuffer(), search, string.GetCount() );
	}

	template<typename T>
	Int32 FindFirstOfAny(const T* rawString, const T* search, Int32 length, Int32 searchLength)
	{
		if ( length == -1 )
			length = StringLength(rawString);

		if ( searchLength == -1 )
			searchLength = StringLength(search);

		for (SizeType index = 0; index < length; index++)
			for (SizeType iteration = 0; iteration < searchLength; iteration++)
				if ( rawString[index] == search[iteration] )
					return index;

		return -1;
	}

	template<typename T>
	Int32 FindFirstOfAny(const String<T>& string, const String<T>& search)
	{
		return FindFirstOfAny( string.GetBuffer(), search.GetBuffer(), string.GetCount(), search.GetCount() );
	}

	template<typename T>
	Int32 FindLastOfAny(const T* rawString, const T* search, Int32 length, Int32 searchLength)
	{
		if ( length == -1 )
			length = StringLength(rawString);

		if ( searchLength == -1 )
			searchLength = StringLength(search);

		for (Int32 index = length - 1; index >= 0; index--)
			for (SizeType iteration = 0; iteration < searchLength; iteration++)
				if ( rawString[index] == search[iteration] )
					return index;

		return -1;
	}

	template<typename T>
	Int32 FindLastOfAny(const String<T>& string, const String<T>& search)
	{
		return FindLastOfAny( string.GetBuffer(), search.GetBuffer(), string.GetCount(), search.GetCount() );
	}

#pragma endregion
}