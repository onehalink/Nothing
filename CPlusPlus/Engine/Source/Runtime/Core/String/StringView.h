#pragma once

#include "../Forward.h"
#include "../NullTerminatedString.h"
#include "../Span.h"



namespace Engine
{
	template<typename T> class StringView;

	using U8StringView = StringView<Char8>;
	using U16StringView = StringView<Char16>;
	using U32StringView = StringView<Char32>;


	template<typename T>
	class StringView : public ReadOnlySpan<T>
	{
	public:
		static_assert( IsChar<T>::Value );


		StringView(const T* string);
		template<typename ...Parameters>
		StringView(Parameters&&... parameters);
	private:
		using Base = ReadOnlySpan<T>;


		// For Visual Studio's natvis file
		#if defined(COMPILER_MSVC) && defined(DEBUG)
		static constexpr SizeType CharSize = sizeof(T);
		#endif
	};


	U8StringView operator""SV(const Char8*, SizeType);
	U8StringView operator""U8SV(const Char8*, SizeType);
	U16StringView operator""U16SV(const Char16*, SizeType);
	U32StringView operator""U32SV(const Char32*, SizeType);


#pragma region Details

	template<typename T>
	StringView<T>::StringView(const T* string)
		: Base( string, NullTerminatedString::Length(string) )
	{

	}

	template<typename T>
	template<typename ...Parameters>
	StringView<T>::StringView(Parameters&&... parameters)
		: Base( Forward<Parameters>(parameters)... )
	{

	}


	inline U8StringView operator""SV(const Char8* string, SizeType length)
	{
		return { string, length };
	}

	inline U8StringView operator""U8SV(const Char8* string, SizeType length)
	{
		return { string, length };
	}

	inline U16StringView operator""U16SV(const Char16* string, SizeType length)
	{
		return { string, length };
	}

	inline U32StringView operator""U32SV(const Char32* string, SizeType length)
	{
		return { string, length };
	}

#pragma endregion
}