#include "Numeric.h"

#include <cmath>
#include <chrono>
#include <random>



namespace Engine
{
	Bool Approximate(RealType a, RealType b, RealType error)
	{
		return Absolute( a - b ) < error;
	}

	RealType Random(RealType minimum, RealType maximum)
	{
		using RandomNumberGenerator	= std::mt19937_64;
		using Distribution			= std::uniform_real_distribution<RealType>;


		RandomNumberGenerator generator;
		generator.seed( std::chrono::high_resolution_clock::now().time_since_epoch().count() );

		return Distribution(minimum, maximum)(generator);
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


namespace Engine::Private
{
	RealType PowerReal(RealType base, RealType exponent)
	{
		return std::pow(base, exponent);
	}
}