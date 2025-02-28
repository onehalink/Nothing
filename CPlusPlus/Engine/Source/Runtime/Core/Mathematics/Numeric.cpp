#include "Numeric.h"

#include <cmath>



namespace Engine::Private
{
	RealType PowerReal(RealType base, RealType exponent)
	{
		return std::pow(base, exponent);
	}
}


namespace Engine
{
	Bool Approximate(RealType a, RealType b, RealType error)
	{
		return Absolute( a - b ) < error;
	}

	RealType SquareRoot(RealType value)
	{
		return std::sqrt(value);
	}
}
