#pragma once

#include "../../Core.h"



namespace Engine::UI
{
	struct ENGINE_API Padding
	{
		union
		{
			struct
			{
				Int32 left;
				Int32 bottom;
			};
			Vector2Int leftBottom;
		};
		union
		{
			struct
			{
				Int32 right;
				Int32 top;
			};
			Vector2Int rightTop;
		};


		Padding();
		Padding(Int32 scalar);
		Padding(Int32 horizontal, Int32 vertical);
		Padding(Int32 left, Int32 bottom, Int32 right, Int32 top);
		Padding(const Vector2Int& leftBottom, const Vector2Int& rightTop);
		Padding(const Padding& other);
		Padding& operator=(const Padding& other);
	};
}