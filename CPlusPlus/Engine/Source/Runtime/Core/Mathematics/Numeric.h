#pragma once

#include "../Build.h"
#include "../Type.h"

#include "../Template/AndOrNot.h"
#include "../Template/IsArithmetic.h"
#include "../Template/IsFloatPoint.h"
#include "../Template/IsIntegral.h"



namespace Engine
{
	template<typename T> constexpr T Pi			= 3.14159265358979323846;	// The well-known 3.14159..
	template<typename T> constexpr T ToDegrees	= 180 / Pi<T>;				// Radians to degrees conversion constant
	template<typename T> constexpr T ToRadians	= 1 / ToDegrees<T>;			// Degrees to radians conversion constant

	constexpr RealType Epsilon = 1E-6; // A tiny value


	template<typename T> constexpr T Absolute(T value);
	constexpr Bool Approximate(RealType a, RealType b, RealType error = Epsilon);
	template<typename T> constexpr T Clamp(T value, T minimum, T maximum);
	constexpr RealType Clamp01(RealType value);
	template<typename T> constexpr SizeType CountDigits(T value);
	constexpr SizeType DivideRoundUp(SizeType numerator, SizeType denominator);
	template<Bool StartEndpointIncluded = true, Bool EndEndpointIncluded = true, typename T, typename U> constexpr Bool IsBetween(T value, U startEndpoint, U endEndpoint);
	template<typename T> constexpr T IsPowerOfTwo(T value);
	template<typename T, typename U> constexpr T Lerp(T from, T to, U amount);
	// Return the largest of two or more
	template<typename T, typename U, typename ...Parameters> constexpr auto Maximum(T a, U b, Parameters... parameters);
	// Return the smallest of two or more
	template<typename T, typename U, typename ...Parameters> constexpr auto Minimum(T a, U b, Parameters... parameters);
	template<typename T, typename U> constexpr auto Power(T base, U exponent);
	template<typename T, typename U> constexpr U Remap(T fromValue, T fromStart, T fromEnd, U toStart, U toEnd);
	constexpr RealType Remap01(RealType value, RealType start, RealType end);
	template<typename T> constexpr T Sign(T value);
	template<typename T> constexpr T Square(T value);
	constexpr RealType SquareRoot(RealType value);
	template<typename T> Void Swap(T* a, T* b);


#pragma region Details

	namespace Private
	{
		ENGINE_API RealType PowerReal(RealType base, RealType exponent);
	}


	template<typename T>
	constexpr T Absolute(T value)
	{
		static_assert( IsArithmetic<T>::Value );


		if constexpr ( IsUnsigned<T>::Value )
			return value;
		else
			return value < 0 ? -value : value;
	}

	constexpr Bool Approximate(RealType a, RealType b, RealType error)
	{
		return Absolute( a - b ) < error;
	}

	template<typename T>
	constexpr T Clamp(T value, T minimum, T maximum)
	{
		static_assert( IsArithmetic<T>::Value );


		return
			value < minimum ? minimum :
			value > maximum ? maximum : value;
	}

	template<typename T>
	constexpr SizeType CountDigits(T value)
	{
		static_assert( IsIntegral<T>::Value );


		value = Absolute(value);

		SizeType result = 1;
		while ( value >= 10 )
		{
			value /= 10;

			++result;
		}

		return result;
	}

	constexpr RealType Clamp01(RealType value)
	{
		return Clamp<RealType>(value, 0, 1);
	}

	constexpr SizeType DivideRoundUp(SizeType numerator, SizeType denominator)
	{
		return ( numerator + denominator - 1 ) / denominator;
	}

	template<Bool StartEndpointIncluded, Bool EndEndpointIncluded, typename T, typename U>
	constexpr Bool IsBetween(T value, U startEndpoint, U endEndpoint)
	{
		//static_assert( And<IsArithmetic<T>, IsArithmetic<U>>::Value );


		if( value < startEndpoint || value > endEndpoint )
			return false;

		if constexpr ( !StartEndpointIncluded )
			if ( value == startEndpoint )
				return false;

		if constexpr ( !EndEndpointIncluded )
			if ( value == endEndpoint )
				return false;

		return true;
	}

	template<typename T>
	constexpr T IsPowerOfTwo(T value)
	{
		static_assert( IsUnsigned<T>::Value );


		return ( value != 0 ) && !( value & ( value - 1 ) );
	}

	template<typename T, typename U>
	constexpr T Lerp(T from, T to, U amount)
	{
		static_assert( And<IsArithmetic<T>, IsFloatPoint<U>>::Value );


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
			for (SizeType iteration = 0; iteration < exponent; ++iteration)
				result *= base;

			return sign == 1 ? result : 1 / result;
		}
		else
			return Private::PowerReal(base, exponent);
	}

	template<typename T, typename U>
	constexpr U Remap(T fromValue, T fromStart, T fromEnd, U toStart, U toEnd)
	{
		static_assert( And<IsArithmetic<T>, IsArithmetic<U>>::Value );


		T distanceFrom	= fromEnd	- fromStart;
		T advanceFrom	= fromValue - fromStart;

		U distanceTo	= toEnd - toStart;

		return advanceFrom / distanceFrom * distanceTo + toStart;
	}

	constexpr RealType Remap01(RealType value, RealType start, RealType end)
	{
		return Remap<RealType, RealType>(value, start, end, 0, 1);
	}

	template<typename T>
	constexpr T Sign(T value)
	{
		static_assert( IsArithmetic<T>::Value );


		if constexpr ( IsUnsigned<T>::Value )
			return 1;
		else
			return value < 0 ? -1 : 1;
	}

	template<typename T>
	constexpr T Square(T value)
	{
		static_assert( IsArithmetic<T>::Value );


		return value * value;
	}

	constexpr RealType SquareRoot(RealType value)
	{
		/**
		* F(x)	= x^2 - y
		* F'(x) = 2x
		*
		* x0 = value / 2 // initial value
		*
		* F(x) - F(x0) = F'(x0)(x - x0)
		*
		* Iteration Formula(when F(x) == 0):
		* x = x0 - F(x0)/F'(x0)
		*	= x0 - (x0 * x0 - y) / (2 * x0)
		*	= (x0 * x0 + y) / (2 * x0)
		*	= (x0 + y / x0) / 2
		*/

		constexpr SizeType IterationLimit = 32;


		SizeType iteration = 0;

		RealType x		= value / 2; // initial value
		RealType last	= 0;

		while ( iteration < IterationLimit )
		{
			x = ( x + value / x ) / 2;

			if ( Approximate(x, last) )
				return x;

			last = x;

			++iteration;
		}
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