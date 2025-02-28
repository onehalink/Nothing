#include "Icon.h"

#include "Windows.h"



namespace Engine::Windows
{
	Icon::Icon(Void* handle)
		: handle(handle)
	{
	
	}

	Icon::Icon(const Texture& texture, Bool asSystemCursor, SizeType xHotspot, SizeType yHotspot)
	{
		SizeType width	= texture.width;
		SizeType height	= texture.height;

		PixelFormat format		= texture.format;
		SizeType channelCount	= texture.texelSize;

		SizeType texelSize = texture.texelSize;
		SizeType imageSize = width * height * texelSize;

		if (
			format != PixelFormat::R8G8B8 &&
			format != PixelFormat::R8G8B8A8 &&
			format != PixelFormat::B8G8R8 &&
			format != PixelFormat::B8G8R8A8
			)
		{
			handle = nullptr;
			return;
		}

		HBITMAP mask = nullptr;
		if ( channelCount == 4 )
		{
			SizeType size = width * height * 1;
			Span<Byte> temporary(size);

			for (SizeType y = 0; y < height; y++)
				for (SizeType x = 0; x < height; x++)
					temporary[width * y + x] = texture.GetPixel(x, y) >> 24; // alpha

			mask = CreateBitmap( width, height, 1, 8, temporary.GetBuffer() );
		}
		else
			mask = CreateBitmap(width, height, 1, 1, nullptr);

		HBITMAP color = nullptr;
		{
			BITMAPINFO descriptor;
			Memory::Clear( &descriptor, sizeof(descriptor) );
			descriptor.bmiHeader.biSize		= sizeof(descriptor);
			descriptor.bmiHeader.biWidth	= width;
			descriptor.bmiHeader.biHeight	= height;
			descriptor.bmiHeader.biBitCount	= 8 * channelCount;
			descriptor.bmiHeader.biPlanes	= 1;

			Void* target;
			color = CreateDIBSection( GetDC(nullptr), &descriptor, DIB_RGB_COLORS, &target, nullptr, 0 );

			switch (format)
			{
			case PixelFormat::R8G8B8:
			case PixelFormat::R8G8B8A8:
				for (SizeType index = 0; index < imageSize; index += channelCount)
				{
					auto from	= reinterpret_cast<const Byte*>( texture.storage.GetBuffer() ) + index;
					auto to		= reinterpret_cast<Byte*>(target) + index;

					for (SizeType iteration = 0; iteration < 3; iteration++)
						to[iteration] = from[ 2 - iteration ];

					// alpha
					if ( channelCount == 4 )
						to[3] = from[3];
				}
				break;
			default:
				Memory::Copy( texture.storage.GetBuffer(), target, imageSize );
				break;
			}
		}

		{
			ICONINFO descriptor;
			Memory::Clear( &descriptor, sizeof(descriptor) );
			descriptor.fIcon	= !asSystemCursor;
			descriptor.xHotspot = xHotspot;
			descriptor.yHotspot = height - 1 - yHotspot;
			descriptor.hbmMask	= mask;
			descriptor.hbmColor	= color;

			handle = CreateIconIndirect( &descriptor );
		}

		DeleteObject(mask);
		DeleteObject(color);
	}

	Icon::Icon(const U16String& executableFilePath)
	{
		handle = ExtractIconW(nullptr, executableFilePath, 0);
	}

	Icon::~Icon()
	{
		DestroyIcon( reinterpret_cast<HICON>(handle) );
	}

	Texture Icon::Extract() const
	{
		// extract image pixels from HBITMAP
		auto Fn = [](HBITMAP hBitmap)
			{
				SizeType width;
				SizeType height;
				SizeType channelCount;
				{
					BITMAP descriptor;
					GetObjectW( hBitmap, sizeof(BITMAP), &descriptor );

					width			= descriptor.bmWidth;
					height			= descriptor.bmHeight;
					channelCount	= descriptor.bmBitsPixel / 8;
				}

				Texture ret(
					width,
					height,
					channelCount == 3 ? PixelFormat::B8G8R8 : PixelFormat::B8G8R8A8
				);
				{
					BITMAPINFO descriptor;
					Memory::Clear( &descriptor, sizeof(descriptor) );
					descriptor.bmiHeader.biSize		= sizeof(descriptor);
					descriptor.bmiHeader.biWidth	= width;
					descriptor.bmiHeader.biHeight	= height;
					descriptor.bmiHeader.biPlanes	= 1;
					descriptor.bmiHeader.biBitCount	= 8 * channelCount;

					GetDIBits( GetDC(nullptr), hBitmap, 0, height, ret.storage.GetBuffer(), &descriptor, DIB_RGB_COLORS );
				}

				return ret;
			};


		HBITMAP mask;
		HBITMAP color;
		{
			ICONINFO descriptor;
			GetIconInfo( reinterpret_cast<HICON>(handle), &descriptor );

			mask	= descriptor.hbmMask;
			color	= descriptor.hbmColor;
		}

		auto ret = Fn(color);

		DeleteObject(mask);
		DeleteObject(color);

		return ret;
	}

	Void* Icon::GetHandle() const
	{
		return nullptr;
	}
}