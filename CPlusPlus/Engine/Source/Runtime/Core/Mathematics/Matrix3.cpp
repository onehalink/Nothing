#include "Matrix3.h"



namespace Engine
{
	Matrix3 Rotate(Angle angle)
	{
		RealType sine	= Sine(angle);
		RealType cosine = Cosine(angle);

		return
		{
			cosine,	-sine,	0,
			sine,	cosine, 0,
			0,		0,		1,
		};
	}

	Matrix3 Scale(const Vector2& scale)
	{
		return
		{
			scale[0],	0,			0,
			0,			scale[1],	0,
			0,			0,			1,
		};
	}

	Matrix3 Translate(const Vector2& translation)
	{
		return
		{
			1, 0, translation[0],
			0, 1, translation[1],
			0, 0, 1,
		};
	}
}