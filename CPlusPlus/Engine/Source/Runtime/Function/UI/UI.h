#pragma once

#include "../../Asset/FontSDFAtlas.h"

#include "../../Platform/Service/Input/InputSystem.h"

#include "../Render/2DGeometry.h"



namespace Engine::UI
{
#pragma region Constants

	const RealType ScrollBarDefaultGrabRenderSize = 0.2;

	const SizeType ScrollViewDefaultScrollBarSize = 20;

	constexpr UInt32 FallbackUnicodeChar = '?';

	const U32String InputTextPlaceholder = "Type text..";


	// Common
	const Color Color_Border = { 0.50, 0.50, 0.50, 0.50 };
	//const Color Color_Border = { 1, 0, 0, 1 };

	// Text
	const Color Color_Text = { 0.90, 0.90, 0.90, 1.00 };
	const Color Color_TextDisabled = { 0.60, 0.60, 0.60, 1.00 };

	// Button
	const Color Color_ButtonNormal = { 0.35, 0.40, 0.61, 0.62 };
	const Color Color_ButtonHover = { 0.40, 0.48, 0.71, 0.79 };
	const Color Color_ButtonHighlighted = { 0.46, 0.54, 0.80, 1.00 };

	// CheckBox
	const Color Color_CheckBoxBackground = Color_ButtonNormal;
	const Color Color_CheckBoxMark = { 0.90, 0.90, 0.90, 0.5 };

	// ScrollBar
	const Color Color_ScrollBarBackground = { 0.46, 0.54, 0.80, 1.00 };
	const Color Color_ScrollBarGrabNormal = { 0.40, 0.40, 0.80, 0.30 };
	const Color Color_ScrollBarGrabHover = { 0.40, 0.40, 0.80, 0.40 };
	const Color Color_ScrollBarGrabHighlighted = { 0.41, 0.39, 0.80, 0.60 };

	// ProcessBar
	const Color Color_ProcessBarBackground = Color_ScrollBarBackground;
	const Color Color_ProcessBarForeground = Color_ScrollBarGrabNormal;

	// ScrollView
	const Color Color_ScrollViewBackground = { 0.43f, 0.43f, 0.43f, 0.39f };

	// TextInput
	const Color Color_TextInputBackground = Color_ButtonNormal;
	const Color Color_TextInputBorderSelected = { 0.8, 0.8, 0.8, 1 };
	//const Color Color_TextInputBorderSelected = { 1, 0, 0, 1 };
	const Color Color_TextInputCaret = { 0, 0, 0, 1 };

	// CombineBox
	const Color Color_CombineBoxNormal = Color_ButtonNormal;
	const Color Color_CombineBoxHover = Color_ButtonHover;

#pragma endregion


#pragma region Variables

	extern ENGINE_API Stack<FontSDFAtlas> fontSDFAtlasStack;

#pragma endregion


#pragma region Enums

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


	enum class HorizontalLocation
	{
		Left,
		Right,
	};


	enum class VerticalLocation
	{
		Bottom,
		Top,
	};

#pragma endregion


#pragma region Types

	struct Padding
	{
		Int32 left;
		Int32 right;
		Int32 bottom;
		Int32 top;
	};

#pragma endregion
}


namespace Engine::UI::Private
{
	enum class ArrowDirection
	{
		Left,
		Right,
		Bottom,
		Top,
	};


	Axis AxisFromDirection(Direction direction);
	Vector2Int CalculateRectangleAlignment(Alignment alignment, const RectangleInt& relativeTo, const Vector2Int& alignedRectangleSize);

	Void DrawArrow(IDrawable* interface, ArrowDirection direction, const Vector2Int& arrowPoint, SizeType size, const Color& color);
}