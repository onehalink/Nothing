#include "Texture.h"



namespace Engine
{
	Texture::Texture()
	{
		MemoryOp::Clear( this, sizeof(Texture) );
	}

	Texture::Texture(SizeType width, SizeType height, PixelFormat format)
	{
		this->width		= width;
		this->height	= height;
		this->format	= format;

		texelSize	= GetPixelStoreSize(format);
		storage		= Memory<Byte>( width * height * texelSize );
	}

	Texture::Texture(const Texture& other)
	{
		CopyFrom(other);
	}

	Texture::Texture(Texture&& other)
	{
		SwapWith(other);
	}

	Texture::~Texture()
	{

	}

	Void Texture::SetPixel(SizeType x, SizeType y, UInt32 pixel)
	{
		MemoryOp::Copy( &pixel, storage.GetBuffer() + ( width * y + x ) * texelSize, texelSize );
	}

	UInt32 Texture::GetPixel(SizeType x, SizeType y) const
	{
		UInt32 ret;
		MemoryOp::Copy( storage.GetBuffer() + ( width * y + x ) * texelSize, &ret, texelSize );

		return ret;
	}

	Void Texture::FlipHorizontal()
	{
		SizeType halfWidth = width / 2;
		for (SizeType y = 0; y < height; y++)
			for (SizeType x = 0; x < halfWidth; x++)
				for (SizeType iteration = 0; iteration < texelSize; iteration++)
					Swap(
						storage.GetBuffer() + ( width * y + x					) * texelSize + iteration,
						storage.GetBuffer() + ( width * y + ( width - 1 - x )	) * texelSize + iteration
					);
	}

	Void Texture::FlipVertical()
	{
		SizeType halfHeight = height / 2;
		for (SizeType y = 0; y < halfHeight; y++)
			for (SizeType x = 0; x < width; x++)
				for (SizeType iteration = 0; iteration < texelSize; iteration++)
					Swap(
						storage.GetBuffer() + ( width * y					+ x ) * texelSize + iteration,
						storage.GetBuffer() + ( width * ( height - 1 - y )	+ x ) * texelSize + iteration
					);
	}

	Texture Texture::ConvertPixelFormat(PixelFormat specific) const
	{
		Function<Color, UInt32> OpA = nullptr;
		switch (format)
		{
		case PixelFormat::R8G8B8:
			OpA = FromR8G8B8;
			break;
		case PixelFormat::R8G8B8A8:
			OpA = FromR8G8B8A8;
			break;
		case PixelFormat::B8G8R8:
			OpA = FromB8G8R8;
			break;
		case PixelFormat::B8G8R8A8:
			OpA = FromB8G8R8A8;
			break;
		}

		Function<UInt32, const Color&> OpB = nullptr;
		switch (specific)
		{
		case PixelFormat::R8G8B8:
			OpB = ToR8G8B8;
			break;
		case PixelFormat::R8G8B8A8:
			OpB = ToR8G8B8A8;
			break;
		case PixelFormat::B8G8R8:
			OpB = ToB8G8R8;
			break;
		case PixelFormat::B8G8R8A8:
			OpB = ToB8G8R8A8;
			break;
		}

		Texture ret(width, height, specific);

		for (SizeType y = 0; y < height; y++)
			for (SizeType x = 0; x < width; x++)
				ret.SetPixel(
					x, y,
					OpB( OpA( GetPixel(x, y) ) )
				);

		return ret;
	}

	Texture& Texture::operator=(const Texture& other)
	{
		CopyFrom(other);

		return *this;
	}

	Texture& Texture::operator=(Texture&& other)
	{
		SwapWith(other);

		return *this;
	}

	Void Texture::CopyFrom(const Texture& other)
	{
		storage = other.storage;

		width		= other.width;
		height		= other.height;
		format		= other.format;
		texelSize	= other.texelSize;
	}

	Void Texture::SwapWith(Texture& other)
	{
		storage = Move( other.storage );

		Swap( &width,		&other.width		);
		Swap( &height,		&other.height		);
		Swap( &format,		&other.format		);
		Swap( &texelSize,	&other.texelSize	);
	}
}
