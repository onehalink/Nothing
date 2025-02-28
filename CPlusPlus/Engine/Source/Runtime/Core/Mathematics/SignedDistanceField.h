#pragma once

#include "Vector.h"



namespace Engine
{
	/**
	* Note:
	* Coordinate's value must be between [0, 1]
	*/

	ENGINE_API RealType DistanceToLine(const Vector2& a, const Vector2& b, const Vector2& point);
	ENGINE_API RealType DistanceToCircle(const Vector2& center, RealType radius, const Vector2& point);

	ENGINE_API RealType CalculateTimeForBezierCurve(const Vector2& startPoint, const Vector2& endPoint, const Vector2& point);
	/**
	* @remark
	* Not exactly correct
	*/
	ENGINE_API RealType DistanceToQuadraticBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& point, RealType time);
	ENGINE_API RealType DistanceToQuadraticBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& point);
	ENGINE_API RealType DistanceToCubicBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, const Vector2& point, RealType time);
	ENGINE_API RealType DistanceToCubicBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, const Vector2& point);
}
