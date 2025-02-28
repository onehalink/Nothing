#pragma once

#include "../../Core.h"



namespace Engine
{
	struct IDrawable
	{
		virtual Void SetPixel(SizeType x, SizeType y, const Color& color) = 0;
		virtual const Color& GetPixel(SizeType x, SizeType y) const = 0;

		virtual RectangleInt SafeArea() const = 0;
	};
}