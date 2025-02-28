#include "SignedDistanceField.h"

#include "Trigonometry.h"



namespace Engine::SDF
{
	RealType Rectangle(const Vector2& center, const Vector2& halfSize, const Vector2& point)
	{
		Vector2 distance = Absolute( point - center ) - halfSize;

		RealType innerDistance	= Minimum( Maximum( distance.x, distance.y ), 0 );
		Vector2 outerDistance	= Maximum( distance, Vector2::Zero );

		return Magnitude(outerDistance) + innerDistance;
	}

	RealType Circle(const Vector2& center, RealType radius, const Vector2& point)
	{
		return Magnitude( point - center ) - radius;
	}

	RealType Line(const Vector2& startPoint, const Vector2& endPoint, const Vector2& point)
	{
		Vector2 direction	= endPoint - startPoint;
		Vector2 normal		= { -direction.y, direction.x };

		return Dot( Normalize(normal), point - startPoint );
	}

	RealType CalculateTimeForBezierCurve(const Vector2& startPoint, const Vector2& endPoint, const Vector2& point)
	{
		Vector2 direction = endPoint - startPoint;

		return Clamp01( Dot( direction, point - startPoint ) / Dot(direction, direction) );
	}

	RealType QuadraticBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& point, RealType time)
	{
		Vector2 p0 = Lerp(a, b, time);
		Vector2 p1 = Lerp(b, c, time);

		return Line(p0, p1, point);
	}

	RealType QuadraticBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& point)
	{
		return QuadraticBezierCurve( a, b, c, point, CalculateTimeForBezierCurve(a, c, point) );
	}

	RealType CubicBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, const Vector2& point, RealType time)
	{
		Vector2 p0 = Lerp(a, b, time);
		Vector2 p1 = Lerp(b, c, time);
		Vector2 p2 = Lerp(c, d, time);
		Vector2 q0 = Lerp(p0, p1, time);
		Vector2 q1 = Lerp(p1, p2, time);

		return Line(q0, q1, point);
	}

	RealType CubicBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, const Vector2& point)
	{
		return CubicBezierCurve( a, b, c, d, point, CalculateTimeForBezierCurve(a, d, point) );
	}

	RealType Triangle(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& point)
	{
		return
			Maximum(
				Line(B, A, point),
				Line(C, B, point),
				Line(A, C, point)
			);
	}

	RealType Cross(RealType lineWidth, const Vector2& point)
	{
		RealType unit = lineWidth * Sine( Pi<RealType> / 4 );

		Vector2 A = { unit,		0			};
		Vector2 B = { 1,		1 - unit	};
		Vector2 C = { 1 - unit,	1			};
		Vector2 D = { 0,		unit		};

		Vector2 E = { 1 - unit,	0			};
		Vector2 F = { 1,		unit		};
		Vector2 G = { unit,		1			};
		Vector2 H = { 0,		1 - unit	};

		return
			Minimum(
				Maximum(
					Line(B, A, point),
					Line(C, B, point),
					Line(D, C, point),
					Line(A, D, point)
				),
				Maximum(
					Line(F, E, point),
					Line(G, F, point),
					Line(H, G, point),
					Line(E, H, point)
				)
			);
	}
}
