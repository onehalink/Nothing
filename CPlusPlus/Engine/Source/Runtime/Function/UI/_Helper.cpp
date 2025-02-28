#include "_Helper.h"



namespace Engine::UI::Private
{
	static Void CalculateArrowABPoints(Vector2& outputA, Vector2& outputB, const Vector2Int& position, SizeType size, ArrowDirection direction)
	{
		RealType sine60		= Sine( PiOverThree<RealType> * 2 );
		SizeType halfSize	= size / 2;
		switch (direction)
		{
		case ArrowDirection::Left:
			outputA = { position.x + sine60 * size, position.y - halfSize };
			outputB = { position.x + sine60 * size, position.y + halfSize };
			break;
		case ArrowDirection::Right:
			outputA = { position.x - sine60 * size, position.y + halfSize };
			outputB = { position.x - sine60 * size, position.y - halfSize };
			break;
		case ArrowDirection::Bottom:
			outputA = { position.x + halfSize, position.y + sine60 * size };
			outputB = { position.x - halfSize, position.y + sine60 * size };
			break;
		case ArrowDirection::Top:
			outputA = { position.x - halfSize, position.y - sine60 * size };
			outputB = { position.x + halfSize, position.y - sine60 * size };
			break;
		}
	}


	Void DrawArrow(IDrawable* interface, const Vector2Int& position, SizeType size, ArrowDirection direction, const Color& color)
	{
		Vector2 a, b;
		CalculateArrowABPoints(a, b, position, size, direction);

		DrawTriangle(interface, a, b, position, color);
	}

	Void DrawArrowFilled(IDrawable* interface, const Vector2Int& position, SizeType size, ArrowDirection direction, const Color& color)
	{
		Vector2 a, b;
		CalculateArrowABPoints(a, b, position, size, direction);

		DrawTriangleFilled(interface, a, b, position, color);
	}

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
}
