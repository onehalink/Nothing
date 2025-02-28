#include "InputField.h"
#include "../DefaultValue.h"

#include "../Mask.h"


namespace Engine::UI
{


	InputField::InputField()
	{
		text.padding = { 4 };
		text.color = Colors::Text;
		text.alignment = Alignment::LeftMiddle;
		isSelected = false;

		isHeld = false;

		showCaret = false;
		blinkTimestep = 0.5;
		timeElapsed = 0;

		textInsertIndex = 0;

		backgroundColor = 0x9E9B6659;
		borderColor = Colors::Border;
		selectedBorderColor = Color::Red;
		caretColor = Color::White;
		selectedTextRegionColor = 0x202020;
	}

	Void InputField::Update(const InputSystem& inputSystem, RealType deltaTime)
	{
		if (inputSystem.MouseButtonClicked(MouseButton::Left) && !isHeld)
		{
			isSelected = false;

			selectedTextRegion = { 0, 0, 0, 0 };
		}

		auto position = GetAbsolutePosition();
		hitBox = { position, position + size };

		textHitBox.minimum = position + text.padding.leftBottom;
		textHitBox.maximum = textHitBox.minimum + Vector2Int(8 * text.text.GetCount(), size.y - text.padding.bottom - text.padding.top);

		Bool isPressed = inputSystem.MouseButtonPressed(MouseButton::Left);
		Bool isHover = hitBox.Contain(inputSystem.mousePosition);

		if (!isHeld && isPressed && isHover)
		{
			isHeld = true;

			isSelected = true;

			textInsertIndex = (Clamp(inputSystem.mousePosition.x - textHitBox.minimum.x, 0, textHitBox.Size().x) + 4) / 8;
		}
		
		if (isSelected)
		{
			timeElapsed += deltaTime;
			if (timeElapsed > blinkTimestep)
			{
				timeElapsed = 0;
				showCaret = !showCaret;
			}
		}
		else
			timeElapsed = 0;

		if (!isPressed)
			isHeld = false;

		if (isHeld)
		{
			auto caretPositionX = textHitBox.left + textInsertIndex * 8;
			auto offset = inputSystem.mousePosition.x - caretPositionX;

			Vector2Int minimum, maximum;
			if (offset >= 0)
			{
				minimum = { caretPositionX , textHitBox.bottom };
				maximum = { minimum.x + (offset + 4) / 8 * 8, textHitBox.top };

				isSelectTextFromLeftToRight = true;
			}
			else
			{
				maximum = { caretPositionX , textHitBox.top };
				minimum = { caretPositionX + (offset - 4) / 8 * 8, textHitBox.bottom };

				isSelectTextFromLeftToRight = false;
			}

			selectedTextRegion = { 
				Clamp(minimum, textHitBox.minimum, textHitBox.maximum),
				Clamp(maximum, textHitBox.minimum, textHitBox.maximum)
			};
		}

		if (isSelected)
		{
			if (inputSystem.KeyClicked(Key::BackSpace))
			{
				if (selectedTextRegion.IsValid())
					DropSelectedTextRegion();
				else
					if (textInsertIndex > 0)
						text.text = Remove<Char32>(text.text, --textInsertIndex, 1);
			}

			if (inputSystem.inputChar32WritePosition != 0)
			{
				if (selectedTextRegion.IsValid())
					DropSelectedTextRegion();

				text.text = Insert<Char32>(text.text, textInsertIndex, inputSystem.inputChar32s);
				textInsertIndex += inputSystem.inputChar32WritePosition;

				if (OnType)
					OnType(text.text);
			}
		}
	}

	Void InputField::Render(IRenderable* interface)
	{
		Render::SolidRectangle(interface, hitBox, backgroundColor);
		Render::Rectangle(interface, hitBox, !isSelected ? borderColor : selectedBorderColor);

		Mask mask(interface, { hitBox.minimum + text.padding.leftBottom, hitBox.maximum - text.padding.rightTop });
		Render::SolidRectangle(interface, selectedTextRegion, selectedTextRegionColor);
		text.Render(interface, hitBox.minimum, textHitBox.Size() + text.padding.rightTop);

		if (isSelected && showCaret)
		{
			if (!selectedTextRegion.IsValid())
			{
				Vector2Int from = hitBox.minimum + text.padding.leftBottom + Vector2Int::Right * textInsertIndex * 8;
				Vector2Int to = from + Vector2Int::Top * (size.y - text.padding.top - text.padding.bottom);

				Render::Segment(interface, from, to, caretColor);
			}
		}
	}

	Void InputField::DropSelectedTextRegion()
	{
		SizeType count = selectedTextRegion.Size().x / 8;

		SizeType index;
		if (isSelectTextFromLeftToRight)
		{
			index = textInsertIndex;
		}
		else
		{
			index = textInsertIndex - count;

			textInsertIndex -= count;
		}

		text.text = Remove<Char32>(text.text, index, count);

		selectedTextRegion = { 0, 0, 0, 0 };
	}
}