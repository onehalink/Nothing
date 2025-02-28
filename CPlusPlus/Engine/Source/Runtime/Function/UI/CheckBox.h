#pragma once

#include "UI.h"



namespace Engine::UI
{
	struct ENGINE_API CheckBox
	{
		Action<Bool> OnToggle;

		RectangleInt rectangle;

		Color background;
		Color border;

		Color markColor;

		Bool value;

		Bool active;
		Bool visible;


		CheckBox();
		CheckBox(const Vector2Int& position, SizeType size /** width & height */, Action<Bool> OnToggle = nullptr);


		Void Update(const InputSystem& inputSystem);
		Void Render(IDrawable* interface);
	private:
		void InitInternal();
	};
}