#include "Triangle.h"



namespace Engine
{
	RectangleInt CalculateAABB(const Vector2& a, const Vector2& b, const Vector2& c)
	{
		return RectangleInt(
			Minimum( a.x, b.x, c.x ),
			Minimum( a.y, b.y, c.y ),
			Maximum( a.x, b.x, c.x ) + 1, // right and top are excluded
			Maximum( a.y, b.y, c.y ) + 1
		);
	}

	Vector3 BarycentricCoordinates(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& point)
	{
		RealType areaA = Cross( c - b, point - b );
		RealType areaB = Cross( a - c, point - c );
		RealType areaC = Cross( b - a, point - a );

		RealType sum = areaA + areaB + areaC;

		RealType alpha	= areaA / sum;
		RealType beta	= areaB / sum;
		RealType gamma	= 1 - ( alpha + beta );

		return { alpha, beta, gamma };
	}

	Bool IsInside(const Vector3& barycentricCoordinates)
	{
		Bool ret = true;
		for (SizeType index = 0; index < 3; index++)
			ret &= barycentricCoordinates[index] > 0;

		return ret;
	}
}