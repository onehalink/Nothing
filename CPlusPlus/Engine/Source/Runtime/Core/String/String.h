#pragma once

#include "../CoreMinimal.h"

#include "Unicode.h"



namespace Engine
{
	template<typename T> class String;

	using U8String	= String<Char8>;
	using U16String = String<Char16>;
	using U32String = String<Char32>;


	template<typename T>
	class String
	{
	public:
		static_assert( IsChar<T>::Value );


		String();
		template<typename U>
		String(const U* string);
		String(const T* string);
		String(Memory<T>&& stringWrapper);
		String(const Memory<T>& stringWrapper);
		template<typename U>
		String(const String<U>& other);
		String(String<T>&& other);
		String(const String<T>& other);
		~String();


		T* GetBuffer();
		const T* GetBuffer() const;
		SizeType GetCount() const;


		String<T>& operator=(String<T>&& other);
		String<T>& operator=(const String<T>& other);

		T& operator[](SizeType index);
		const T& operator[](SizeType index) const;

		operator T*();
		operator const T*() const;
	private:
		Memory<T> storage;


		// For Visual Studio's natvis file
		#if defined(DEBUG)
		SizeType charSize = sizeof(T);
		#endif
	};


	template<typename T> Void SetNullTerminator(T* string, SizeType count /** indicate how many chars(null terminator included) could be placed in string */);
	template<typename T> Void SetNullTerminator(Memory<T>& stringWrapper);
	template<typename T> SizeType StringLength(const T* string);


	template<typename T> String<T> operator+(const String<T>& string, const T* nullTerminatedString);
	template<typename T> String<T> operator+(const T* nullTerminatedString, const String<T>& string);
	template<typename T> String<T> operator+(const String<T>& string, T value);
	template<typename T> String<T> operator+(T value, const String<T>& string);
	template<typename T> String<T> operator+(const String<T>& L, const String<T>& R);
	template<typename T> String<T>& operator+=(String<T>& string, const T* nullTerminatedString);
	template<typename T> String<T>& operator+=(String<T>& string, T value);
	template<typename T> String<T>& operator+=(String<T>& L, const String<T>& R);

	template<typename T> Bool operator==(const String<T>& string, const T* nullTerminatedString);
	template<typename T> Bool operator==(const T* nullTerminatedString, const String<T>& string);
	template<typename T> Bool operator==(const String<T>& L, const String<T>& R);
	template<typename T> Bool operator!=(const String<T>& string, const T* nullTerminatedString);
	template<typename T> Bool operator!=(const T* nullTerminatedString, const String<T>& string);
	template<typename T> Bool operator!=(const String<T>& L, const String<T>& R);


#pragma region Details

	namespace Private
	{
		template<typename T>
		String<T> CombineString(const T* stringA, const T* stringB, Int32 lengthA = -1, Int32 lengthB = -1)
		{
			if ( lengthA == -1 )
				lengthA = StringLength(stringA);

			if ( lengthB == -1 )
				lengthB = StringLength(stringB);

			Memory<T> result( lengthA + lengthB + 1 );
			SetNullTerminator(result);

			MemoryCopy( stringA, result.GetBuffer(),			sizeof(T) * lengthA );
			MemoryCopy( stringB, result.GetBuffer() + lengthA,	sizeof(T) * lengthB );

			return result;
		}

		template<typename T>
		Bool StringEqual(const T* stringA, const T* stringB, Int32 lengthA = -1, Int32 lengthB = -1)
		{
			if ( lengthA == -1 )
				lengthA = StringLength(stringA);

			if ( lengthB == -1 )
				lengthB = StringLength(stringB);

			return ( lengthA == lengthB ) && MemoryEqual( stringA, stringB, sizeof(T) * lengthA );
		}
	}


	template<typename T>
	String<T>::String()
	{

	}

	template<typename T>
	template<typename U>
	String<T>::String(const U* string)
	{
		*this = String<U>(string);
	}

	template<typename T>
	String<T>::String(const T* string)
	{
		storage = Memory<T>( StringLength(string) + 1 );
		SetNullTerminator(storage);

		MemoryCopy( string, GetBuffer(), sizeof(T) * GetCount() );
	}

	template<typename T>
	String<T>::String(Memory<T>&& stringWrapper)
		: storage( Forward<Memory<T>>(stringWrapper) )
	{

	}

	template<typename T>
	String<T>::String(const Memory<T>& stringWrapper)
		: storage(stringWrapper)
	{

	}

