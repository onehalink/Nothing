#pragma once

#include "Scalar.h"



namespace Engine
{
	template<typename T> constexpr T Absolute(T value);
	template<typename T> constexpr T Clamp(T value, T minimum, T maximum);
	template<typename T> constexpr T IsBetween(T value, T minimum, T maximum, Bool leftClosed, Bool rightClosed);
	template<typename T> constexpr T IsBetweenClosed(T value, T minimum, T maximum);
	template<typename T> constexpr T IsBetweenOpened(T value, T minimum, T maximum);
	template<typename T> constexpr Bool IsPowerOfTwo(T value);
	template<typename First, typename Second, typename ...Parameters> constexpr auto Maximum(First a, Second b, Parameters... parameters);
	template<typename First, typename Second, typename ...Parameters> constexpr auto Minimum(First a, Second b, Parameters... parameters);
	template<typename T> constexpr T Sign(T value);
	template<typename First, typename Second, typename ...Parameters> constexpr auto Sum(First a, Second b, Parameters... parameters);
	template<typename T> Void Swap(T* a, T* b);

	template<typename T> constexpr T Square(T value);
	template<typename T> constexpr T Cubic(T value);
	template<typename T> constexpr T Quadruple(T value);


	ENGINE_API Bool Approximate(RealType a, RealType b, RealType error = Epsilon);
	ENGINE_API RealType Clamp01(RealType value);
	ENGINE_API RealType Lerp(RealType from, RealType to, RealType amount /** between [0, 1] */);
	ENGINE_API RealType Power(RealType base, RealType exponent);
	ENGINE_API RealType SquareRoot(RealType value);

	ENGINE_API RealType Sine(RealType radians);
	ENGINE_API RealType Cosine(RealType radians);
	ENGINE_API RealType Tangent(RealType radians);


#pragma region Details

	template<typename T>
	constexpr T Absolute(T value)
	{
		return value < 0 ? -value : value;
	}

	template<typename T>
	constexpr T Clamp(T value, T minimum, T maximum)
	{
		return value < minimum ? minimum :
			value > maximum ? maximum : value;
	}

	template<typename T>
	constexpr T IsBetween(T value, T minimum, T maximum, Bool leftClosed, Bool rightClosed)
	{
		auto Less		= [](T a, T b) { return a < b; };
		auto LEqual		= [](T a, T b) { return a <= b; };

		auto Greater	= [](T a, T b) { return a > b; };
		auto GEqual		= [](T a, T b) { return a >= b; };

		auto OpA = leftClosed ? GEqual : Greater;
		auto OpB = rightClosed ? LEqual : Less;

		return OpA(value, minimum) && OpB(value, maximum);
	}

	template<typename T>
	constexpr T IsBetweenClosed(T value, T minimum, T maximum)
	{
		return IsBetween(value, minimum, maximum, true, true);
	}

	template<typename T>
	constexpr T IsBetweenOpened(T value, T minimum, T maximum)
	{
		return IsBetween(value, minimum, maximum, false, false);
	}

	template<typename T>
	constexpr Bool IsPowerOfTwo(T value)
	{
		return ( value != 0 ) && !( value & ( value - 1 ) );
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

	template<typename T>
	constexpr T Sign(T value)
	{
		return value < 0 ? -1 : 1;
	}

	template<typename First, typename Second, typename ...Parameters>
	constexpr auto Sum(First a, Second b, Parameters ...parameters)
	{
		auto ret = a + b;

		if constexpr ( sizeof...(parameters) > 0 )
			return Sum( ret, parameters... );

		return ret;
	}

	template<typename T>
	Void Swap(T* a, T* b)
	{
		T temporary	= *a;
		*a			= *b;
		*b			= temporary;
	}

	template<typename T>
	constexpr T Square(T value)
	{
		return value * value;
	}

	template<typename T>
	constexpr T Cubic(T value)
	{
		return value * value * value;
	}

	template<typename T>
	constexpr T Quadruple(T value)
	{
		return value * value * value * value;
	}

#pragma endregion
}