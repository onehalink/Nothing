#pragma once

#include "Vector.h"



namespace Engine
{
	template<Dimension D, typename T> Vector<D, T> BezierCurve(Vector<D, T>* controlPoints, SizeType count, RealType time);

#pragma region Details

	template<Dimension D, typename T>
	Vector<D, T> BezierCurve(Vector<D, T>* controlPoints, SizeType count, RealType time)
	{
		if ( count == 1 )
			return controlPoints[0];

		for (SizeType index = 1; index < count; index++)
		{
			SizeType begin	= index - 1;
			SizeType end	= index;

			controlPoints[begin] = Lerp( controlPoints[begin], controlPoints[end], time );
		}

		return BezierCurve( controlPoints, count - 1, time );
	}

#pragma endregion
}