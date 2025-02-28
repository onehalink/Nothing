#pragma once

#include "IDrawable.h"



namespace Engine
{
	ENGINE_API Void DrawSegment(IDrawable* interface, const Vector2Int& a, const Vector2Int& b, const Color& color);
	ENGINE_API Void DrawRectangle(IDrawable* interface, const Vector2Int& minimum, const Vector2Int& maximum, const Color& color);

	ENGINE_API Void DrawRectangleFilled(IDrawable* interface, const Vector2Int& minimum, const Vector2Int& maximum, const Color& color);
}