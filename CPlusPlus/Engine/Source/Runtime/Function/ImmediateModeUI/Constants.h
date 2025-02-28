#pragma once

#include "../../Core.h"



namespace Engine::IMUI
{
	const Vector2Int DefaultFontSizeInPixel = { 8, 16 };

	const RealType ScrollBarDefaultGrabRenderSize = 0.2;

	const SizeType ScrollViewDefaultScrollBarSize = 20;



	// Common
	const Color Color_Border = { 0.50, 0.50, 0.50, 0.50 };

	// Text
	const Color Color_Text			= { 0.90, 0.90, 0.90, 1.00 };
	const Color Color_TextDisabled	= { 0.60, 0.60, 0.60, 1.00 };

	// Button
	const Color Color_ButtonNormal		= { 0.35, 0.40, 0.61, 0.62 };
	const Color Color_ButtonHover		= { 0.40, 0.48, 0.71, 0.79 };
	const Color Color_ButtonHighlighted	= { 0.46, 0.54, 0.80, 1.00 };

	// ScrollBar
	const Color Color_ScrollBarBackground		= { 0.46, 0.54, 0.80, 1.00 };
	const Color Color_ScrollBarGrabNormal		= { 0.40, 0.40, 0.80, 0.30 };
	const Color Color_ScrollBarGrabHover		= { 0.40, 0.40, 0.80, 0.40 };
	const Color Color_ScrollBarGrabHighlighted	= { 0.41, 0.39, 0.80, 0.60 };

	// ProcessBar
	const Color Color_ProcessBarBackground = Color_ScrollBarBackground;
	const Color Color_ProcessBarForeground = Color_ScrollBarGrabNormal;

	// ScrollView
	const Color Color_ScrollViewBackground = { 0.43f, 0.43f, 0.43f, 0.39f };
}