	template<typename T>
	template<typename U>
	String<T>::String(const String<U>& other)
	{
		auto ConvertFromU32String = [](const U32String& string) -> String<T>
			{
				constexpr TextEncoding TE = TypesAreSame<T, Char8>::Value ? TextEncoding::UTF8 : TextEncoding::UTF16;


				SizeType count = GetUTFElementCountFromCodePoints<TE>( string.GetBuffer(), string.GetCount() );

				Memory<T> result( count + 1 );
				SetNullTerminator(result);

				SizeType offset = 0;
				for (SizeType index = 0; index < string.GetCount(); index++)
					offset += ToUTF<TE>(
						result.GetBuffer() + offset,
						string[index]
					);

				return result;
			};

		auto ConvertToU32String = [](const String<U>& string) -> U32String
			{
				constexpr TextEncoding TE = TypesAreSame<U, Char8>::Value ? TextEncoding::UTF8 : TextEncoding::UTF16;


				SizeType count = GetCodePointCountFromUTFElements<TE>( string.GetBuffer(), string.GetCount() );

				Memory<Char32> result( count + 1 );
				SetNullTerminator(result);

				SizeType offset = 0;
				for (SizeType index = 0; index < count; index++)
					offset += FromUTF<TE>(
						result.GetBuffer() + index,
						string.GetBuffer() + offset
					);

				return result;
			};


		if constexpr (
			( TypesAreSame<T,  Char8>::Value && TypesAreSame<U, Char16>::Value ) ||
			( TypesAreSame<T, Char16>::Value && TypesAreSame<U,  Char8>::Value )
			)
			*this = ConvertFromU32String( ConvertToU32String(other) );

		if constexpr ( TypesAreSame<U, Char32>::Value )
			*this = ConvertFromU32String(other);

		if constexpr ( TypesAreSame<T, Char32>::Value )
			*this = ConvertToU32String(other);
	}


	template<typename T>
	String<T>::String(String<T>&& other)
		: storage( Move( other.storage ) )
	{

	}

	template<typename T>
	String<T>::String(const String<T>& other)
		: storage( other.storage )
	{

	}

	template<typename T>
	String<T>::~String()
	{

	}

	template<typename T>
	T* String<T>::GetBuffer()
	{
		return storage.GetBuffer();
	}

	template<typename T>
	const T* String<T>::GetBuffer() const
	{
		return storage.GetBuffer();
	}

	template<typename T>
	SizeType String<T>::GetCount() const
	{
		return GetBuffer() == nullptr ? 0 : storage.GetCount() - 1;
	}

	template<typename T>
	String<T>& String<T>::operator=(String<T>&& other)
	{
		storage = Move( other.storage );

		return *this;
	}

	template<typename T>
	String<T>& String<T>::operator=(const String<T>& other)
	{
		storage = other.storage;

		return *this;
	}

	template<typename T>
	T& String<T>::operator[](SizeType index)
	{
		return GetBuffer()[index];
	}

	template<typename T>
	const T& String<T>::operator[](SizeType index) const
	{
		return GetBuffer()[index];
	}

	template<typename T>
	String<T>::operator T*()
	{
		return GetBuffer();
	}

	template<typename T>
	String<T>::operator const T*() const
	{
		return GetBuffer();
	}

	template<typename T>
	Void SetNullTerminator(T* string, SizeType count)
	{
		string[count - 1] = '\0';
	}

	template<typename T>
	Void SetNullTerminator(Memory<T>& stringWrapper)
	{
		SetNullTerminator( stringWrapper.GetBuffer(), stringWrapper.GetCount() );
	}

	template<typename T>
	SizeType StringLength(const T* string)
	{
		SizeType result = 0;
		while ( string[result] != '\0' ) result++;

		return result;
	}

	template<typename T>
	String<T> operator+(const String<T>& string, const T* nullTerminatedString)
	{
		return Private::CombineString( string.GetBuffer(), nullTerminatedString, string.GetCount(), -1 );
	}

	template<typename T>
	String<T> operator+(const T* nullTerminatedString, const String<T>& string)
	{
		return Private::CombineString( nullTerminatedString, string.GetBuffer(), -1, string.GetCount() );
	}

	template<typename T>
	String<T> operator+(const String<T>& string, T value)
	{
		return Private::CombineString( string.GetBuffer(), &value, string.GetCount(), 1 );
	}

	template<typename T>
	String<T> operator+(T value, const String<T>& string)
	{
		return Private::CombineString( &value, string.GetBuffer(), 1, string.GetCount() );
	}

	template<typename T>
	String<T> operator+(const String<T>& L, const String<T>& R)
	{
		return Private::CombineString( L.GetBuffer(), R.GetBuffer(), L.GetCount(), R.GetCount() );
	}

	template<typename T>
	String<T>& operator+=(String<T>& string, const T* nullTerminatedString)
	{
		return string = string + nullTerminatedString;
	}

	template<typename T>
	String<T>& operator+=(String<T>& string, T value)
	{
		return string = string + value;
	}

	template<typename T>
	String<T>& operator+=(String<T>& L, const String<T>& R)
	{
		return L = L + R;
	}

	template<typename T>
	Bool operator==(const String<T>& string, const T* nullTerminatedString)
	{
		return Private::StringEqual( string.GetBuffer(), nullTerminatedString, string.GetCount(), -1 );
	}

	template<typename T>
	Bool operator==(const T* nullTerminatedString, const String<T>& string)
	{
		return string == nullTerminatedString;
	}

	template<typename T>
	Bool operator==(const String<T>& L, const String<T>& R)
	{
		return Private::StringEqual( L.GetBuffer(), R.GetBuffer(), L.GetCount(), R.GetCount() );
	}

	template<typename T>
	Bool operator!=(const String<T>& string, const T* nullTerminatedString)
	{
		return !operator==(string, nullTerminatedString);
	}

	template<typename T>
	Bool operator!=(const T* nullTerminatedString, const String<T>& string)
	{
		return string != nullTerminatedString;
	}

	template<typename T>
	Bool operator!=(const String<T>& L, const String<T>& R)
	{
		return !operator==(L, R);
	}

#pragma endregion
}
