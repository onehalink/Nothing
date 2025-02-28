#pragma once

#include "../Base.h"



namespace Engine
{
	using Dimension = SizeType;
}


namespace Engine::Private
{
	template<Dimension, typename T>
	struct VectorBase;


	template<typename T>
	struct VectorBase<2, T>
	{
		union
		{
			T components[2];
			struct
			{
				T x;
				T y;
			};
		};
	};


	template<typename T>
	struct VectorBase<3, T>
	{
		union
		{
			T components[3];
			struct
			{
				T x;
				T y;
				T z;
			};
		};
	};


	template<typename T>
	struct VectorBase<4, T>
	{
		union
		{
			T components[4];
			struct
			{
				T x;
				T y;
				T z;
				T w;
			};
			struct
			{
				T r;
				T g;
				T b;
				T a;
			};
		};
	};
}