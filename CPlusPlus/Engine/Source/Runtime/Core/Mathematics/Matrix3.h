#pragma once

#include "Matrix.h"



namespace Engine
{
	using Matrix3 = Matrix<3, RealType>;


	// 2D transformation

	ENGINE_API Matrix3 Rotate(Angle angle);
	ENGINE_API Matrix3 Scale(const Vector2& scale);
	ENGINE_API Matrix3 Translate(const Vector2& translation);
}