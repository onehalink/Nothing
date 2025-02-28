#pragma once

#include "Text.h"



namespace Engine::UI
{
	struct ENGINE_API Button
	{
		Action<> OnClick;
		Action<> OnPress;

		RectangleInt rectangle; // position and size
		
		Color normal;
		Color hover;
		Color highlighted;
		Color currentColor;

		Color border;

		Bool active;
		Bool visible;

		U32String	text;
		Color		textColor;
		Alignment	textAlignment;


		Button();
		Button(const Vector2Int& position, const Vector2Int& size, const U32String& text, Action<> OnClick = nullptr, Action<> OnPress = nullptr);


		Void Update(const InputSystem& inputSystem);
		Void Render(IDrawable* interface);
	private:
		Void InitInternal();
	};
}