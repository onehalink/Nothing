#include "Texture.h"



namespace Engine
{
	Texture::Texture()
	{
		MemoryClear(this);
	}

	Texture::Texture(SizeType width, SizeType height, PixelFormat format)
	{
		storage = { width * height };

		this->format	= format;
		this->width		= width;
		this->height	= height;

		switch (format)
		{
		case PixelFormat::R8:
			channelCount	= 1;
			texelSize		= 1;
			break;
		case PixelFormat::R8G8:
			channelCount	= 2;
			texelSize		= 2;
			break;
		case PixelFormat::R8G8B8:
			channelCount	= 3;
			texelSize		= 3;
			break;
		case PixelFormat::R8G8B8A8:
			channelCount	= 4;
			texelSize		= 4;
			break;

		case PixelFormat::B8G8R8:
			channelCount	= 3;
			texelSize		= 3;
			break;
		case PixelFormat::B8G8R8A8:
			channelCount	= 4;
			texelSize		= 4;
			break;
		default:
			ASSERT(false);
			break;
		}
	}

	Texture::Texture(Texture&& other)
	{
		SwapWith(other);
	}

	Texture::Texture(const Texture& other)
	{
		CopyFrom(other);
	}

	Texture& Texture::operator=(Texture&& other)
	{
		SwapWith(other);

		return *this;
	}

	Texture& Texture::operator=(const Texture& other)
	{
		CopyFrom(other);

		return *this;
	}

	Void Texture::SetPixel(SizeType x, SizeType y, UInt32 pixel)
	{
		Buffer::Copy( storage.GetBuffer() + ( width * y + x ) * texelSize, &pixel, texelSize );
	}

	UInt32 Texture::GetPixel(SizeType x, SizeType y) const
	{
		UInt32 result;
		Buffer::Copy( &result, storage.GetBuffer() + ( width * y + x ) * texelSize, texelSize );

		return result;
	}

	Void Texture::FlipHorizontal()
	{
		for (SizeType y = 0; y < height; ++y)
			for (SizeType x = 0; x < width / 2; ++x)
			{
				SizeType offsetL = ( width * y + x					) * texelSize;
				SizeType offsetR = ( width * y + ( width - 1 - x )	) * texelSize;

				UInt32 temporary;
				auto a = storage.GetBuffer() + offsetL;
				auto b = storage.GetBuffer() + offsetR;

				Buffer::Copy( &temporary,	a,			texelSize );
				Buffer::Copy( a,			b,			texelSize );
				Buffer::Copy( b,			&temporary,	texelSize );
			}
	}

	Void Texture::FlipVertical()
	{
		SizeType strideSize = width * texelSize;

		Memory<Byte> buffer(strideSize);

		for (SizeType y = 0; y < height / 2; ++y)
		{
			SizeType offsetB = strideSize * y;
			SizeType offsetT = strideSize * ( height - 1 - y );

			auto a = storage.GetBuffer() + offsetB;
			auto b = storage.GetBuffer() + offsetT;

			Buffer::Copy( buffer.GetBuffer(),	a,					strideSize );
			Buffer::Copy( a,					b,					strideSize );
			Buffer::Copy( b,					buffer.GetBuffer(), strideSize );
		}
	}

	Texture Texture::Convert(PixelFormat specific) const
	{
		auto ReverseR8G8B8OrB8G8R8 = [](Void* output, const Void* input)
			{
				auto from	= reinterpret_cast<const Byte*>(input);
				auto to		= reinterpret_cast<Byte*>(output);

				to[0] = from[2];
				to[1] = from[1];
				to[2] = from[0];
			};
		auto ReverseR8G8B8A8OrB8G8R8A8 = [=](Void* output, const Void* input)
			{
				ReverseR8G8B8OrB8G8R8(output, input);

				reinterpret_cast<Byte*>(output)[3] = reinterpret_cast<const Byte*>(input)[3];
			};


		Texture result(width, height, specific);

		Action<Void*, const Void*> ConvertToR8G8B8A8;
		switch (format)
		{
		case PixelFormat::R8:
		case PixelFormat::R8G8:
		case PixelFormat::R8G8B8:
		case PixelFormat::R8G8B8A8:
			ConvertToR8G8B8A8 = [=](Void* output, const Void* input)
				{
					MemoryCopy(output, input, texelSize);
				};
			break;

		case PixelFormat::B8G8R8:
			ConvertToR8G8B8A8 = ReverseR8G8B8OrB8G8R8;
			break;
		case PixelFormat::B8G8R8A8:
			ConvertToR8G8B8A8 = ReverseR8G8B8A8OrB8G8R8A8;
			break;
		}

		Action<Void*, const Void*> ConvertFromR8G8B8A8;
		switch (specific)
		{
		case PixelFormat::R8:
		case PixelFormat::R8G8:
		case PixelFormat::R8G8B8:
		case PixelFormat::R8G8B8A8:
			ConvertFromR8G8B8A8 = [&result](Void* output, const Void* input)
				{
					MemoryCopy( output, input, result.texelSize );
				};
			break;

		case PixelFormat::B8G8R8:
			ConvertFromR8G8B8A8 = ReverseR8G8B8OrB8G8R8;
			break;
		case PixelFormat::B8G8R8A8:
			ConvertFromR8G8B8A8 = ReverseR8G8B8A8OrB8G8R8A8;
			break;
		}

		for (SizeType y = 0; y < height; y++)
			for (SizeType x = 0; x < width; x++)
			{
				SizeType offset = ( width * y + x ) * texelSize;

				UInt32 temporary = 0;
				ConvertToR8G8B8A8( &temporary, storage.GetBuffer() + offset	);
				ConvertFromR8G8B8A8( result.storage.GetBuffer(), &temporary );
			}

		return result;
	}

	Void Texture::SwapWith(Texture& other)
	{
		storage = Move( other.storage );

		Swap( &format,			&other.format		);
		Swap( &channelCount,	&other.channelCount	);
		Swap( &texelSize,		&other.texelSize	);
		Swap( &width,			&other.width		);
		Swap( &height,			&other.height		);
	}

	Void Texture::CopyFrom(const Texture& other)
	{
		storage			= other.storage;
		format			= other.format;
		channelCount	= other.channelCount;
		texelSize		= other.texelSize;
		width			= other.width;
		height			= other.height;
	}
}