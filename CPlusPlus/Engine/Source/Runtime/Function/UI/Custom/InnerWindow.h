#pragma once

#include "../Attachment.h"
#include "../Element.h"



namespace Engine::UI
{
	struct ENGINE_API Window : Element
	{
		Vector2Int containerSize;

		Attachment::Shape bottomArrow;
		Attachment::Shape rightArrow;
		Attachment::Shape cross;
		Attachment::Button collapseButton;
		Attachment::Button closeButton;
		Attachment::Text titleBarText;
		Attachment::Draggable draggable;
		Attachment::Sizing sizing;

		SizeType titleBarHeight;
		Color titleBarBackground;
		Color titleBarBackgroundCollapsed;
		Color titleBarArrowColor;
		Color titleBarCrossColor;

		Color borderColor;

		Bool isCollapsed;


		Window();


		virtual Void Update(const InputSystem& inputSystem, RealType deltaTime) override;
		virtual Void Render(IRenderable* interface) override;


		Void OnResize();
	private:
		RectangleInt CalculateTitleBarRectangle(Vector2Int absolutePosition) const;
	};
}