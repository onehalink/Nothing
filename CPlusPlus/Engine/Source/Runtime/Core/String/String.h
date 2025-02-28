#pragma once

#include "../Container/Span.h"

#include "../Template/IsChar.h"

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
		String(const T* inUTF);
		template<typename U> String(const U* inUTF);
		String(const Span<T>& rawStringWrapper);
		String(Span<T>&& rawStringWrapper);
		String(const String<T>& other);
		template<typename U> String(const String<U>& other);
		String(String<T>&& other);
		~String();


		T* GetBuffer();
		const T* GetBuffer() const;
		SizeType GetCount() const;


		String<T>& operator=(const String<T>& other);
		String<T>& operator=(String<T>&& other);

		T& operator[](SizeType index);
		const T& operator[](SizeType index) const;

		operator T*();
		operator const T*() const;
	private:
		Span<T> storage;


		// For Visual Studio's natvis file
		#if defined(DEBUG)
		SizeType charSize = sizeof(T);
		#endif
	};


	template<typename T> Void SetNullForRawString(T* rawString, SizeType count);
	template<typename T> Void SetNullForRawString(Span<T>& rawStringWrapper);
	template<typename T> SizeType StringLength(const T* rawString);


	template<typename T> String<T> operator+(const String<T>& L, const String<T>& R);

	template<typename T> String<T> operator+(const String<T>& string, T character);
	template<typename T> String<T> operator+(T character, const String<T>& string);

	template<typename T> String<T>& operator+=(String<T>& L, const String<T>& R);

	template<typename T> String<T>& operator+=(String<T>& string, T character);

	template<typename T> Bool operator==(const String<T>& L, const String<T>& R);
	template<typename T> Bool operator!=(const String<T>& L, const String<T>& R);


