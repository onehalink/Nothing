#pragma once

#include "Text.h"



namespace Engine::UI
{
	struct ENGINE_API TextInput
	{
		Action<const U32String&> OnType;

		RectangleInt rectangle;
		Padding padding;

		Color background;

		Color normalBorderColor;
		Color selectedBorderColor;
		Color currentBorderColor;
		
		Color textColor;
		Color caretColor;

		Bool selected;
		U32String value;

		Bool active;
		Bool visible;


		TextInput();
		TextInput(const Vector2Int& position, const Vector2Int& size, const Padding& padding = { 5, 5, 5, 5 });


		Void Update(const InputSystem& inputSystem);
		Void Render(IDrawable* interface);
	private:
		Void InitInternal();
	};
}