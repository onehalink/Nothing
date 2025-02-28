#pragma once

#include "Vector.h"



namespace Engine::SDF
{
	ENGINE_API RealType Rectangle(const Vector2& center, const Vector2& halfSize, const Vector2& point);
	ENGINE_API RealType Circle(const Vector2& center, RealType radius, const Vector2& point);

	
	// Bezier curve

	ENGINE_API RealType CalculateTimeForBezierCurve(const Vector2& startPoint, const Vector2& endPoint, const Vector2& point);
	/**
	* @remark
	* Not exactly correct
	*/
	ENGINE_API RealType QuadraticBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& point, RealType time);
	ENGINE_API RealType QuadraticBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& point);
	ENGINE_API RealType CubicBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, const Vector2& point, RealType time);
	ENGINE_API RealType CubicBezierCurve(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, const Vector2& point);


	// Lines union

	ENGINE_API RealType Line(const Vector2& startPoint, const Vector2& endPoint, const Vector2& point);
	ENGINE_API RealType Triangle(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& point);
	// 'X'
	ENGINE_API RealType Cross(RealType lineWidth /** 0 - 1(percent) */, const Vector2& point);
}
