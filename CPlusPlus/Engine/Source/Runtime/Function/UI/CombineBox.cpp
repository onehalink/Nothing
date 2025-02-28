#include "CombineBox.h"



namespace Engine::UI
{
	CombineBox::CombineBox()
	{
		InitInternal();
	}

	CombineBox::CombineBox(const Vector2Int& position, const Vector2Int& size, Action<Int32> OnValueChange)
	{
		InitInternal();

		rectangle = { position, position + size };

		this->OnValueChange = OnValueChange;
	}

	Void CombineBox::Update(const InputSystem& inputSystem)
	{
		if (!active)
			return;

		if (!collapsed)
		{
			itemHoverIndex = -1;

			for (SizeType index = 0; index < items.GetCount(); index++)
				if (CalculateRectangleForItem(index).IsInside(inputSystem.mousePosition))
				{
					itemHoverIndex = index;

					if (inputSystem.MouseButtonClicked(MouseButton::Left) && value != index)
					{
						value = index;

						if (OnValueChange)
							OnValueChange(value);
					}
				}
		}

		{
			Bool isHover = rectangle.IsInside(inputSystem.mousePosition);
			if (isHover)
				current = hover;
			else
				current = normal;

			if (inputSystem.MouseButtonClicked(MouseButton::Left))
			{
				if (isHover)
					collapsed = !collapsed;
				else
					collapsed = true;
			}
		}
	}

	Void CombineBox::Render(IDrawable* interface)
	{
		if (!visible)
			return;

		DrawRectangleFilled(interface, rectangle, current);
		DrawRectangle(interface, rectangle, border);

		{
			Int32 height = rectangle.maximum.y - rectangle.minimum.y;

			Private::DrawArrow(interface, Private::ArrowDirection::Bottom, rectangle.maximum - Vector2Int(arrowSize, (height + arrowSize) / 2), arrowSize, arrowColor);
		}

		if(value < items.GetCount())
			Private::RenderAlignedText(interface, Alignment::LeftMiddle, rectangle, items[value].text, Color_Text);

		if (!collapsed)
			for (SizeType index = 0; index < items.GetCount(); index++)
			{
				auto itemRectangle = CalculateRectangleForItem(index);

				DrawRectangleFilled(interface, itemRectangle, itemHoverIndex != index ? normal : hover);
				DrawRectangle(interface, itemRectangle, border);

				Private::RenderAlignedText(interface, Alignment::LeftMiddle, itemRectangle, items[index].text, textColor);
			}
	}

	Void CombineBox::InitInternal()
	{
		MemoryClear(this);

		
		normal = Color_CombineBoxNormal;
		hover = Color_CombineBoxHover;

		border = Color_Border;

		textColor = Color_Text;

		arrowSize = 10;
		arrowColor = Color::White;

		collapsed = true;

		items = { InPlace(), Item{"Item 0"}, Item{"Item 1"}, Item{"Item 2"} };

		active = true;
		visible = true;
	}

	RectangleInt CombineBox::CalculateRectangleForItem(SizeType index)
	{
		auto size = rectangle.Size();

		Vector2Int minimum = rectangle.minimum + Vector2Int::Bottom * size.y * (index + 1);
		Vector2Int maximum = rectangle.maximum + Vector2Int::Bottom * size.y * (index + 1);

		return { minimum, maximum };
	}
}
