#pragma once

#include "Text.h"



namespace Engine::UI
{
	ENGINE_API Void ProcessBar(IDrawable* interface, const Vector2Int& position, const Vector2Int& size, RealType processValue, const Color& background = Color_ProcessBarBackground, const Color& foreground = Color_ProcessBarForeground, const Color& border = Color_Border, Direction direction = Direction::LeftToRight);
}