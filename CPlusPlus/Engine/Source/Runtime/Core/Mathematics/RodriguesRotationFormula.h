#pragma once

#include "Vector.h"



namespace Engine
{
	ENGINE_API Vector3 RodriguesRotationFormula(const Vector3& rotationAxis, RealType radians, const Vector3& point);
}