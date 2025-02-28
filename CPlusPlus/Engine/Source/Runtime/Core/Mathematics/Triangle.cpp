#include "Triangle.h"



namespace Engine
{
	RectangleInt Triangle::CalculateAABB() const
	{
		return RectangleInt(
			Minimum( a.x, b.x, c.x ),
			Minimum( a.y, b.y, c.y ),
			Maximum( a.x, b.x, c.x ) + 1, // right and top are excluded
			Maximum( a.y, b.y, c.y ) + 1
		);
	}

	Vector3 Triangle::BarycentricCoordinates(const Vector2& point) const
	{
		RealType areaA = Cross( c - b, point - b );
		RealType areaB = Cross( a - c, point - c );
		RealType areaC = Cross( b - a, point - a );

		RealType sum = areaA + areaB + areaC;

		RealType alpha	= areaA / sum;
		RealType beta	= areaB / sum;
		RealType gamma	= 1 - ( alpha + beta );

		return Vector3{ alpha, beta, gamma };
	}

	Bool Triangle::IsInside(const Vector3& barycentricCoordinates, Bool edgeIncluded) const
	{
		Function<Bool, RealType> Fn = edgeIncluded ?
			[](RealType value) { return value >= 0; } :
			[](RealType value) { return value >  0; };

		
		Bool result = true;
		for (SizeType index = 0; index < 3; index++)
			result &= Fn( barycentricCoordinates[index] );

		return result;
	}

	Bool Triangle::IsInside(const Vector2& point, Bool edgeIncluded) const
	{
		return IsInside( BarycentricCoordinates(point), edgeIncluded );
	}
}