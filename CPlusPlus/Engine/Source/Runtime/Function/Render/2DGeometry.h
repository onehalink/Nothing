#pragma once

#include "IDrawable.h"



namespace Engine
{
	ENGINE_API Void DrawSegment(IDrawable* interface, const Vector2Int& a, const Vector2Int& b, const Color& color);
	ENGINE_API Void DrawPath(IDrawable* interface, const Vector2Int* points, SizeType pointCount, const Color& color);
	ENGINE_API Void DrawTriangle(IDrawable* interface, const Vector2Int& a, const Vector2Int& b, const Vector2Int& c, const Color& color);
	ENGINE_API Void DrawRectangle(IDrawable* interface, const Vector2Int& minimum, const Vector2Int& maximum, const Color& color);
	ENGINE_API Void DrawCircleFast(IDrawable* interface, const Vector2Int& position, RealType radius, const Color& color, SizeType iteration = 16);

	ENGINE_API Void DrawTriangleFilled(IDrawable* interface, const Vector2Int& a, const Vector2Int& b, const Vector2Int& c, const Color& color);
	ENGINE_API Void DrawRectangleFilled(IDrawable* interface, const Vector2Int& minimum, const Vector2Int& maximum, const Color& color);
	ENGINE_API Void DrawCircleFilled(IDrawable* interface, const Vector2Int& position, RealType radius, const Color& color);
}