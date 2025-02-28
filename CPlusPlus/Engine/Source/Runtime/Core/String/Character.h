#pragma once

#include "../Mathematics/NumericCalculation.h"



namespace Engine
{
	constexpr Char32 NullTerminator			= '\0';
	constexpr Char32 HorizontalTabulation	= '\t';
	constexpr Char32 LineFeed				= '\n';
	constexpr Char32 VerticalTabulation		= '\v';
	constexpr Char32 FormFeed				= '\f';
	constexpr Char32 CarriageReturn			= '\r';
	constexpr Char32 Space					= ' ';

	constexpr Char32 Slash					= '/';
	constexpr Char32 BackSlash				= '\\';


	constexpr Char32 Tab	= HorizontalTabulation;
	constexpr Char32 VTab	= VerticalTabulation;

	constexpr Char32 LF		= LineFeed;
	constexpr Char32 CR		= CarriageReturn;
	constexpr Char32 CRLF	= ( CR << 8 ) | ( LF << 0 );

	#if defined(PLATFORM_WINDOWS)
	constexpr Char32 PreferedPathSeparator = BackSlash;
	#else
	constexpr Char32 PreferedPathSeparator = Slash;
	#endif


	template<Bool Check = false> constexpr Char32 ToLower(Char32 value);
	template<Bool Check = false> constexpr Char32 ToUpper(Char32 value);

	constexpr Bool IsWhitespace(Char32 value);

	constexpr Bool IsLowerCaseLetter(Char32 value);
	constexpr Bool IsUpperCaseLetter(Char32 value);
	constexpr Bool IsLetter(Char32 value);

	constexpr Bool IsBinaryDigit(Char32 value);
	constexpr Bool IsOctalDigit(Char32 value);
	constexpr Bool IsDecimalDigit(Char32 value);
	constexpr Bool IsHexDigit(Char32 value);


#pragma region Details

	template<Bool Check>
	constexpr Char32 ToLower(Char32 value)
	{
		if constexpr (Check)
			if ( !IsUpperCaseLetter(value) )
				return value;

		return value + 0x20;
	}

	template<Bool Check>
	constexpr Char32 ToUpper(Char32 value)
	{
		if constexpr (Check)
			if ( !IsLowerCaseLetter(value) )
				return value;

		return value - 0x20;
	}

	constexpr Bool IsWhitespace(Char32 value)
	{
		return
			value == Tab		||
			value == VTab		||
			value == FormFeed	||
			value == CR			||
			value == Space;
	}

	constexpr Bool IsLowerCaseLetter(Char32 value)
	{
		return IsBetweenClosed<Char32>(value, 'a', 'z');
	}

	constexpr Bool IsUpperCaseLetter(Char32 value)
	{
		return IsBetweenClosed<Char32>(value, 'A', 'Z');
	}

	constexpr Bool IsLetter(Char32 value)
	{
		return IsLowerCaseLetter(value) || IsUpperCaseLetter(value);
	}

	constexpr Bool IsBinaryDigit(Char32 value)
	{
		return IsBetweenClosed<Char32>(value, '0', '1');
	}

	constexpr Bool IsOctalDigit(Char32 value)
	{
		return IsBetweenClosed<Char32>(value, '0', '7');
	}

	constexpr Bool IsDecimalDigit(Char32 value)
	{
		return IsBetweenClosed<Char32>(value, '0', '9');
	}

	constexpr Bool IsHexDigit(Char32 value)
	{
		return IsBetweenClosed<Char32>(value, '0', '9') || IsBetweenClosed<Char32>(value, 'a', 'f') || IsBetweenClosed<Char32>(value, 'A', 'F');
	}

#pragma endregion
}