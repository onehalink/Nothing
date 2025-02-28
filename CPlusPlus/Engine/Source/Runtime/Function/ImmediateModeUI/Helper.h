#pragma once

#include "../Render/2DGeometry.h"

#include "Axis.h"
#include "Direction.h"
#include "Alignment.h"



namespace Engine::IMUI::Private
{
	enum class ArrowDirection
	{
		Left,
		Right,
		Bottom,
		Top,
	};


	Void DrawArrow(IDrawable* interface, const Vector2Int& position, SizeType size, ArrowDirection direction, const Color& color);
	Void DrawArrowFilled(IDrawable* interface, const Vector2Int& position, SizeType size, ArrowDirection direction, const Color& color);

	Axis AxisFromDirection(Direction direction);
	Vector2Int CalculateRectangleAlignment(Alignment alignment, const RectangleInt& relativeTo, const Vector2Int& alignedRectangleSize);
}