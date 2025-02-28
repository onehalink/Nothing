#include "Tooltip.h"

#include "../DefaultValue.h"



namespace Engine::UI
{
	Tooltip::Tooltip()
		: Element()
	{
		text.color = Colors::Text;
		text.padding = Values::TooltipTextPadding;
		text.alignment = Alignment::LeftBottom;
		SetText(LITERAL(Char32, "This is a tip"));

		background = Colors::TooltipBackground;
		border = Colors::Border;

		isHover = false;
		isShow = false;
		timeElapsed = 0;
		timeThreshold = Values::TooltipShowTimeThreshold;
	}

	Void Tooltip::Update(const InputSystem& inputSystem, RealType deltaTime)
	{
		if (!parent)
			return;

		{
			auto parentPosition = parent->GetAbsolutePosition();
			isHover = RectangleInt(parentPosition, parentPosition + parent->size).Contain(inputSystem.mousePosition);
		}

		if (isHover)
		{
			if (!isShow)
			{
				timeElapsed += deltaTime;
				if (timeElapsed > timeThreshold)
				{
					isShow = true;

					showPosition =
					{
						inputSystem.mousePosition.x,
						inputSystem.mousePosition.y - cursorHeight - size.y,
					};
				}
			}
		}
		else
		{
			if (isShow)
			{
				isShow = false;

				timeElapsed = 0;
			}
		}
	}

	Void Tooltip::Render(IRenderable* interface)
	{
		if (!isShow)
			return;

		RectangleInt rectangle = { showPosition, showPosition + size };

		Render::SolidRectangle(interface, rectangle, background);
		text.Render(interface, showPosition, size);

		Render::Rectangle(interface, rectangle, border);
	}

	Void Tooltip::SetText(U32StringView view)
	{
		text.text = view;
		size = Attachment::Text::CalculateTextRenderSize(view) + Vector2Int(text.padding.left + text.padding.right, text.padding.bottom + text.padding.top);
	}
}
