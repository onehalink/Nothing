#pragma once

#include "../../Core.h"

#include "Padding.h"



namespace Engine::UI
{
	namespace Colors
	{
		const Color Border = 0x7F7F7F7F;

		const Color Text = 0xFFE5E5E5;
		const Color TextDisable = 0xFF999999;

		const Color TitleBar = 0xD3894444;
		const Color TitleBarCollapsed = 0xDDA05151;

		const Color TooltipBackground = 0xEA231C1C;
	}


	namespace Values
	{
		constexpr SizeType TitleBarHeight = 25;
		constexpr SizeType TitleBarArrowTriangleSideLength = 10;
		constexpr RealType TitleBarCrossLineWidth = 0.15;

		const Vector2Int WindowSize = { 400, 600 };
		constexpr SizeType WindowSizingWidth = 5;

		const Padding TooltipTextPadding = { 4, 8, 4, 8 };
		constexpr RealType TooltipShowTimeThreshold = 1;
	}
}