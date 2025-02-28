#pragma once

#include "../CoreMinimal.h"
#include "../Memory.h"
#include "../Unicode.h"

#include "StringView.h"



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
		String(SizeType count);
		String(const T* string);
		String(StringView<T> view);
		String(String<T>&& other);
		String(const String<T>& other);
		String<T>& operator=(String<T>&& other);
		String<T>& operator=(const String<T>& other);
		template<typename U> String(const U* string);
		template<typename U> String(StringView<U> view);
		template<typename U> String(const String<U>& other);


		Bool IsNullOrEmpty() const;


		T* GetBuffer();
		const T* GetBuffer() const;
		SizeType GetCount() const;


		T& operator[](SizeType index);
		const T& operator[](SizeType index) const;

		operator StringView<T>() const;
	private:
		Memory<T> storage;


		// For Visual Studio's natvis file
		#if defined(COMPILER_MSVC) && defined(DEBUG)
		static constexpr SizeType CharSize = sizeof(T);
		#endif
	};


	template<typename T> String<T> operator+(StringView<T> L, StringView<T> R);
	template<typename T> String<T> operator+(const String<T>& string, StringView<T> view);
	template<typename T> String<T> operator+(StringView<T> view, const String<T>& string);
	template<typename T> String<T> operator+(const String<T>& L, const String<T>& R);

	template<typename T> String<T>& operator+=(String<T>& string, StringView<T> view);
	template<typename T> String<T>& operator+=(String<T>& L, const String<T>& R);


#pragma region Details

	template<typename T>
	String<T>::String()
	{

	}

	template<typename T>
	String<T>::String(SizeType count)
	{
		storage = { count + 1 };

		storage[count] = '\0';
	}

	template<typename T>
	String<T>::String(const T* string)
		: String( StringView<T>(string) )
	{

	}

	template<typename T>
	String<T>::String(StringView<T> view)
	{
		*this = String<T>( view.GetCount() );

		MemoryCopy( GetBuffer(), view.GetBuffer(), view.GetCount() );
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
	typename String<T>::String<T>& String<T>::operator=(String<T>&& other)
	{
		storage = Move( other.storage );

		return *this;
	}

	template<typename T>
	typename String<T>::String<T>& String<T>::operator=(const String<T>& other)
	{
		storage = other.storage;

		return *this;
	}

	template<typename T>
	template<typename U>
	String<T>::String(const U* string)
		: String( StringView<U>(string) )
	{

	}

	template<typename T>
	template<typename U>
	String<T>::String(StringView<U> view)
		: String( String<U>(view) )
	{
	
	}

	template<typename T>
	template<typename U>
	String<T>::String(const String<U>& other)
	{
		using namespace Unicode;


		if constexpr ( TypesAreSame<U, Char32>::Value )
		{
			auto ConvertFromU32String = [](const String<Char32>& string)
				{
					constexpr Encoding E = TypesAreSame<T, Char8>::Value ? Encoding::UTF8 : Encoding::UTF16;


					SizeType count = GetDecodedLength<E>( string.GetBuffer(), string.GetCount() );

					String<T> result(count);

					SizeType offset = 0;
					for (SizeType index = 0; index < string.GetCount(); ++index)
						offset += ToUTF<E>(
							result.GetBuffer() + offset,
							string[index]
						);

					return result;
				};


			*this = ConvertFromU32String(other);
		}

		if constexpr ( TypesAreSame<T, Char32>::Value )
		{
			auto ConvertToU32String = [](const String<U>& string)
				{
					constexpr Encoding E = TypesAreSame<U, Char8>::Value ? Encoding::UTF8 : Encoding::UTF16;


					SizeType count = GetEncodedLength<E>( string.GetBuffer(), string.GetCount() );

					String<Char32> result(count);

					SizeType offset = 0;
					for (SizeType index = 0; index < count; ++index)
						offset += FromUTF<E>(
							result.GetBuffer() + index,
							string.GetBuffer() + offset
						);

					return result;
				};


			*this = ConvertToU32String(other);
		}

		if constexpr (
			( TypesAreSame<T,  Char8>::Value && TypesAreSame<U, Char16>::Value ) ||
			( TypesAreSame<T, Char16>::Value && TypesAreSame<U,  Char8>::Value )
			)
			*this = String<T>( String<Char32>(other) );
	}

	template<typename T>
	Bool String<T>::IsNullOrEmpty() const
	{
		return storage.GetCount() < 2;
	}

	template<typename T>
	T* String<T>::GetBuffer()
	{
		return storage.GetBuffer();
	}

	template<typename T>
	const T* String<T>::GetBuffer() const
	{
		return const_cast<String<T>*>(this)->GetBuffer();
	}

	template<typename T>
	SizeType String<T>::GetCount() const
	{
		return GetBuffer() == nullptr ? 0 : storage.GetCount() - 1;
	}

	template<typename T>
	T& String<T>::operator[](SizeType index)
	{
		return GetBuffer()[index];
	}

	template<typename T>
	const T& String<T>::operator[](SizeType index) const
	{
		return const_cast<String<T>*>(this)->operator[](index);
	}

	template<typename T>
	String<T>::operator StringView<T>() const
	{
		return { GetBuffer(), GetCount() };
	}

	template<typename T>
	String<T> operator+(StringView<T> L, StringView<T> R)
	{
		String<T> result( L.GetCount() + R.GetCount() );

		MemoryCopy( result.GetBuffer(),					L.GetBuffer(),	L.GetCount()	);
		MemoryCopy( result.GetBuffer() + L.GetCount(),	R.GetBuffer(),	R.GetCount()	);

		return result;
	}

	template<typename T>
	String<T> operator+(const String<T>& string, StringView<T> view)
	{
		return static_cast<StringView<T>>(string) + view;
	}

	template<typename T>
	String<T> operator+(StringView<T> view, const String<T>& string)
	{
		return view + static_cast<StringView<T>>(string);
	}

	template<typename T>
	String<T> operator+(const String<T>& L, const String<T>& R)
	{
		return static_cast<StringView<T>>(L) + static_cast<StringView<T>>(R);
	}

	template<typename T>
	String<T>& operator+=(String<T>& string, StringView<T> view)
	{
		return string = string + view;
	}

	template<typename T>
	String<T>& operator+=(String<T>& L, const String<T>& R)
	{
		return L = L + R;
	}

#pragma endregion
}