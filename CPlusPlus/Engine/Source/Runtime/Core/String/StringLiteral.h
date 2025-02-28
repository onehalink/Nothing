#pragma once

#include "../CoreMinimal.h"



namespace Engine
{
	#define STRING_LITERAL(CharType, Text) StringLiteral<CharType>::Select( Text, L ## Text, (typename Conditional<TypesAreSame<decltype(Text), Char8>::Value, Char32, const Char32*>::Type)U ## Text )


	template<typename CharType>
	struct StringLiteral;


	template<>
	struct StringLiteral<Char8>
	{
		static Char8 Select(Char8 value, Char16, Char32) { return value; }
		static const Char8* Select(const Char8* value, const Char16*, const Char32*) { return value; }
	};


	template<>
	struct StringLiteral<Char16>
	{
		static Char16 Select(Char8, Char16 value, Char32) { return value; }
		static const Char16* Select(const Char8*, const Char16* value, const Char32*) { return value; }
	};


	template<>
	struct StringLiteral<Char32>
	{
		static Char32 Select(Char8, Char16, Char32 value) { return value; }
		static const Char32* Select(const Char8*, const Char16*, const Char32* value) { return value; }
	};
}