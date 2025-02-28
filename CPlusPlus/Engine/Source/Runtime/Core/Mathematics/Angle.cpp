#include "Angle.h"



namespace Engine
{
	using Unit = Angle::Unit;


	Angle::Angle()
		: unit(DefaultAngleUnit), value(0)
	{

	}

	Angle::Angle(RealType value)
		: unit(DefaultAngleUnit), value(value)
	{

	}

	Angle::Angle(Unit unit, RealType value)
		: unit(unit), value(value)
	{

	}

	Angle::Angle(const Angle& other)
	{
		unit	= other.unit;
		value	= other.value;
	}

	RealType Angle::ToDegrees() const
	{
		if ( unit == Unit::Degree )
			return value;

		return Engine::ToDegrees<RealType> * value;
	}

	RealType Angle::ToRadians() const
	{
		if ( unit == Unit::Radian )
			return value;

		return Engine::ToRadians<RealType> * value;
	}

	Angle& Angle::operator=(const Angle& other)
	{
		unit	= other.unit;
		value	= other.value;

		return *this;
	}

	Angle operator-(Angle angle)
	{
		if constexpr ( Angle::DefaultAngleUnit == Unit::Degree )
			return -angle.ToDegrees();

		if constexpr ( Angle::DefaultAngleUnit == Unit::Radian )
			return -angle.ToRadians();
	}

	Angle operator+(Angle L, Angle R)
	{
		if constexpr ( Angle::DefaultAngleUnit == Unit::Degree )
			return L.ToDegrees() + R.ToDegrees();

		if constexpr ( Angle::DefaultAngleUnit == Unit::Radian )
			return L.ToRadians() + R.ToRadians();
	}

	Angle operator-(Angle L, Angle R)
	{
		if constexpr ( Angle::DefaultAngleUnit == Unit::Degree )
			return L.ToDegrees() - R.ToDegrees();

		if constexpr ( Angle::DefaultAngleUnit == Unit::Radian )
			return L.ToRadians() - R.ToRadians();
	}

	Angle operator*(Angle angle, RealType scalar)
	{
		if constexpr ( Angle::DefaultAngleUnit == Unit::Degree )
			return angle.ToDegrees() * scalar;

		if constexpr ( Angle::DefaultAngleUnit == Unit::Radian )
			return angle.ToRadians() * scalar;
	}

	Angle operator*(RealType scalar, Angle angle)
	{
		return angle * scalar;
	}

	Angle operator/(Angle angle, RealType scalar)
	{
		if constexpr ( Angle::DefaultAngleUnit == Unit::Degree )
			return angle.ToDegrees() / scalar;

		if constexpr ( Angle::DefaultAngleUnit == Unit::Radian )
			return angle.ToRadians() / scalar;
	}

	Angle& operator+=(Angle& L, Angle R)
	{
		return L = L + R;
	}

	Angle& operator-=(Angle& L, Angle R)
	{
		return L = L - R;
	}

	Angle& operator*=(Angle& angle, RealType scalar)
	{
		return angle *= scalar;
	}

	Angle& operator/=(Angle& angle, RealType scalar)
	{
		return angle /= scalar;
	}

	Bool operator==(Angle L, Angle R)
	{
		if constexpr ( Angle::DefaultAngleUnit == Unit::Degree )
			return Approximate( L.ToDegrees(), R.ToDegrees() );

		if constexpr ( Angle::DefaultAngleUnit == Unit::Radian )
			return Approximate( L.ToRadians(), R.ToRadians() );
	}

	Bool operator!=(Angle L, Angle R)
	{
		return !operator==(L, R);
	}
}