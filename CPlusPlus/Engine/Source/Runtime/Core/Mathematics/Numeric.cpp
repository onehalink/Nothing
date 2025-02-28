#include "Numeric.h"

#include <cmath>



namespace Engine::Private
{
	RealType PowerReal(RealType base, RealType exponent)
	{
		return std::pow(base, exponent);
	}
}