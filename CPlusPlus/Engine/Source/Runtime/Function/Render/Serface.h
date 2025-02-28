#pragma once

#include "../Interface/IRenderable.h"



namespace Engine
{
	struct ENGINE_API Serface : IRenderable
	{
		Memory<Color>	storage;
		SizeType		width;
		SizeType		height;

		RectangleInt	scissorRectangle;


		Serface();
		Serface(SizeType width, SizeType height);
		Serface(Serface&& other);
		Serface(const Serface& other);
		Serface& operator=(Serface&& other);
		Serface& operator=(const Serface& other);


		virtual Void SetPixel(SizeType x, SizeType y, Color color) override;
		virtual const Color& GetPixel(SizeType x, SizeType y) const override;
		virtual Void SetScissorRectangle(const RectangleInt& scissorRectangle) override;
		virtual const RectangleInt& GetScissorRectangle() const override;


		Void Clear(Color clearColor = Color::Black);
		Void CopyTo(Void* target);
	private:
		Void SwapWith(Serface& other);
		Void CopyFrom(const Serface& other);
	};
}