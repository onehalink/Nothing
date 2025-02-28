#pragma once

#include "Text.h"



namespace Engine::IMUI
{
	struct ENGINE_API Button : IBehaviour
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

		U8String text;
		Color textColor;
		Alignment alignment;


		Button(const Vector2Int& position, const Vector2Int& size, const U8String& text, Action<> OnClick = nullptr, Action<> OnPress = nullptr);


		Void Update(const EventSystem& eventSystem) override;
		Void Render(IDrawable* interface) override;
	};
}