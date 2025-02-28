#pragma once

#include "../Render/FrameBuffer.h"

#include "IBehaviour.h"



namespace Engine::UI
{
	enum class Alignment
	{
		LeftBottom,
		LeftMiddle,
		LeftTop,

		MiddleBottom,
		Center,
		MiddleTop,

		RightBottom,
		RightMiddle,
		RightTop,
	};


	enum class Axis
	{
		Horizontal,
		Vertical,
	};


	enum class Direction
	{
		LeftToRight,
		RightToLeft,

		BottomToTop,
		TopToBottom,
	};


	struct Visual
	{
		Color normal;
		Color hover;
		Color active;

		Color color;
	};


	struct State
	{
		Bool active;
		Bool visible;
	};


	const Vector2Int FontSizeInPixel = { 8, 16 };

	const Color Color_Text = { 0.90f, 0.90f, 0.90f, 1.00f };
	const Color Color_Border = { 0.50f, 0.50f, 0.50f, 0.50f };
	const Color Color_ButtonNormal = { 0.35f, 0.40f, 0.61f, 0.62f };
	const Color Color_ButtonHover = { 0.40f, 0.48f, 0.71f, 0.79f };
	const Color Color_ButtonActive = { 0.46f, 0.54f, 0.80f, 1.00f };
	const Color Color_ScrollBarBackground = { 0.46f, 0.54f, 0.80f, 1.00f };
	const Color Color_ScrollBarGrabNormal = { 0.40f, 0.40f, 0.80f, 0.30f };
	const Color Color_ScrollBarGrabHover = { 0.40f, 0.40f, 0.80f, 0.40f };
	const Color Color_ScrollBarGrabActive = { 0.41f, 0.39f, 0.80f, 0.60f };
	const Color Color_ScrollViewBackground = { 0.00f, 0.00f, 0.00f, 0.45f };


	Axis AxisFromDirection(Direction direction);
	Vector2Int CalculateRectangleAlignment(Alignment alignment, const Vector2Int& from, const RectangleInt& relativeTo);
	Bool NoEnoughDisplaySpace(const RectangleInt& safeArea, const RectangleInt& rectangle);
}