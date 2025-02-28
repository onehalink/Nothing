#pragma once

#include "Find.h"
#include "_Helper.h"



namespace Engine
{
	template<typename T> Bool TryConvertInt32(T* inBuffer, SizeType inSize, Int32 value);
	template<typename T> Bool TryConvertFloat32(T* inBuffer, SizeType inSize, Float32 value);
	template<typename T> Bool TryConvertBool(T* inBuffer, SizeType inSize, Bool value);

	template<typename T> Bool TryParseInt32(Int32* outputResult, const T* string);
	template<typename T> Bool TryParseFloat32(Float32* outputResult, const T* string);
	template<typename T> Bool TryParseBool(Bool* outputResult, const T* string);


#pragma region Details

	template<typename T>
	Bool TryConvertInt32(T* inBuffer, SizeType inSize, Int32 value)
	{
		Int32 sign = Sign(value);
		if ( sign == -1 )
		{
			if ( inSize == 0 )
				return false;

			*inBuffer = '-';
			inBuffer++;

			inSize--;
		}

		value = Absolute(value);

		SizeType digitCount = Private::GetDigitCount(value);
		if ( inSize < digitCount + 1 )
			return false;

		for (SizeType index = 0; index < digitCount; index++)
		{
			Int32 divisor	= Power( 10, digitCount - 1 - index );
			Int32 number	= value / divisor;

			value -= number * divisor;

			inBuffer[index] = '0' + number;
		}

		inBuffer[digitCount] = '\0';

		return true;
	}

	template<typename T>
	Bool TryConvertFloat32(T* inBuffer, SizeType inSize, Float32 value)
	{
		constexpr RealType Scale		= 100000;
		constexpr SizeType ZeroCount	= 5;


		Float32 sign = Sign(value);

		Bool isLessThanOne = Absolute(value) < 1;
		if (isLessThanOne)
			value += sign;

		if ( !TryConvertInt32( inBuffer, inSize - 1, value * Scale ) )
			return false;

		SizeType length = StringLength(inBuffer);

		SizeType dotIndex = length - ZeroCount;
		for (SizeType index = length + 1; index > dotIndex; index--)
			inBuffer[index] = inBuffer[ index - 1 ];

		inBuffer[dotIndex] = '.';

		// trim trailling zeros
		for (SizeType index = length; index > dotIndex + 1; index--)
		{
			if ( inBuffer[index] != '0' )
				break;

			inBuffer[index] = '\0';
		}

		if (isLessThanOne)
			inBuffer[ sign == -1 ? 1 : 0 ] = '0';

		return true;
	}

	template<typename T>
	Bool TryConvertBool(T* inBuffer, SizeType inSize, Bool value)
	{
		auto Fn = [=](const Char8* text, SizeType size)
			{
				if ( inSize < size )
					return false;

				for (SizeType index = 0; index < size; index++)
					inBuffer[index] = text[index];

				return true;
			};


		if ( !value )
			return Fn( "false", 5 + 1 );
		
		return Fn( "true", 4 + 1 );
	}

	template<typename T>
	Bool TryParseInt32(Int32* outputResult, const T* string)
	{
		using namespace Private;


		string = SkipWhitespace(string);

		Int32 sign = 1;
		switch (*string)
		{
		case '-':
			sign = -1;
		case '+':
			string++;
			break;
		}

		if ( !IsDigit( *string ) )
			return false;

		Int32 value = 0;
		while ( IsDigit( *string ) )
		{
			value *= 10;
			value += *string - '0';

			string++;
		}

		if (outputResult)
			*outputResult = value * sign;

		return true;
	}

	template<typename T>
	Bool TryParseFloat32(Float32* outputResult, const T* string)
	{
		Int32 integerPart;
		if ( !TryParseInt32( &integerPart, string ) )
			return false;

		Int32 fractionPart = 0;
		{
			Int32 dotIndex = FindFirst<T>(string, '.');
			if ( dotIndex != -1 )
			{
				string += dotIndex + 1;
				TryParseInt32( &fractionPart, string );
			}
		}

		if (outputResult)
			*outputResult = integerPart + static_cast<Float32>(fractionPart) / Power( 10, Private::GetDigitCount(fractionPart) ) * Sign(integerPart);

		return true;
	}

	template<typename T>
	Bool TryParseBool(Bool* outputResult, const T* string)
	{
		string = Private::SkipWhitespace(string);

		Bool value;
		switch ( *string )
		{
		case 'f':
		case 'F':
			value = false;
			break;
		case 't':
		case 'T':
			value = true;
			break;
		default:
			return false;
		}

		if (outputResult)
			*outputResult = value;

		return true;
	}

#pragma endregion
}