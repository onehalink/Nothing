#include "Trigonometry.h"

#include <cmath>



namespace Engine
{
	RealType Sine(Angle angle)
	{
		return std::sin( angle.ToRadians() );
	}

	RealType Cosine(Angle angle)
	{
		return std::cos( angle.ToRadians() );
	}

	RealType Tangent(Angle angle)
	{
		return std::tan( angle.ToRadians() );
	}
}
