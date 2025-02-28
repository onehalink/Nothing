#include "Trigonometry.h"

#include <cmath>



namespace Engine
{
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
