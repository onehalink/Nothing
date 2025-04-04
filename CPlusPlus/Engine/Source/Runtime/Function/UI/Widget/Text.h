#pragma once

#include "../IBehaviour.h"



namespace Engine::UI
{
	ENGINE_API Void Text(IDrawable* interface, const Vector2Int& position, const U8String& text, const Color& color = Color_Text);
}