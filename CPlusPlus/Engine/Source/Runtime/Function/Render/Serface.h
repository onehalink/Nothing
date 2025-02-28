#pragma once

#include "IDrawable.h"



namespace Engine
{
	struct ENGINE_API Serface : IDrawable
	{
		Memory<Color>	storage;

		SizeType		width;
		SizeType		height; 


		Serface();
		Serface(SizeType width, SizeType height);
		Serface(const Serface& other);
		Serface(Serface&& other);
		~Serface();


		Void SetPixel(SizeType x, SizeType y, const Color& color) override;
		const Color& GetPixel(SizeType x, SizeType y) const override;

		RectangleInt SafeArea() const override;


		Void Clear(const Color& clearColor = Color::Black);
		Void CopyTo(Void* RenderTarget, PixelFormat specific = PixelFormat::B8G8R8A8);


		Serface& operator=(const Serface& other);
		Serface& operator=(Serface&& other);
	private:
		Void CopyFrom(const Serface& other);
		Void SwapWith(Serface& other);
	};
}