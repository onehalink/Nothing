#include "Serface.h"



namespace Engine
{
	Serface::Serface()
	{
		storage				= { };
		width				= 0;
		height				= 0;
		scissorRectangle	= { 0, 0, 0, 0 };
	}

	Serface::Serface(SizeType width, SizeType height)
	{
		storage				= { width * height };
		this->width			= width;
		this->height		= height;
		scissorRectangle	= { Vector2Int::Zero, Vector2Int(width, height) };
	}

	Serface::Serface(Serface&& other)
	{
		SwapWith(other);
	}

	Serface::Serface(const Serface& other)
	{
		CopyFrom(other);
	}

	Serface& Serface::operator=(Serface&& other)
	{
		SwapWith(other);

		return *this;
	}

	Serface& Serface::operator=(const Serface& other)
	{
		CopyFrom(other);

		return *this;
	}

	Void Serface::SetPixel(SizeType x, SizeType y, Color color)
	{
		storage[ width * y + x ] = color;
	}

	const Color& Serface::GetPixel(SizeType x, SizeType y) const
	{
		return storage[ width * y + x ];
	}

	Void Serface::SetScissorRectangle(const RectangleInt& scissorRectangle)
	{
		this->scissorRectangle =
		{
			Maximum( Vector2Int::Zero,			scissorRectangle.minimum ),
			Minimum( Vector2Int(width, height), scissorRectangle.maximum ),
		};
	}

	const RectangleInt& Serface::GetScissorRectangle() const
	{
		return scissorRectangle;
	}

	Void Serface::Clear(Color clearColor)
	{
		for (SizeType index = 0; index < storage.GetCount(); ++index)
			storage[index] = clearColor;
	}

	Void Serface::CopyTo(Void* target)
	{
	#if defined(PLATFORM_WINDOWS)
		for (SizeType index = 0; index < storage.GetCount(); ++index)
		{
			auto& from	= storage[index];
			auto& to	= reinterpret_cast<UInt32*>(target)[index];

			to =
				( from.r << 16 ) |
				( from.g <<  8 ) |
				( from.b <<  0 );
		}
	#else
		// do nothing here
	#endif
	}

	Void Serface::SwapWith(Serface& other)
	{
		storage = Move( other.storage );

		Swap( &width,				&other.width			);
		Swap( &height,				&other.height			);
		Swap( &scissorRectangle,	&other.scissorRectangle	);
	}

	Void Serface::CopyFrom(const Serface& other)
	{
		storage				= other.storage;
		width				= other.width;
		height				= other.height;
		scissorRectangle	= other.scissorRectangle;
	}
}