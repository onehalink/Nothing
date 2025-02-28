#pragma once

#include "../Base.h"

#include "../Template/FunctionPointer.h"
#include "../Template/IsArithmetic.h"



namespace Engine
{
	constexpr RealType Pi			= 3.14159265358979323846;	// The well-known 3.14159..
	constexpr RealType ToDegrees	= 180 / Pi;					// Radians to degrees conversion constant
	constexpr RealType ToRadians	= 1 / ToDegrees;			// Degrees to radians conversion constant

	constexpr RealType Epsilon		= 1E-6; // A tiny value


	template<typename T> constexpr T Absolute(T value);
	template<typename T> constexpr T Clamp(T value, T minimum, T maximum);
	template<typename T> constexpr Bool IsBetween(T value, T minimum, T maximum, Bool leftClosed = true, Bool rightClosed = true);
	template<typename T> constexpr Bool IsPowerOfTwo(T value);
	template<typename T> constexpr T Lerp(T from, T to, T amount);
	// Return the largest of two or more
	template<typename First, typename Second, typename ...Parameters> constexpr auto Maximum(First a, Second b, Parameters... parameters);
	// Return the smallest of two or more
	template<typename First, typename Second, typename ...Parameters> constexpr auto Minimum(First a, Second b, Parameters... parameters);
	template<typename T, typename U> constexpr auto Power(T base, U exponent);
	template<typename T> constexpr T Sign(T value);


	template<typename T> constexpr T Square(T value);
	template<typename T> constexpr T Cubic(T value);
	template<typename T> constexpr T Quadruple(T value);


	ENGINE_API Bool Approximate(RealType a, RealType b, RealType error = Epsilon);
	ENGINE_API RealType Clamp01(RealType value);
	// Minimum and maximum are included
	ENGINE_API RealType Random(RealType minimum, RealType maximum);
	ENGINE_API RealType SquareRoot(RealType value);

	ENGINE_API RealType Sine(RealType radians);
	ENGINE_API RealType Cosine(RealType radians);
	ENGINE_API RealType Tangent(RealType radians);


#pragma region Details

	namespace Private
	{
		RealType PowerReal(RealType base, RealType exponent);
	}


	template<typename T>
	constexpr T Absolute(T value)
	{
		static_assert( IsSignedInteger<T>::Value || IsFloatPoint<T>::Value );


		return value < 0 ? -value : value;
	}

	template<typename T>
	constexpr T Clamp(T value, T minimum, T maximum)
	{
		static_assert( IsArithmetic<T>::Value );


		return value < minimum ? minimum :
			value > maximum ? maximum : value;
	}

	template<typename T>
	constexpr Bool IsBetween(T value, T minimum, T maximum, Bool leftClosed, Bool rightClosed)
	{
		static_assert( IsArithmetic<T>::Value );


		Function<Bool, T, T> Less		= [](T a, T b) { return a  < b; };
		Function<Bool, T, T> LEqual		= [](T a, T b) { return a <= b; };

		Function<Bool, T, T> Greater	= [](T a, T b) { return a  > b; };
		Function<Bool, T, T> GEqual		= [](T a, T b) { return a >= b; };


		Function<Bool, T, T> OpA = leftClosed	? GEqual : Greater;
		Function<Bool, T, T> OpB = rightClosed	? LEqual : Less;

		return OpA(value, minimum) && OpB(value, maximum);
	}

	template<typename T>
	constexpr Bool IsPowerOfTwo(T value)
	{
		static_assert( IsUnsignedInteger<T>::Value );


		return ( value != 0 ) && ( ( value & ( value - 1 ) ) != 0 );
	}

	template<typename T>
	constexpr T Lerp(T from, T to, T amount)
	{
		static_assert( IsFloatPoint<T>::Value );


		return from + ( to - from ) * amount;
	}

	template<typename First, typename Second, typename ...Parameters>
	constexpr auto Maximum(First a, Second b, Parameters ...parameters)
	{
		auto ret = a > b ? a : b;

		if constexpr ( sizeof...(parameters) > 0 )
			return Maximum( ret, parameters... );

		return ret;
	}

	template<typename First, typename Second, typename ...Parameters>
	constexpr auto Minimum(First a, Second b, Parameters ...parameters)
	{
		auto ret = a < b ? a : b;

		if constexpr ( sizeof...(parameters) > 0 )
			return Minimum( ret, parameters... );

		return ret;
	}

	template<typename T, typename U>
	constexpr auto Power(T base, U exponent)
	{
		static_assert( IsArithmetic<T>::Value && IsArithmetic<U>::Value );


		if constexpr ( IsInteger<U>::Value )
		{
			U sign		= Sign(exponent);
			exponent	*= sign;

			T ret = 1;
			for (SizeType iteration = 0; iteration < exponent; iteration++)
				ret *= base;

			return sign ? ret : 1 / ret;
		}
		else
			return Private::PowerReal(base, exponent);
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
	constexpr T Cubic(T value)
	{
		static_assert( IsArithmetic<T>::Value );


		return value * value * value;
	}

	template<typename T>
	constexpr T Quadruple(T value)
	{
		static_assert( IsArithmetic<T>::Value );


		return value * value * value * value;
	}

#pragma endregion
}