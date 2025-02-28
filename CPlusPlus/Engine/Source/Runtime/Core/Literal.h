#pragma once

#include "Type.h"



#define LITERAL(CharType, Text)	Engine::Private::Literal<CharType>::Select( u8 ## Text, L ## Text, U ## Text )


namespace Engine::Private
{
	template<typename CharType>
	struct Literal;


	template<>
	struct Literal<Char8>
	{
		static Char8 Select(Char8 value, Char16, Char32) { return value; }
		static const Char8* Select(const Char8* value, const Char16*, const Char32*) { return value; }
	};


	template<>
	struct Literal<Char16>
	{
		static Char16 Select(Char8, Char16 value, Char32) { return value; }
		static const Char16* Select(const Char8*, const Char16* value, const Char32*) { return value; }
	};


	template<>
	struct Literal<Char32>
	{
		static Char32 Select(Char8, Char16, Char32 value) { return value; }
		static const Char32* Select(const Char8*, const Char16*, const Char32* value) { return value; }
	};
}