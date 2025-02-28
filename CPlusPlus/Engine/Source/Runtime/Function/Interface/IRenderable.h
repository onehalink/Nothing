#pragma once

#include "../../Core.h"



namespace Engine
{
	struct IRenderable
	{
		virtual Void SetPixel(SizeType x, SizeType y, Color color) = 0;
		virtual const Color& GetPixel(SizeType x, SizeType y) const = 0;

		virtual Void SetScissorRectangle(const RectangleInt& scissorRectangle) = 0;
		virtual const RectangleInt& GetScissorRectangle() const = 0;
	};
}