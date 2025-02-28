#pragma once

#include "String.h"



namespace Engine
{
	template<typename T> Bool StartWith(const T* string, T search, Int32 length = -1);
	template<typename T> Bool StartWith(const String<T>& string, T search);

	template<typename T> Bool StartWith(const T* string, const T* search, Int32 length = -1, Int32 searchLength = -1);
	template<typename T> Bool StartWith(const String<T>& string, const String<T>& search);


	template<typename T> Bool EndWith(const T* string, T search, Int32 length = -1);
	template<typename T> Bool EndWith(const String<T>& string, T search);

	template<typename T> Bool EndWith(const T* string, const T* search, Int32 length = -1, Int32 searchLength = -1);
	template<typename T> Bool EndWith(const String<T>& string, const String<T> search);


#pragma region Details

	template<typename T>
	Bool StartWith(const T* string, T search, Int32 length)
	{
		return StartWith( string, &search, length, 1 );
	}

	template<typename T>
	Bool StartWith(const String<T>& string, T search)
	{
		return StartWith( string.GetBuffer(), search, string.GetCount() );
	}

	template<typename T>
	Bool StartWith(const T* string, const T* search, Int32 length, Int32 searchLength)
	{
		if ( length == -1 )
			length = StringLength(string);

		if ( searchLength == -1 )
			searchLength = StringLength(search);

		if ( length < searchLength )
			return false;

		return MemoryEqual( string, search, sizeof(T) * searchLength );
	}

	template<typename T>
	Bool StartWith(const String<T>& string, const String<T>& search)
	{
		return StartWith( string.GetBuffer(), search.GetBuffer(), string.GetCount(), search.GetCount() );
	}

	template<typename T>
	Bool EndWith(const T* string, T search, Int32 length)
	{
		return EndWith( string, &search, length, 1 );
	}

	template<typename T>
	Bool EndWith(const String<T>& string, T search)
	{
		return EndWith( string.GetBuffer(), search, string.GetCount() );
	}

	template<typename T>
	Bool EndWith(const T* string, const T* search, Int32 length, Int32 searchLength)
	{
		if ( length == -1 )
			length = StringLength(string);

		if ( searchLength == -1 )
			searchLength = StringLength(search);

		if ( length < searchLength )
			return false;

		return MemoryEqual( string + length - searchLength, search, sizeof(T) * searchLength );
	}

	template<typename T>
	Bool EndWith(const String<T>& string, const String<T> search)
	{
		return EndWith( string.GetBuffer(), search.GetBuffer(), string.GetCount(), search.GetCount() );
	}

#pragma endregion
}