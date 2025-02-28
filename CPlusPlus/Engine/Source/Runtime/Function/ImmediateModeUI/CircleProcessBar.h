#pragma once

#include "Text.h"



namespace Engine::IMUI
{
	struct ENGINE_API CircleProcessBar : IBehaviour
	{
		Vector2Int position;
		Int32 outerRadius;
		Int32 innerRadius;

		Color background;
		Color foreground;

		Bool active;
		Bool visible;

		RealType value;

		Bool displayText;
		Color textColor;


		CircleProcessBar(const Vector2Int& position, Int32 outerRadius, Int32 innerRadius);


		Void Update(const EventSystem& eventSystem) override;
		Void Render(IDrawable* interface) override;
	};
}