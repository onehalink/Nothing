#pragma once

#include "../Template.h"

#include "Scalar.h"



namespace Engine::Private
{
	ENGINE_API RealType PowerReal(RealType base, RealType exponent);
}


namespace Engine
{
	template<typename T> constexpr T Absolute(T value);
	template<typename T> constexpr T Clamp(T value, T minimum, T maximum);
	template<typename T> constexpr T Clamp01(T value);
	template<typename T, Bool LeftClose = true, Bool RightClose = true> constexpr Bool IsBetween(T value, T minimum, T maximum);
	template<typename T> constexpr Bool IsPowerOfTwo(T value);
	template<typename T> constexpr T Lerp(T from, T to, T amount);
	// Return the largest of two or more
	template<typename First, typename Second, typename ...Parameters> constexpr auto Maximum(First a, Second b, Parameters... parameters);
	// Return the smallest of two or more
	template<typename First, typename Second, typename ...Parameters> constexpr auto Minimum(First a, Second b, Parameters... parameters);
	template<typename T, typename U> constexpr auto Power(T base, U exponent);
	template<typename T> constexpr T Sign(T value);
	template<typename T> Void Swap(T* a, T* b);

	template<typename T> constexpr T Square(T value);
	template<typename T> constexpr T Cubic(T value);
	template<typename T> constexpr T Quadruple(T value);


	ENGINE_API Bool Approximate(RealType a, RealType b, RealType error = Epsilon<RealType>);
	ENGINE_API RealType SquareRoot(RealType value);


#pragma region Details

	template<typename T>
	constexpr T Absolute(T value)
	{
		static_assert( IsSigned<T>::Value || IsFloatPoint<T>::Value );


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
	constexpr T Clamp01(T value)
	{
		return Clamp<T>(value, 0, 1);
	}

	template<typename T, Bool LeftClose, Bool RightClose>
	constexpr Bool IsBetween(T value, T minimum, T maximum)
	{
		using PredicateA = typename Conditional<LeftClose, GreaterEqual<>, Greater<>>::Type;
		using PredicateB = typename Conditional<RightClose,	LessEqual<>, Less<>>::Type;


		return PredicateA()(value, minimum) && PredicateB()(value, maximum);
	}

	template<typename T>
	constexpr Bool IsPowerOfTwo(T value)
	{
		static_assert( IsUnsigned<T>::Value );


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


		if constexpr ( IsIntegral<U>::Value )
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
	Void Swap(T* a, T* b)
	{
		T temporary	= *a;
		*a			= *b;
		*b			= temporary;
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