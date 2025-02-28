#include "Icon.h"

#include "Windows.h"



namespace Engine::Windows
{
	const Cursor Icon::Arrow		= LoadCursorW(nullptr, IDC_ARROW);
	const Cursor Icon::Ibeam		= LoadCursorW(nullptr, IDC_IBEAM);
	const Cursor Icon::Wait			= LoadCursorW(nullptr, IDC_WAIT);
	const Cursor Icon::Cross		= LoadCursorW(nullptr, IDC_CROSS);
	const Cursor Icon::UpArrow		= LoadCursorW(nullptr, IDC_UPARROW);
	const Cursor Icon::SizeNWSE		= LoadCursorW(nullptr, IDC_SIZENWSE);
	const Cursor Icon::SizeNESW		= LoadCursorW(nullptr, IDC_SIZENESW);
	const Cursor Icon::SizeWE		= LoadCursorW(nullptr, IDC_SIZEWE);
	const Cursor Icon::SizeNS		= LoadCursorW(nullptr, IDC_SIZENS);
	const Cursor Icon::SizeAll		= LoadCursorW(nullptr, IDC_SIZEALL);
	const Cursor Icon::No			= LoadCursorW(nullptr, IDC_NO);
	const Cursor Icon::Hand			= LoadCursorW(nullptr, IDC_HAND);
	const Cursor Icon::AppStarting	= LoadCursorW(nullptr, IDC_APPSTARTING);
	const Cursor Icon::Help			= LoadCursorW(nullptr, IDC_HELP);
	const Cursor Icon::Pin			= LoadCursorW(nullptr, IDC_PIN);
	const Cursor Icon::Persion		= LoadCursorW(nullptr, IDC_PERSON);


	Icon::Icon(Void* handle)
		: handle(handle)
	{
	
	}

	Icon::Icon(const Texture& texture, Bool asSystemCursor, SizeType xHotspot, SizeType yHotspot)
	{
		ASSERT(
			texture.format != PixelFormat::R8G8B8		&&
			texture.format != PixelFormat::R8G8B8A8		&&
			texture.format != PixelFormat::B8G8R8		&&
			texture.format != PixelFormat::B8G8R8A8,
			"Unsupported pixel format"
		);

		SizeType width			= texture.width;
		SizeType height			= texture.height;
		PixelFormat format		= texture.format;
		SizeType channelCount	= texture.texelSize;

		SizeType imageSize = width * height * texture.texelSize;

		HBITMAP mask = nullptr;
		if ( channelCount == 4 )
		{
			SizeType size = width * height * 1;
			Memory<Byte> temporary(size);

			for (SizeType y = 0; y < height; y++)
				for (SizeType x = 0; x < width; x++)
					temporary[ width * y + x ] = texture.GetPixel(x, y) >> 24; // alpha

			mask = CreateBitmap( width, height, 1, 8, temporary.GetBuffer() );
		}
		else
			mask = CreateBitmap(width, height, 1, 1, nullptr);

		HBITMAP color = nullptr;
		{
			BITMAPINFO descriptor;
			MemoryOp::Clear( &descriptor );
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
				MemoryOp::Copy( texture.storage.GetBuffer(), target, imageSize );
				break;
			}
		}

		{
			ICONINFO descriptor;
			MemoryOp::Clear( &descriptor );
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

	Icon::Icon(const U8String& executableFilePath)
	{
		handle = ExtractIconW( nullptr, static_cast<U16String>(executableFilePath), 0 );
	}

	Icon::~Icon()
	{
		DestroyIcon( reinterpret_cast<HICON>(handle) );
	}

	Void Icon::AttachToWindow(Void* windowHandle) const
	{
		SendMessageW(
			reinterpret_cast<HWND>(windowHandle),
			WM_SETICON,
			ICON_SMALL,
			reinterpret_cast<LPARAM>(handle)
		);

		SendMessageW(
			reinterpret_cast<HWND>(windowHandle),
			WM_SETICON,
			ICON_BIG,
			reinterpret_cast<LPARAM>(handle)
		);
	}

	Void Icon::SetAsSystemCursor() const
	{
		::SetCursor( reinterpret_cast<HCURSOR>(handle) );
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
					MemoryOp::Clear( &descriptor, sizeof(descriptor) );
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
}