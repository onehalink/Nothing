#pragma once

#include "2DGeometry.h"
#include "IDrawable.h"



namespace Engine
{
	struct ENGINE_API FrameBuffer : IDrawable
	{
		enum class ClearFlag
		{
			Color = 1 << 0,

			All = Color,
		};
		CLASS_ENUMCLASS_FLAGS(ClearFlag);


		Span<Color> colorBuffer;

		SizeType width;
		SizeType height;
		SizeType elementCount;
		RealType aspect;


		FrameBuffer();
		FrameBuffer(SizeType width, SizeType height);
		FrameBuffer(const FrameBuffer& other);
		FrameBuffer(FrameBuffer&& other);
		~FrameBuffer();


		Void SetPixel(SizeType x, SizeType y, const Color& color) override;
		const Color& GetPixel(SizeType x, SizeType y) const override;
		RectangleInt SafeArea() const override;

		Void Clear(ClearFlag flags = ClearFlag::Color, const Color& clearColor = Color::Black);
		Void CopyTo(Void* RenderTarget, PixelFormat specific = PixelFormat::B8G8R8A8);


		FrameBuffer& operator=(const FrameBuffer& other);
		FrameBuffer& operator=(FrameBuffer&& other);
	private:
		Void CopyFrom(const FrameBuffer& other);
		Void SwapWith(FrameBuffer& other);
	};
}