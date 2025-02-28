#pragma once

#include "Text.h"



namespace Engine::UI
{
	struct ENGINE_API ProcessBar : IBehaviour
	{
		RectangleInt rectangle;

		Color background;
		Color foreground;
		Color border;

		Bool active;
		Bool visible;

		RealType value;
		Direction direction;

		Bool displayText;
		Color textColor;
		Alignment alignment;


		ProcessBar(const Vector2Int& position, const Vector2Int& size, Direction direction = Direction::LeftToRight);

		Void Update(const InputSystem& inputSystem) override;
		Void Render(IDrawable* interface) override;
	};
}