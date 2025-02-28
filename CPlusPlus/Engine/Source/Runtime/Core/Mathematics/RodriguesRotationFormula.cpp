#include "RodriguesRotationFormula.h"



namespace Engine
{
	Vector3 RodriguesRotationFormula(const Vector3& rotationAxis, RealType radians, const Vector3& point)
	{
		/**
		* Note:
		* u		= rotationAxis
		* theta	= radians
		* v		= point
		*
		* v' = Cosine(theta) * v + ( 1 - Cosine(theta) ) * Dot(u, v) * u + Sine(theta) * Cross(u, v)
		*/

		Vector3 u		= Normalize(rotationAxis);
		RealType theta	= radians;
		Vector3 v		= point;

		RealType sine	= Sine(theta);
		RealType cosine	= Cosine(theta);

		return cosine * v + ( RealType(1) - cosine ) * Dot(u, v) * u + sine * Cross(u, v);
	}
}