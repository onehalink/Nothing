#pragma once

#include "Rectangle.h"



namespace Engine
{
	ENGINE_API RectangleInt CalculateAABB(const Vector2& a, const Vector2& b, const Vector2& c);
	ENGINE_API Vector3 BarycentricCoordinates(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& point);
	ENGINE_API Bool IsInside(const Vector3& barycentricCoordinates);
}