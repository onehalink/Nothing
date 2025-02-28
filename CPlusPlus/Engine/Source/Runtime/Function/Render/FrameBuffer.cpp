#include "FrameBuffer.h"



namespace Engine
{
	FrameBuffer::FrameBuffer()
	{

	}

	FrameBuffer::FrameBuffer(SizeType width, SizeType height)
	{
		elementCount = width * height;
		if ( elementCount == 0 )
			return;

		colorBuffer = Span<Color>(elementCount);

		this->width		= width;
		this->height	= height;
	}

	FrameBuffer::FrameBuffer(const FrameBuffer& other)
	{
		CopyFrom(other);
	}

	FrameBuffer::FrameBuffer(FrameBuffer&& other)
	{
		colorBuffer = Move( other.colorBuffer );

		width			= other.width;
		height			= other.height;
		elementCount	= other.elementCount;
		aspect			= other.aspect;
	}

	FrameBuffer::~FrameBuffer()
	{

	}

	Void FrameBuffer::SetPixel(SizeType x, SizeType y, const Color& color)
	{
		colorBuffer[ width * y + x ] = color;
	}

	const Color& FrameBuffer::GetPixel(SizeType x, SizeType y) const
	{
		return colorBuffer[ width * y + x ];
	}

	RectangleInt FrameBuffer::SafeArea() const
	{
		return RectangleInt( Vector2Int::Zero, Vector2Int(width, height) );
	}

	Void FrameBuffer::Clear(ClearFlag flags, const Color& clearColor)
	{
		if ( ( flags & ClearFlag::Color ) == ClearFlag::Color )
			for (auto& color : colorBuffer)
				color = clearColor;
	}

	Void FrameBuffer::CopyTo(Void* RenderTarget, PixelFormat specific)
	{
		switch (specific)
		{
		case PixelFormat::B8G8R8A8:
			for (SizeType index = 0; index < elementCount; index++)
				reinterpret_cast<UInt32*>(RenderTarget)[index] = ToB8G8R8A8( colorBuffer[index] );
			break;
		}
	}

	FrameBuffer& FrameBuffer::operator=(const FrameBuffer& other)
	{
		CopyFrom(other);

		return *this;
	}

	FrameBuffer& FrameBuffer::operator=(FrameBuffer&& other)
	{
		colorBuffer = Move( other.colorBuffer );

		Swap( &width,			&other.width		);
		Swap( &height,			&other.height		);
		Swap( &elementCount,	&other.elementCount	);
		Swap( &aspect,			&other.aspect		);

		return *this;
	}

	Void FrameBuffer::CopyFrom(const FrameBuffer& other)
	{
		colorBuffer		= other.colorBuffer;
		width			= other.width;
		height			= other.height;
		elementCount	= other.elementCount;
		aspect			= other.aspect;
	}
}