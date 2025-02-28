#include "Serface.h"



namespace Engine
{
	Serface::Serface()
	{
		width			= 0;
		height			= 0;
		elementCount	= 0;
	}

	Serface::Serface(SizeType width, SizeType height)
	{
		elementCount	= width * height;
		storage			= Span<Color>(elementCount);

		this->width		= width;
		this->height	= height;
	}

	Serface::Serface(const Serface& other)
	{
		CopyFrom(other);
	}

	Serface::Serface(Serface&& other)
	{
		SwapWith(other);
	}

	Serface::~Serface()
	{

	}

	Void Serface::Clear(const Color& clearColor)
	{
		for (auto& color : storage)
			color = clearColor;
	}

	Void Serface::CopyTo(Void* RenderTarget, PixelFormat specific)
	{
		switch (specific)
		{
		case PixelFormat::B8G8R8A8:
			for (SizeType index = 0; index < elementCount; index++)
				reinterpret_cast<UInt32*>(RenderTarget)[index] = ToB8G8R8A8( storage[index] );
			break;
		}
	}

	Void Serface::SetPixel(SizeType x, SizeType y, const Color& color)
	{
		storage[ width * y + x ] = color;
	}

	const Color& Serface::GetPixel(SizeType x, SizeType y) const
	{
		return storage[ width * y + x ];
	}

	RectangleInt Serface::SafeArea() const
	{
		return RectangleInt( Vector2Int::Zero, Vector2Int(width, height) );
	}

	Serface& Serface::operator=(const Serface& other)
	{
		CopyFrom(other);

		return *this;
	}

	Serface& Serface::operator=(Serface&& other)
	{
		SwapWith(other);

		return *this;
	}

	Void Serface::CopyFrom(const Serface& other)
	{
		storage			= other.storage;
		width			= other.width;
		height			= other.height;
		elementCount	= other.elementCount;
	}

	Void Serface::SwapWith(Serface& other)
	{
		storage = Move(other.storage);

		Swap( &width,			&other.width	);
		Swap( &height,			&other.height	);
		Swap( &elementCount,	&elementCount	);
	}
}