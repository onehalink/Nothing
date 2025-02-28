#include "Mask.h"



namespace Engine::UI
{
	Mask::Mask(IRenderable* interface, const RectangleInt& newScissorRectangle)
	{
		this->interface = interface;
		oldScissorRectangle = interface->GetScissorRectangle();

		interface->SetScissorRectangle({
				Maximum(newScissorRectangle.minimum, oldScissorRectangle.minimum),
				Minimum(newScissorRectangle.maximum, oldScissorRectangle.maximum) }
		);
	}

	Mask::~Mask()
	{
		interface->SetScissorRectangle(oldScissorRectangle);
	}
}