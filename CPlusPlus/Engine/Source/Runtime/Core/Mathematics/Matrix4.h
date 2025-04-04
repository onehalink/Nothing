#pragma once

#include "Matrix.h"



namespace Engine
{
	using Matrix4 = Matrix<4, RealType>;


	// 3D transformation

	ENGINE_API Matrix4 RotateX(Angle radians);
	ENGINE_API Matrix4 RotateY(Angle radians);
	ENGINE_API Matrix4 RotateZ(Angle radians);
	ENGINE_API Matrix4 Scale(const Vector3& scale);
	ENGINE_API Matrix4 Translate(const Vector3& translation);

	ENGINE_API Matrix4 LookAt(const Vector3& eye, const Vector3& forward, const Vector3& up);

	ENGINE_API Matrix4 OrthographicProjection(RealType left, RealType right, RealType bottom, RealType top, RealType nearZ, RealType farZ);
	ENGINE_API Matrix4 Frustum(RealType left, RealType right, RealType bottom, RealType top, RealType nearZ, RealType farZ);
	ENGINE_API Matrix4 PerspectiveProjection(Angle fovY, RealType aspect, RealType nearZ, RealType farZ);

	ENGINE_API Matrix4 HomogeneousClipSpaceToScreenSpace(RealType width, RealType height);
}
