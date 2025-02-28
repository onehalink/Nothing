#pragma once

#include "IDrawable.h"



namespace Engine
{
	struct ENGINE_API Serface : IDrawable
	{
		Span<Color> storage;

		SizeType width;
		SizeType height;
		SizeType elementCount;


		Serface();
		Serface(SizeType width, SizeType height);
		Serface(const Serface& other);
		Serface(Serface&& other);
		~Serface();


		Void Clear(const Color& clearColor = Color::Black);
		Void CopyTo(Void* RenderTarget, PixelFormat specific = PixelFormat::B8G8R8A8);

		Void SetPixel(SizeType x, SizeType y, const Color& color) override;
		const Color& GetPixel(SizeType x, SizeType y) const override;
		RectangleInt SafeArea() const override;


		Serface& operator=(const Serface& other);
		Serface& operator=(Serface&& other);
	private:
		Void CopyFrom(const Serface& other);
		Void SwapWith(Serface& other);
	};
}