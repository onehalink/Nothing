#pragma once

#include "ConvertAndParse.h"
#include "Substring.h"



namespace Engine
{
	template<SizeType Size, typename T, typename First, typename ...Parameters>
	String<T> Format(const T( &format )[Size], First&& value, Parameters&&... parameters);
	/**
	* The value's datatype from parameter pack should be String<T>, T*, Int32, Float32 or Bool
	* The count of elements from parameter pack should be equal with the "{}"'s count from format
	* Text included in "{}" is ignored from format, such as "How much {?}!" evaluate to "How much !"
	*
	* Usage:
	* Format("1 + 1 = {}", 2) -> "1 + 1 = 2"
	*/
	template<typename T, typename First, typename ...Parameters>
	String<T> Format(const String<T>& format, First&& value, Parameters&&... parameters);


#pragma region Details

	template<SizeType Size, typename T, typename First, typename ...Parameters>
	String<T> Format(const T( &format )[Size], First&& value, Parameters&&... parameters)
	{
		return Format( String<T>(format), Forward<First>(value), Forward<Parameters>(parameters)... );
	}

	template<typename T, typename First, typename ...Parameters>
	String<T> Format(const String<T>& format, First&& value, Parameters&&... parameters)
	{
		using ValueType = typename RemoveConst<typename RemoveReference<First>::Type>::Type;


		constexpr T Start	= '{';
		constexpr T End		= '}';

		String<T> head = Substring( format, 0,							FindFirst(format, Start)	);
		String<T> tail = Substring( format, FindFirst(format, End) + 1								);

		if constexpr (
			IsIntegral<ValueType>			::Value ||
			IsFloatPoint<ValueType>			::Value ||
			TypesAreSame<ValueType, Bool>	::Value
			)
		{
			constexpr SizeType	size = 32;
			T					buffer[size];


			if constexpr ( IsIntegral<ValueType>::Value )
				TryConvertInt32( buffer, size, Forward<First>(value) );

			if constexpr ( IsFloatPoint<ValueType>::Value )
				TryConvertFloat32( buffer, size, Forward<First>(value) );

			if constexpr ( TypesAreSame<ValueType, Bool>::Value )
				TryConvertBool( buffer, size, Forward<First>(value) );

			String<T> result = head + String<T>(buffer) + tail;

			if constexpr ( sizeof...(parameters) > 0 )
				return Format( result, Forward<Parameters>(parameters)... );

			return result;
		}
		else
		{
			String result = head + String<T>( Forward<First>(value) ) + tail;

			if constexpr ( sizeof...(parameters) > 0 )
				return Format( result, Forward<Parameters>(parameters)... );

			return result;
		}
	}

#pragma endregion
}