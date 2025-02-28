#include "SignedDistanceField.h"



namespace Engine
{
	RealType DistanceToLine(const Vector2& a, const Vector2& b, const Vector2& point)
	{
		Vector2 direction	= b - a;
		Vector2 normal		= { -direction.y, direction.x };

		return Dot( Normalize(normal), point - a );
	}

	RealType DistanceToCircle(const Vector2& center, RealType radius, const Vector2& point)
	{
		return radius - SquareRoot( Square( point.x - center.x ) + Square( point.y - center.y ) );
	}

	RealType CalculateTimeForBezierCurve(const Vector2& startPoint, const Vector2& endPoint, const Vector2& point)
	{
		Vector2 direction = endPoint - startPoint;

		return Clamp01( Dot( direction, point - startPoint ) / Dot(direction, direction) );
	}

	RealType DistanceToQuadraticBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& point, RealType time)
	{
		Vector2 p0 = Lerp(a, b, time);
		Vector2 p1 = Lerp(b, c, time);

		return DistanceToLine(p0, p1, point);
	}

	RealType DistanceToQuadraticBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& point)
	{
		return DistanceToQuadraticBezierCurve( a, b, c, point, CalculateTimeForBezierCurve(a, c, point) );
	}

	RealType DistanceToCubicBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, const Vector2& point, RealType time)
	{
		Vector2 p0 = Lerp(a, b, time);
		Vector2 p1 = Lerp(b, c, time);
		Vector2 p2 = Lerp(c, d, time);
		Vector2 q0 = Lerp(p0, p1, time);
		Vector2 q1 = Lerp(p1, p2, time);

		return DistanceToLine(q0, q1, point);
	}

	RealType DistanceToCubicBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, const Vector2& point)
	{
		return DistanceToCubicBezierCurve( a, b, c, d, point, CalculateTimeForBezierCurve(a, d, point) );
	}
}