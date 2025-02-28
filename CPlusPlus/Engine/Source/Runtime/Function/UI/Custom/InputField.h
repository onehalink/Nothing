#pragma once

#include "../Attachment.h"
#include "../Element.h"



namespace Engine::UI
{
	struct ENGINE_API InputField : Element
	{
		Action<U32StringView> OnType;

		Attachment::Text text;
		Bool isSelected;

		RectangleInt hitBox;
		RectangleInt textHitBox;

		Bool isHeld;
		RectangleInt selectedTextRegion;
		Bool isSelectTextFromLeftToRight;

		Bool showCaret;
		RealType blinkTimestep;
		RealType timeElapsed;

		Int32 textInsertIndex;

		Color backgroundColor;
		Color borderColor;
		Color selectedBorderColor;
		Color caretColor;
		Color selectedTextRegionColor;


		InputField();


		virtual Void Update(const InputSystem& inputSystem, RealType deltaTime) override;
		virtual Void Render(IRenderable* interface) override;
	private:
		Void DropSelectedTextRegion();
	};
}