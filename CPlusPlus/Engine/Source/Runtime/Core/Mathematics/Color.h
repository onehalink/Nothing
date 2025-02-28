#pragma once

#include "Vector.h"



namespace Engine
{
	using Color = Vector4;


	ENGINE_API RealType Luminance(const Color& color);
	ENGINE_API Color Inverted(const Color& color);

	ENGINE_API Color Lightened(const Color& color, RealType amount);
	ENGINE_API Color Darkened(const Color& color, RealType amount);

	ENGINE_API Color ToSRGB(const Color& color);
	ENGINE_API Color ToLinear(const Color& color);

	ENGINE_API Color FromR8G8B8(UInt32 pixel);
	ENGINE_API Color FromR8G8B8A8(UInt32 pixel);
	ENGINE_API Color FromB8G8R8(UInt32 pixel);
	ENGINE_API Color FromB8G8R8A8(UInt32 pixel);
	ENGINE_API UInt32 ToR8G8B8(const Color& color);
	ENGINE_API UInt32 ToR8G8B8A8(const Color& color);
	ENGINE_API UInt32 ToB8G8R8(const Color& color);
	ENGINE_API UInt32 ToB8G8R8A8(const Color& color);
}