#pragma once

#include "Rectangle.h"



namespace Engine
{
	struct ENGINE_API Triangle
	{
		Vector2 a;
		Vector2 b;
		Vector2 c;


		RectangleInt CalculateAABB() const;
		Vector3 BarycentricCoordinates(const Vector2& point) const;
		Bool IsInside(const Vector3& barycentricCoordinates, Bool edgeIncluded = false) const;
		Bool IsInside(const Vector2& point, Bool edgeIncluded = false) const;
	};
}