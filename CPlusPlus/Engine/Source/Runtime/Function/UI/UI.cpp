#include "UI.h"



namespace Engine::UI
{
	Stack<FontSDFAtlas> fontSDFAtlasStack;
}


namespace Engine::UI::Private
{
	Axis AxisFromDirection(Direction direction)
	{
		return direction == Direction::LeftToRight || direction == Direction::RightToLeft ?
			Axis::Horizontal : Axis::Vertical;
	}

	Vector2Int CalculateRectangleAlignment(Alignment alignment, const RectangleInt& relativeTo, const Vector2Int& alignedRectangleSize)
	{
		auto distance = relativeTo.Size() - alignedRectangleSize;
		auto x = distance.x;
		auto y = distance.y;
		auto halfX = x / 2;
		auto halfY = y / 2;

		auto offset = Vector2Int::Zero;
		switch (alignment)
		{
		case Alignment::LeftBottom:
			break;
		case Alignment::LeftMiddle:
			offset.y = halfY;
			break;
		case Alignment::LeftTop:
			offset.y = y;
			break;
		case Alignment::MiddleBottom:
			offset.x = halfX;
			break;
		case Alignment::Center:
			offset = { halfX, halfY };
			break;
		case Alignment::MiddleTop:
			offset = { halfX, y };
			break;
		case Alignment::RightBottom:
			offset.x = x;
			break;
		case Alignment::RightMiddle:
			offset = { x, halfY };
			break;
		case Alignment::RightTop:
			offset = { x, y };
			break;
		}

		return relativeTo.minimum + offset;
	}

	Void DrawArrow(IDrawable* interface, ArrowDirection direction, const Vector2Int& arrowPoint, SizeType size, const Color& color)
	{
		Int32 unit = size;
		Int32 half = unit / 2;
		Int32 height = unit * Sine(Pi<RealType> / 3 * 2);

		Vector2Int a, b;
		switch (direction)
		{
		case ArrowDirection::Left:
			a = arrowPoint + Vector2Int(height, -half);
			b = a + Vector2Int::Top * unit;
			break;
		case ArrowDirection::Right:
			a = arrowPoint + Vector2Int(-height, half);
			b = a + Vector2Int::Bottom * unit;
			break;
		case ArrowDirection::Bottom:
			a = arrowPoint + Vector2Int(half, height);
			b = a + Vector2Int::Left * unit;
			break;
		case ArrowDirection::Top:
			a = arrowPoint - Vector2Int(half, height);
			b = a + Vector2Int::Right * unit;
			break;
		}

		DrawTriangleFilled(interface, a, b, arrowPoint, color);
	}
}