#pragma once

#include "Numeric.h"



namespace Engine
{
	class ENGINE_API Angle
	{
	public:
		enum class Unit
		{
			Degree,
			Radian,
		};


		static constexpr Unit DefaultAngleUnit = Unit::Radian;
		

		Angle();
		Angle(RealType value);
		Angle(Unit unit, RealType value);
		Angle(const Angle& other);


		RealType ToDegrees() const;
		RealType ToRadians() const;


		Angle& operator=(const Angle& other);
	private:
		Unit		unit;
		RealType	value;
	};


	ENGINE_API Angle operator-(Angle angle);

	ENGINE_API Angle operator+(Angle L, Angle R);
	ENGINE_API Angle operator-(Angle L, Angle R);
	ENGINE_API Angle operator*(Angle angle, RealType scalar);
	ENGINE_API Angle operator*(RealType scalar, Angle angle);
	ENGINE_API Angle operator/(Angle angle, RealType scalar);

	ENGINE_API Angle& operator+=(Angle& L, Angle R);
	ENGINE_API Angle& operator-=(Angle& L, Angle R);
	ENGINE_API Angle& operator*=(Angle& angle, RealType scalar);
	ENGINE_API Angle& operator/=(Angle& angle, RealType scalar);

	ENGINE_API Bool operator==(Angle L, Angle R);
	ENGINE_API Bool operator!=(Angle L, Angle R);
}