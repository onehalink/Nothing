#include "NumericCalculation.h"

#include <cmath>



namespace Engine
{
	Bool Approximate(RealType a, RealType b, RealType error)
	{
		return Absolute( a - b ) < error;
	}

	RealType Clamp01(RealType value)
	{
		return Clamp<RealType>(value, 0, 1);
	}

	RealType Lerp(RealType from, RealType to, RealType amount)
	{
		return from + ( to - from ) * amount;
	}

	RealType Power(RealType base, RealType exponent)
	{
		return std::pow(base, exponent);
	}

	RealType SquareRoot(RealType value)
	{
		return std::sqrt(value);
	}

	RealType Sine(RealType radians)
	{
		return std::sin(radians);
	}

	RealType Cosine(RealType radians)
	{
		return std::cos(radians);
	}

	RealType Tangent(RealType radians)
	{
		return std::tan(radians);
	}
}