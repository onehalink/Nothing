#include "Matrix4.h"

#include "Trigonometry.h"



namespace Engine
{
	Matrix4 RotateX(RealType radians)
	{
		RealType sine	= Sine(radians);
		RealType cosine = Cosine(radians);

		return
		{
			1, 0,		0,		0,
			0, cosine,	-sine,	0,
			0, sine,	cosine,	0,
			0, 0,		0,		1,
		};
	}

	Matrix4 RotateY(RealType radians)
	{
		RealType sine	= Sine(radians);
		RealType cosine = Cosine(radians);

		return
		{
			cosine,	0, sine,	0,
			0,		1, 0,		0,
			-sine,	0, cosine,	0,
			0,		0, 0,		1,
		};
	}

	Matrix4 RotateZ(RealType radians)
	{
		RealType sine	= Sine(radians);
		RealType cosine = Cosine(radians);

		return
		{
			cosine,	-sine,	0, 0,
			sine,	cosine,	0, 0,
			0,		0,		1, 0,
			0,		0,		0, 1,
		};
	}

	Matrix4 Scale(const Vector3& scale)
	{
		return
		{
			scale[0],	0,			0,			0,
			0,			scale[1],	0,			0,
			0,			0,			scale[2],	0,
			0,			0,			0,			1,
		};
	}

	Matrix4 Translate(const Vector3& translation)
	{
		return
		{
			1, 0, 0, translation[0],
			0, 1, 0, translation[1],
			0, 0, 1, translation[2],
			0, 0, 0, 1,
		};
	}

	Matrix4 LookAt(const Vector3& eye, const Vector3& forward, const Vector3& up)
	{
		Vector3 g	= Normalize(forward);	// gaze direction, -z axis
		Vector3 t	= Normalize(up);		// top direction, y axis
		Vector3 gxt	= Cross(g, t);			// right direction, x axis

		Vector4 r0 = { gxt,	0 };
		Vector4 r1 = { t,	0 };
		Vector4 r2 = { -g,	0 };

		Matrix4 R = Matrix4::Identity;
		R.SetRow(0, r0);
		R.SetRow(1, r1);
		R.SetRow(2, r2);

		return R * Translate( -eye );
	}

	Matrix4 OrthographicProjection(RealType left, RealType right, RealType bottom, RealType top, RealType nearZ, RealType farZ)
	{
		Matrix4 T = Translate(
			Vector3
			{
				( right	+ left		) / 2 * -1,
				( top	+ bottom	) / 2 * -1,
				( nearZ	+ farZ		) / 2 * -1,
			}
		);

		Matrix4 S = Scale(
			Vector3
			{
				2 / ( right	- left		),
				2 / ( top	- bottom	),
				2 / ( nearZ - farZ		),
			}
		);

		return S * T;
	}

	Matrix4 Frustum(RealType left, RealType right, RealType bottom, RealType top, RealType nearZ, RealType farZ)
	{
		/**
		* Perspective to orthographic
		*
		* N = nearZ
		* F = farZ
		* A = N + F
		* B = N * F * -1
		*
		* Matrix:
		* [N, 0, 0, 0]
		* [0, N, 0, 0]
		* [0, 0, A, B]
		* [0, 0, 1, 0]
		*/

		Matrix4 M;
		MemoryClear(&M);
		M[0][0] = nearZ;
		M[1][1] = nearZ;
		M[2][2] = nearZ + farZ;
		M[2][3] = -nearZ * farZ;
		M[3][2] = 1;

		return OrthographicProjection(left, right, bottom, top, nearZ, farZ) * M;
	}

	Matrix4 PerspectiveProjection(RealType fovY, RealType aspect, RealType nearZ, RealType farZ)
	{
		RealType halfHeight	= nearZ * Tangent( fovY / 2 );
		RealType halfWidth	= halfHeight * aspect;

		return Frustum( -halfWidth, halfWidth, -halfHeight, halfHeight, nearZ, farZ );
	}

	Matrix4 HomogeneousClipSpaceToScreenSpace(RealType width, RealType height)
	{
		RealType halfWidth	= width / 2;
		RealType halfHeight = height / 2;

		Matrix4 S = Scale(
			Vector3
			{
				halfWidth,
				halfHeight,
				1,
			}
		);

		Matrix4 T = Translate(
			Vector3
			{
				halfWidth,
				halfHeight,
				0,
			}
		);

		return T * S;
	}
}