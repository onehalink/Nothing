#pragma once

#include "../Mathematics/Numeric.h"



namespace Engine::Private
{
	inline Bool IsWhitespace(Char32 value)
	{
		return value == '\t' || value == '\v' || value == '\f' || value == '\r' || value == ' ';
	}

	template<typename T>
	const T* SkipWhitespace(const T* pointer)
	{
		while ( IsWhitespace( *pointer ) )
			pointer++;

		return pointer;
	}

	inline Bool IsDecimalDigit(Char32 value)
	{
		return IsBetween<Int32>(value, '0', '9');
	}
}