#pragma once

#include "../../Core.h"

#include "Alignment.h"



namespace Engine::UI::Private
{
	inline Vector2Int CalculateRectangleAlignment(Alignment alignment, Vector2Int relativeToRectangleSize, Vector2Int alignedRectangleSize, Vector2Int paddingRightTop)
	{
		auto distance = relativeToRectangleSize - alignedRectangleSize - paddingRightTop;
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

		return offset;
	}
}
