#pragma once

#include "../Mathematics/NumericCalculation.h"

#include "Find.h"



namespace Engine
{
	template<typename T> Bool TryConvertInt32(T* inBuffer, SizeType inSize, Int32 value);
	template<typename T> Bool TryConvertFloat32(T* inBuffer, SizeType inSize, Float32 value);
	template<typename T> Bool TryConvertBool(T* inBuffer, SizeType inSize, Bool value);

	template<typename T> Bool TryParseInt32(Int32* outputResult, const T* rawString);
	template<typename T> Bool TryParseFloat32(Float32* outputResult, const T* rawString);
	template<typename T> Bool TryParseBool(Bool* outputResult, const T* rawString);


#pragma region Details

	namespace Private
	{
		inline Bool IsDecimalDigit(Char32 value)
		{
			return IsBetween<Int32>(value, '0', '9');
		}
	}


	template<typename T>
	Bool TryConvertInt32(T* inBuffer, SizeType inSize, Int32 value)
	{
		Int32 sign	= Sign(value);
		value		= Absolute(value);

		if ( sign == -1 )
		{
			if ( inSize == 0 )
				return false;

			*inBuffer = '-';

			inBuffer++;
			inSize--;
		}

		SizeType digits = 1;
		{
			Int32 temporary = value;
			while ( temporary >= 10 )
			{
				temporary /= 10;

				digits++;
			}
		}

		if ( inSize < digits + 1 )
			return false;

		for (SizeType index = 0; index < digits; index++)
		{
			Int32 divisor = Power( 10, digits - 1 - index );

			Int32 number	= value / divisor;
			value			-= number * divisor;

			inBuffer[index] = '0' + number;
		}

		inBuffer[digits] = '\0';

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
	Bool TryParseInt32(Int32* outputResult, const T* rawString)
	{
		using namespace Private;


		auto p = SkipWhitespace(rawString);
		Int32 sign = 1;
		switch ( *p )
		{
		case '-':
			sign = -1;
		case '+':
			p++;
			break;
		}

		if ( !IsDecimalDigit( *p ) )
			return false;

		Int32 value = 0;
		while ( IsDecimalDigit( *p ) )
		{
			value *= 10;
			value += *p - '0';

			p++;
		}

		if (outputResult)
			*outputResult = value * sign;

		return true;
	}

	template<typename T>
	Bool TryParseFloat32(Float32* outputResult, const T* rawString)
	{
		using namespace Private;


		auto p = SkipWhitespace(rawString);

		Int32 integerPart;
		if ( !TryParseInt32( &integerPart, rawString ) )
			return false;

		Float32 fractionPart;
		{
			Int32 numerator		= 0;
			Int32 denominator	= 1;

			Int32 dotIndex = FindFirst<T>(rawString, '.');
			if ( dotIndex != -1 )
			{
				p += dotIndex + 1;

				while ( IsDecimalDigit( *p ) )
				{
					numerator *= 10;
					numerator += *p - '0';

					denominator *= 10;

					p++;
				}
			}

			fractionPart = static_cast<Float32>(numerator) / denominator;
		}

		if (outputResult)
			*outputResult = integerPart + fractionPart * Sign(integerPart);

		return true;
	}

	template<typename T>
	Bool TryParseBool(Bool* outputResult, const T* rawString)
	{
		auto p = Private::SkipWhitespace(rawString);

		Bool value;
		switch ( *p )
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