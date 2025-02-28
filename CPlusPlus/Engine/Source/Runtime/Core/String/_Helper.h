#pragma once

#include "../CoreMinimal.h"



namespace Engine::Private
{
	inline Bool IsDigit(Char8 value)
	{
		return IsBetween(value, '0', '9');
	}

	inline Bool IsWhitespace(Char8 value)
	{
		return value == '\t' || value == '\v' || value == '\f' || value == '\r' || value == ' ';
	}

	template<typename T>
	const T* SkipWhitespace(const T* string)
	{
		while ( IsWhitespace( *string ) )
			string++;

		return string;
	}

	inline SizeType GetDigitCount(Int32 value)
	{
		SizeType result = 1;
		while ( value >= 10 )
		{
			value /= 10;

			result++;
		}

		return result;
	}
}