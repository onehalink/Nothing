#pragma once

#include "../Base.h"



namespace Engine
{
	// Useful constants in different precision
	
	template<typename T> constexpr T Pi				= 3.14159265358979323846; // The well-known 3.14159..
	template<typename T> constexpr T TwoPi			= Pi<T> * 2;
	template<typename T> constexpr T FourPi			= Pi<T> * 4;
	template<typename T> constexpr T HalfPi			= Pi<T> * 0.5;
	template<typename T> constexpr T PiOverThree	= Pi<T> / 3;
	template<typename T> constexpr T PiOverFour		= Pi<T> / 4;

	template<typename T> constexpr T ToDegrees = 180	/ Pi<T>;		// Radians to degrees conversion constant
	template<typename T> constexpr T ToRadians = 1		/ ToDegrees<T>; // Degrees to radians conversion constant

	
	template<typename T>	constexpr T			Epsilon				= 0; // A tiny value
	template<>				constexpr Float32	Epsilon<Float32>	= 1E-6;
	template<>				constexpr Float64	Epsilon<Float64>	= 1E-12;
}


