#pragma once

#include "AsciiSet.h"
#include "Char.h"
#include "Result.h"

#include "Template/IsChar.h"



namespace Engine::Parse
{
	// Converts the string representation of a value to its specific ValueType equivalent
	template<typename ValueType, typename CharType>
	Result<ValueType> Value(const CharType* text)
	{
		static_assert( IsChar<CharType>::Value );
		static_assert( Or<IsIntegral<ValueType>, IsFloatPoint<ValueType>, TypesAreSame<ValueType, Bool>>::Value );


		using namespace Char;


		text = PredefinedAsciiSet::Whitespaces.Skip(text);
		
		if constexpr ( IsArithmetic<ValueType>::Value )
		{
			ValueType sign = 1;
			switch ( *text )
			{
			case '-':
				sign = -1;
			case '+':
				++text;
				break;
			}

			if constexpr ( IsIntegral<ValueType>::Value )
			{
				if ( !IsDecimalDigit( *text ) )
					return { InPlaceIndex<0>(), "Mismatch to integral type"};

				ValueType value = 0;
				while ( IsDecimalDigit( *text ) )
				{
					value *= 10;
					value += *text - '0';

					++text;
				}

				return { InPlaceIndex<1>(), value * sign };
			}

			if constexpr ( IsFloatPoint<ValueType>::Value )
			{
				using IntType = typename Conditional<TypesAreSame<ValueType, Float32>::Value, Int32, Int64>::Type;


				IntType integerPart;
				{
					auto result = Value<IntType>(text);
					if( !result )
						return { InPlaceIndex<0>(), "Mismatch to float point type" };

					integerPart = result.GetValue();
				}

				IntType fractionPart = 0;
				{
					while ( IsDecimalDigit( *text ) ) ++text;

					if ( *text++ == '.' )
						if( auto result = Value<IntType>(text) )
							fractionPart = result.GetValue();
				}

				return { InPlaceIndex<1>(), integerPart + static_cast<ValueType>(fractionPart) / Power( 10, CountDigits(fractionPart) ) * sign };
			}
		}

		if constexpr ( TypesAreSame<ValueType, Bool>::Value )
		{
			switch ( *text )
			{
			case 'f':
			case 'F':
				return { InPlaceIndex<1>(), false};
				break;
			case 't':
			case 'T':
				return { InPlaceIndex<1>(), true };
				break;
			default:
				return { InPlaceIndex<0>(), "Mismatch to bool type" };
			}
		}

		return { InPlaceIndex<0>(), "Not appropriate method to Convert to ValueType" };
	}
}