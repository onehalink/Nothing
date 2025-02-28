#pragma once

#include "ConvertAndParse.h"
#include "Substring.h"



namespace Engine
{
	/**
	* The value's datatype from parameter pack should be String<T>, T*, Int32, Float32 or Bool
	* The count of elements from parameter pack should be equal with the "{}"'s count from format
	* Text included in "{}" is ignored from format, such as "How much {?}!" evaluate to "How much !"
	*
	* Usage:
	* Format(U8String("1 + 1 = {}"), 2) -> "1 + 1 = 2"
	*/
	template<typename T, typename First, typename ...Parameters>
	String<T> Format(const String<T>& format, First&& value, Parameters&&... parameters);


#pragma region Details

	template<typename T, typename First, typename ...Parameters>
	String<T> Format(const String<T>& format, First&& value, Parameters&&... parameters)
	{
		using ValueType = typename RemoveConst<typename RemoveReference<First>::Type>::Type;


		constexpr T Start	= '{';
		constexpr T End		= '}';


		String<T> head = Substring( format, 0, FindFirst(format, Start) );
		String<T> tail = Substring( format, FindFirst(format, End) + 1 );

		if constexpr (
			IsInteger<ValueType>::Value ||
			IsFloatPoint<ValueType>::Value ||
			TypesAreSame<ValueType, Bool>::Value
			)
		{
			constexpr SizeType Size = 32;


			T buffer[Size];

			if constexpr ( IsInteger<ValueType>::Value )
				TryConvertInt32( buffer, Size, Forward<First>(value) );

			if constexpr ( IsFloatPoint<ValueType>::Value )
				TryConvertFloat32( buffer, Size, Forward<First>(value) );

			if constexpr (TypesAreSame<ValueType, Bool>::Value)
				TryConvertBool( buffer, Size, Forward<First>(value) );

			String<T> ret = head + String<T>(buffer) + tail;
			if constexpr ( sizeof...(parameters) > 0 )
				return Format( ret, Forward<Parameters>(parameters)... );

			return ret;
		}
		else
		{
			String ret = head + String<T>( Forward<First>(value) ) + tail;
			if constexpr ( sizeof...(parameters) > 0 )
				return Format( ret, Forward<Parameters>(parameters)... );

			return ret;
		}
	}

#pragma endregion
}