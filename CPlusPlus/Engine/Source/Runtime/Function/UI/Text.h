#pragma once

#include "UI.h"



namespace Engine::UI
{
	ENGINE_API Void Text(IDrawable* interface, const Vector2Int& position, const U32String& text, const Color& color = Color_Text);
}


namespace Engine::UI::Private
{
	Vector2Int CalcualteTextRenderSize(const U32String& text);
	Void RenderAlignedText(IDrawable* interface, Alignment alignment, const RectangleInt& relativeTo, const U32String& text, const Color& color);
}