#pragma region Details

	namespace Private
	{
		inline Bool IsWhitespace(Char32 value)
		{
			return value == '\t' || value == '\v' || value == '\f' || value == '\r' || value == ' ';
		}

		template<typename T>
		const T* SkipWhitespace(const T* pointer)
		{
			while ( pointer != '\0' && IsWhitespace( *pointer ) )
				pointer++;

			return pointer;
		}
	}


	template<typename T>
	String<T>::String()
	{

	}

	template<typename T>
	String<T>::String(const T* inUTF)
	{
		storage = Span<T>( StringLength(inUTF) + 1 );
		SetNullForRawString(storage);

		Memory::Copy( inUTF, GetBuffer(), sizeof(T) * GetCount() );
	}


	template<typename T>
	template<typename U>
	String<T>::String(const U* inUTF)
	{
		*this = String<U>(inUTF);
	}

	template<typename T>
	String<T>::String(const Span<T>& rawStringWrapper)
		: storage(rawStringWrapper)
	{

	}

	template<typename T>
	String<T>::String(Span<T>&& rawStringWrapper)
		: storage( Move(rawStringWrapper) )
	{

	}

	template<typename T>
	String<T>::String(const String<T>& other)
		: storage( other.storage )
	{

	}

	template<typename T>
	template<typename U>
	String<T>::String(const String<U>& other)
	{
		using namespace Private;


		auto ConvertFromU32String = [](const U32String& u32String) -> String<T>
			{
				constexpr TextEncoding TE = TypesAreSame<T, Char8>::Value ? TextEncoding::UTF8 : TextEncoding::UTF16;


				SizeType count = GetUTFElementCountFromCodePoints<TE>( u32String.GetBuffer(), u32String.GetCount() );

				Span<T> temporary( count + 1 );
				SetNullForRawString(temporary);

				SizeType offset = 0;
				for (SizeType index = 0; index < u32String.GetCount(); index++)
					offset += ToUTF<TE>(
						temporary.GetBuffer() + offset,
						u32String[index]
					);

				return temporary;
			};

		auto ConvertToU32String = [](const String<U>& string) -> U32String
			{
				constexpr TextEncoding TE = TypesAreSame<U, Char8>::Value ? TextEncoding::UTF8 : TextEncoding::UTF16;


				SizeType count = GetCodePointCountFromUTFElements<TE>( string.GetBuffer(), string.GetCount() );

				Span<Char32> temporary( count + 1 );
				SetNullForRawString(temporary);

				SizeType offset = 0;
				for (SizeType index = 0; index < count; index++)
					offset += FromUTF<TE>(
						temporary.GetBuffer() + index,
						string.GetBuffer() + offset
					);

				return temporary;
			};


		if constexpr (
			( TypesAreSame<T, Char8>::Value && TypesAreSame<U, Char16>::Value ) ||
			( TypesAreSame<T, Char16>::Value && TypesAreSame<U, Char8>::Value )
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
		// bug fixed when storage.GetCount() == 0
		if ( !GetBuffer() )
			return 0;

		return storage.GetCount() - 1;
	}

	template<typename T>
	String<T>& String<T>::operator=(const String<T>& other)
	{
		storage = other.storage;

		return *this;
	}

	template<typename T>
	String<T>& String<T>::operator=(String<T>&& other)
	{
		storage = Move( other.storage );

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
	Void SetNullForRawString(T* rawString, SizeType count)
	{
		rawString[ count - 1 ] = '\0';
	}

	template<typename T>
	Void SetNullForRawString(Span<T>& rawStringWrapper)
	{
		SetNullForRawString( rawStringWrapper.GetBuffer(), rawStringWrapper.GetCount() );
	}

	template<typename T>
	SizeType StringLength(const T* rawString)
	{
		SizeType ret = 0;
		while ( rawString[ret] != '\0' ) ret++;

		return ret;
	}

	template<typename T>
	String<T> operator+(const String<T>& L, const String<T>& R)
	{
		SizeType count = L.GetCount() + R.GetCount();

		Span<T> temporary( count + 1 );
		SetNullForRawString(temporary);

		Memory::Copy( L.GetBuffer(), temporary.GetBuffer(),					sizeof(T) * L.GetCount() );
		Memory::Copy( R.GetBuffer(), temporary.GetBuffer() + L.GetCount(),	sizeof(T) * R.GetCount() );

		return temporary;
	}

	template<typename T>
	String<T> operator+(const String<T>& string, T character)
	{
		SizeType count = string.GetCount() + 1;

		Span<T> temporary( count + 1 );
		SetNullForRawString(temporary);

		Memory::Copy( string.GetBuffer(),	temporary.GetBuffer(),						sizeof(T) * string.GetCount()	);
		Memory::Copy( &character,			temporary.GetBuffer() + string.GetCount(),	sizeof(T) * 1					);

		return temporary;
	}

	template<typename T>
	String<T> operator+(T character, const String<T>& string)
	{
		SizeType count = 1 + string.GetCount();

		Span<T> temporary( count + 1 );
		SetNullForRawString(temporary);

		Memory::Copy( &character,			temporary.GetBuffer(),		sizeof(T) * 1					);
		Memory::Copy( string.GetBuffer(),	temporary.GetBuffer() + 1,	sizeof(T) * string.GetCount()	);

		return temporary;
	}

	template<typename T>
	String<T>& operator+=(String<T>& L, const String<T>& R)
	{
		return L = L + R;
	}

	template<typename T>
	String<T>& operator+=(String<T>& string, T character)
	{
		return string = string + character;
	}

	template<typename T>
	Bool operator==(const String<T>& L, const String<T>& R)
	{
		return ( L.GetCount() == R.GetCount() ) && Memory::Equal( L.GetBuffer(), R.GetBuffer(), sizeof(T) * L.GetCount() );
	}

	template<typename T>
	Bool operator!=(const String<T>& L, const String<T>& R)
	{
		return !operator==(L, R);
	}

#pragma endregion
}