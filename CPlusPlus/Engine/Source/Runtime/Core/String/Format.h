#pragma once

#include "../CoreMinimal.h"
#include "../StringCast.h"

#include "Find.h"
#include "String.h"
#include "StringBuilder.h"
#include "StringView.h"



namespace Engine
{
	/**
	* The value's datatype from parameter pack must be string(const CharType*, StringView<T>, String<T>), integral(signed/unsigned integer), float point(Float32, Float64) or boolean(Bool)
	* The count of elements from parameter pack should be equal with the "{}"'s count from format
	* Text included in "{}" is ignored from format, such as "How much {?}!" evaluate to "How much !"
	*
	* Example:
	* Format("1 + 1 = {}"U8SV, 2) -> "1 + 1 = 2"
	*/
	template<typename T, typename ...Parameters>
	String<T> Format(StringView<T> format, Parameters&&... parameters);


#pragma region Details

	namespace Private
	{
		template<typename T, typename First, typename ...Parameters>
		Void FormatHelper(StringBuilder<T>& output, StringView<T> format, First&& value, Parameters&&... parameters)
		{
			using ValueType = typename RemoveAllQualifiers<First>::Type;


			constexpr T Start	= '{';
			constexpr T End		= '}';


			auto head = format.Slice( 0, FindFirstChar(format, Start) );
			auto tail = format.Slice( FindFirstChar(format, End) + 1 );

			output.Append(head);

			if constexpr ( Or<IsIntegral<ValueType>, IsFloatPoint<ValueType>, TypesAreSame<ValueType, Bool>>::Value )
			{
				T buffer[32];
				StringCast<T, ValueType>( { buffer, CountArray(buffer) }, value);

				output.Append( reinterpret_cast<const T*>(buffer) );
			}
			else
				output.Append( Forward<First>(value) );

			if constexpr ( sizeof...(parameters) > 0 )
				FormatHelper<T, Parameters...>( output, tail, Forward<Parameters>(parameters)... );
			else
				output.Append(tail);
		}
	}


	template<typename T, typename ...Parameters>
	String<T> Format(StringView<T> format, Parameters&&... parameters)
	{
		static_assert( sizeof...(parameters) > 0 );


		StringBuilder<T> result;
		Private::FormatHelper( result, format, Forward<Parameters>(parameters)... );

		return result.ToString();
	}

#pragma endregion
}
