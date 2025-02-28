#include "CheckBox.h"



namespace Engine::UI
{
	CheckBox::CheckBox()
	{
		InitInternal();
	}

	CheckBox::CheckBox(const Vector2Int& position, SizeType size, Action<Bool> OnToggle)
	{
		InitInternal();

		this->OnToggle = OnToggle;

		rectangle = { position, position + Vector2Int::One * size };
	}

	Void CheckBox::Update(const InputSystem& inputSystem)
	{
		if (!active)
			return;

		Bool isHover = rectangle.IsInside(inputSystem.mousePosition);

		if (isHover && inputSystem.MouseButtonClicked(MouseButton::Left))
		{
			value = !value;

			if (OnToggle)
				OnToggle(value);
		}
	}

	Void CheckBox::Render(IDrawable* interface)
	{
		if (!visible)
			return;

		DrawRectangleFilled(interface, rectangle, background);
		DrawRectangle(interface, rectangle, border);

		if (value)
		{
			auto unit = rectangle.Size().x;
			auto over2 = unit / 2;
			auto over4 = unit / 4;
			
			auto a = rectangle.minimum + Vector2Int::Top * over2;
			auto b = rectangle.minimum + Vector2Int::Right * over2;
			auto c = rectangle.minimum + Vector2Int(unit, unit);
			auto d = rectangle.minimum + Vector2Int(over2, over4);

			DrawTriangleFilled(interface, a, b, d, markColor);
			DrawTriangleFilled(interface, b, c, d + Vector2Int::Left, markColor);
		}
	}

	void CheckBox::InitInternal()
	{
		MemoryClear(this);

		background = Color_CheckBoxBackground;
		border = Color_Border;

		markColor = Color_CheckBoxMark;

		active = true;
		visible = true;
	}
}
