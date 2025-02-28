#pragma once

#include "VectorBase.h"



namespace Engine::Private
{
	template<Dimension, typename T>
	struct MatrixBase;


	template<typename T>
	struct MatrixBase<2, T>
	{
		union
		{
			T components[ 2 * 2 ];
			struct
			{
				T m00, m01;
				T m10, m11;
			};
		};
	};


	template<typename T>
	struct MatrixBase<3, T>
	{
		union
		{
			T components[ 3 * 3 ];
			struct
			{
				T m00, m01, m02;
				T m10, m11, m12;
				T m20, m21, m22;
			};
		};
	};


	template<typename T>
	struct MatrixBase<4, T>
	{
		union
		{
			T components[ 4 * 4 ];
			struct
			{
				T m00, m01, m02, m03;
				T m10, m11, m12, m13;
				T m20, m21, m22, m23;
				T m30, m31, m32, m33;
			};
		};
	};
}