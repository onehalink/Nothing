#pragma once

#include "../Base.h"



namespace Engine
{
	template<typename T> constexpr T Pi = 3.14159265358979323846; // The well-known 3.14159..

	template<typename T> constexpr T ToDegrees	= 180 / Pi<T>;		// Radians to degrees conversion constant
	template<typename T> constexpr T ToRadians	= 1 / ToDegrees<T>;	// Degrees to radians conversion constant

	constexpr RealType Epsilon = 1E-6; // A tiny value
}

