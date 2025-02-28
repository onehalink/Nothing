#pragma once

#include "Macro.h"
#include "Type.h"

#include "Template/AndOrNot.h"
#include "Template/Conditional.h"
#include "Template/Functional.h"
#include "Template/IsArithmetic.h"



namespace Engine
{
	template<typename T> constexpr T Pi			= 3.14159265358979323846;	// The well-known 3.14159..
	template<typename T> constexpr T ToDegrees	= 180 / Pi<T>;				// Radians to degrees conversion constant
	template<typename T> constexpr T ToRadians	= 1 / ToDegrees<T>;			// Degrees to radians conversion constant

	constexpr RealType Epsilon = 1E-6; // A tiny value


	template<typename T> constexpr T Absolute(T value);
	template<typename T> constexpr T Clamp(T value, T minimum, T maximum);
	constexpr RealType Clamp01(RealType value);
	template<Bool LeftClose = true, Bool RightClose = true, typename T, typename U> constexpr Bool IsBetween(T value, U minimum, U maximum);
	template<typename T> constexpr Bool IsPowerOfTwo(T value);
	template<typename T, typename U> constexpr T Lerp(T from, T to, U amount);
	// Return the largest of two or more
	template<typename T, typename U, typename ...Parameters> constexpr auto Maximum(T a, U b, Parameters... parameters);
	// Return the smallest of two or more
	template<typename T, typename U, typename ...Parameters> constexpr auto Minimum(T a, U b, Parameters... parameters);
	template<typename T, typename U> constexpr auto Power(T base, U exponent);
	template<typename T, typename U> constexpr auto Remap(T fromValue, T fromStart, T fromEnd, U toStart, U toEnd);
	constexpr RealType Remap01(RealType value, RealType start, RealType end);
	template<typename T> constexpr T Sign(T value);
	template<typename T> constexpr T Square(T value);
	template<typename T> Void Swap(T* a, T* b);


	ENGINE_API Bool Approximate(RealType a, RealType b, RealType error = Epsilon);
	/**
	* @remark
	* Minimum and maximum are included
	*/
	ENGINE_API RealType Random(RealType minimum, RealType maximum);
	ENGINE_API RealType SquareRoot(RealType value);

	ENGINE_API RealType Sine(RealType radians);
	ENGINE_API RealType Cosine(RealType radians);
	ENGINE_API RealType Tangent(RealType radians);


#pragma region Details

	namespace Private
	{
		ENGINE_API RealType PowerReal(RealType base, RealType exponent);
	}


	template<typename T>
	constexpr T Absolute(T value)
	{
		static_assert( Or<IsSigned<T>, IsFloatPoint<T>>::Value );


		return value < 0 ? -value : value;
	}

	template<typename T>
	constexpr T Clamp(T value, T minimum, T maximum)
	{
		static_assert( IsArithmetic<T>::Value );


		return value < minimum ? minimum :
			value > maximum ? maximum : value;
	}

	constexpr RealType Clamp01(RealType value)
	{
		return Clamp<RealType>(value, 0, 1);
	}

	template<Bool LeftClose, Bool RightClose, typename T, typename U>
	constexpr Bool IsBetween(T value, U minimum, U maximum)
	{
		return
			typename Conditional< LeftClose,	GreaterEqual<>,	Greater<>	>::Type()(value, minimum) &&
			typename Conditional< RightClose,	LessEqual<>,	Less<>		>::Type()(value, maximum);
	}

	template<typename T>
	constexpr Bool IsPowerOfTwo(T value)
	{
		static_assert( IsIntegral<T>::Value );


		return ( value != 0 ) && ( ( value & ( value - 1 ) ) == 0 );
	}

	template<typename T, typename U>
	constexpr T Lerp(T from, T to, U amount)
	{
		static_assert( And<IsArithmetic<T>, IsArithmetic<U>>::Value );


		return from + static_cast<T>( ( to - from ) * amount );
	}

	template<typename T, typename U, typename ...Parameters>
	constexpr auto Maximum(T a, U b, Parameters... parameters)
	{
		static_assert( And<IsArithmetic<T>, IsArithmetic<U>, IsArithmetic<Parameters> ...>::Value );


		auto result = a > b ? a : b;

		if constexpr ( sizeof...(parameters) > 0 )
			return Maximum( result, parameters... );

		return result;
	}

	template<typename T, typename U, typename ...Parameters>
	constexpr auto Minimum(T a, U b, Parameters... parameters)
	{
		static_assert( And<IsArithmetic<T>, IsArithmetic<U>, IsArithmetic<Parameters> ...>::Value );


		auto result = a < b ? a : b;

		if constexpr ( sizeof...(parameters) > 0 )
			return Minimum( result, parameters... );

		return result;
	}

	template<typename T, typename U>
	constexpr auto Power(T base, U exponent)
	{
		static_assert( And<IsArithmetic<T>, IsArithmetic<U>>::Value );


		if constexpr ( IsIntegral<U>::Value )
		{
			U sign		= Sign(exponent);
			exponent	*= sign;

			T result = 1;
			for (SizeType iteration = 0; iteration < exponent; iteration++)
				result *= base;

			return sign == 1 ? result : 1 / result;
		}
		else
			return Private::PowerReal(base, exponent);
	}

	template<typename T, typename U>
	constexpr auto Remap(T fromValue, T fromStart, T fromEnd, U toStart, U toEnd)
	{
		static_assert( And<IsArithmetic<T>, IsArithmetic<U>>::Value );


		return ( fromValue - fromStart ) / ( fromEnd - fromStart ) * ( toEnd - toStart );
	}

	constexpr RealType Remap01(RealType value, RealType start, RealType end)
	{
		return Remap<RealType, RealType>(value, start, end, 0, 1);
	}

	template<typename T>
	constexpr T Sign(T value)
	{
		static_assert( IsArithmetic<T>::Value );


		return value < 0 ? -1 : 1;
	}

	template<typename T>
	constexpr T Square(T value)
	{
		static_assert( IsArithmetic<T>::Value );


		return value * value;
	}

	template<typename T>
	Void Swap(T* a, T* b)
	{
		T temporary	= *a;
		*a			= *b;
		*b			= temporary;
	}

#pragma endregion
}