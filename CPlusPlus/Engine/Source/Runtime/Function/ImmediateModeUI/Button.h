#pragma once

#include "Text.h"



namespace Engine::UI
{
	struct ENGINE_API Button : IBehaviour
	{
		Action<> OnClick;
		Action<> OnPress;

		RectangleInt	rectangle;
		Visual			visual;
		State			state;
		Color			border;

		U8String	text;
		Color		textColor;
		Alignment	textAlignment;


		Button(const Vector2Int& position, const Vector2Int size = { 100, 50 }, const U8String& text = "Button", Action<> OnClick = nullptr, Action<> OnPress = nullptr);


		Void Update(const EventSystem& eventSystem) override;
		Void Render(IDrawable* interface) override;
	};
}