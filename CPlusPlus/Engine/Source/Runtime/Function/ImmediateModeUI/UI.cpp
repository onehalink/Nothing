#include "UI.h"



namespace Engine::UI
{
	Axis AxisFromDirection(Direction direction)
	{
		return direction == Direction::LeftToRight || direction == Direction::RightToLeft ?
			Axis::Horizontal : Axis::Vertical;
	}

	Vector2Int CalculateRectangleAlignment(Alignment alignment, const Vector2Int& from, const RectangleInt& relativeTo)
	{
		auto distance	= relativeTo.Size() - from;
		auto x			= distance.x;
		auto y			= distance.y;
		auto halfX		= x / 2;
		auto halfY		= y / 2;

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

	Bool NoEnoughDisplaySpace(const RectangleInt& safeArea, const RectangleInt& rectangle)
	{
		if (
			rectangle.left		< safeArea.left		||
			rectangle.right		>= safeArea.right	||
			rectangle.bottom	< safeArea.bottom	||
			rectangle.top		>= safeArea.top
			)
			return true;

		return false;
	}
}