#pragma once

#include "Matrix.h"



namespace Engine
{
	using Matrix3 = Matrix<3, RealType>;


	ENGINE_API Matrix3 Rotate(RealType radians);
	ENGINE_API Matrix3 Scale(const Vector2& scale);
	ENGINE_API Matrix3 Translate(const Vector2& translation);
}