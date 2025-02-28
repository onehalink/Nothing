#pragma once

#include "Buffer.h"
#include "Char.h"
#include "Literal.h"
#include "NullTerminatedString.h"
#include "ParameterPack.h"
#include "Span.h"

#include "Mathematics/Numeric.h"

#include "String/String.h"

#include "Template/AndOrNot.h"
#include "Template/Conditional.h"
#include "Template/IsChar.h"
#include "Template/IsFloatPoint.h"
#include "Template/IsIntegral.h"
#include "Template/TypesAreSame.h"



namespace Engine
{
	// Convert to string representation with '\0' as terminator from a value(ValueType must be integral, float point or bool)
	template<typename CharType, typename ValueType>
	Bool StringCast(Span<CharType> buffer, ValueType value)
	{
		static_assert( IsChar<CharType>::Value );
		static_assert( Or<IsIntegral<ValueType>, IsFloatPoint<ValueType>, TypesAreSame<ValueType, Bool>>::Value );


		CharType* inBuffer	= buffer.GetBuffer();
		SizeType inSize		= buffer.GetCount();

		if constexpr ( IsIntegral<ValueType>::Value )
		{
			if constexpr( IsSigned<ValueType>::Value )
			{
				if ( Sign(value) == -1 )
				{
					if ( inSize == 0 )
						return false;

					*inBuffer = '-';
					++inBuffer;

					--inSize;
				}

				value = Absolute(value);
			}

			SizeType digitCount = CountDigits(value);
			if ( inSize < digitCount + 1 )
				return false;

			for (SizeType index = 0; index < digitCount; ++index)
			{
				ValueType divisor	= Power( 10, digitCount - 1 - index );
				ValueType number	= value / divisor;

				value -= number * divisor;

				inBuffer[index] = '0' + number;
			}

			inBuffer[digitCount] = '\0';
		}

		if constexpr ( IsFloatPoint<ValueType>::Value )
		{
			constexpr ValueType Scale		= 1000000;
			constexpr SizeType ZeroCount	= 6;


			ValueType sign = Sign(value);

			Bool isLessThanOne = Absolute(value) < 1;
			if (isLessThanOne)
				value += sign;

			if ( !StringCast<CharType, typename Conditional<TypesAreSame<ValueType, Float32>::Value, Int32, Int64>::Type>( { inBuffer, inSize - 1 }, value * Scale ) )
				return false;

			SizeType length = NullTerminatedString::Length(inBuffer);

			SizeType dotIndex = length - ZeroCount;
			for (SizeType index = length + 1; index > dotIndex; --index)
				inBuffer[index] = inBuffer[ index - 1 ];

			inBuffer[dotIndex] = '.';

			// trim trailling zeros
			for (SizeType index = length; index > dotIndex + 1; --index)
			{
				if ( inBuffer[index] != '0' )
					break;

				inBuffer[index] = '\0';
			}

			if (isLessThanOne)
				inBuffer[ sign == -1 ? 1 : 0 ] = '0';
		}

		if constexpr ( TypesAreSame<ValueType, Bool>::Value )
		{
			auto Fn = [=](const CharType* text, SizeType size)
				{
					if ( inSize < size )
						return false;

					MemoryCopy(inBuffer, text, size);

					return true;
				};


			if ( !value )
				return Fn( LITERAL(CharType, "false"), 5 + 1 );
		
			return Fn( LITERAL(CharType, "true"), 4 + 1 );
		}

		return true;
	}

	template<typename StringType, SizeType StackAllocatedBufferSize = 64, typename ValueType>
	StringType StringCast(ValueType value)
	{
		using CharType = typename ParameterPack::Nth<ParameterPack::TypeIndex<StringType, U8String, U16String, U32String>::Value, Char8, Char16, Char32>::Type;


		CharType buffer[StackAllocatedBufferSize];
		StringCast( Span<CharType>(buffer, StackAllocatedBufferSize), value );

		return buffer;
	}
}