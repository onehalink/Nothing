#pragma once

#include "../Interface/IRenderable.h"



namespace Engine::UI
{
	struct ENGINE_API Mask
	{
		IRenderable* interface;
		RectangleInt oldScissorRectangle;


		Mask(IRenderable* interface, const RectangleInt& newScissorRectangle);
		~Mask();
	};
}