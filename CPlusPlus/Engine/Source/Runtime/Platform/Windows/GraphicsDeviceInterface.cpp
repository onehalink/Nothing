#include "GraphicsDeviceInterface.h"

#include "Windows.h"



namespace Engine::Windows
{
	GraphicsDeviceInterface::GraphicsDeviceInterface(Void* windowHandle)
	{
		this->windowHandle	= windowHandle;
		targetDeviceContext = GetDC( reinterpret_cast<HWND>(windowHandle) );
		memoryDeviceContext = CreateCompatibleDC( reinterpret_cast<HDC>(targetDeviceContext) );
	}

	GraphicsDeviceInterface::~GraphicsDeviceInterface()
	{
		DeleteDC( reinterpret_cast<HDC>(memoryDeviceContext) );
		ReleaseDC( reinterpret_cast<HWND>(windowHandle), reinterpret_cast<HDC>(targetDeviceContext) );
	}

	Void GraphicsDeviceInterface::Present(SizeType width, SizeType height, Action<Void*> Fn)
	{
		HDC targetDeviceContext = reinterpret_cast<HDC>( this->targetDeviceContext );
		HDC memoryDeviceContext = reinterpret_cast<HDC>( this->memoryDeviceContext );

		Void* RenderTarget	= nullptr;
		HBITMAP hBitmap		= nullptr;
		{
			BITMAPINFO descriptor;
			MemoryClear( &descriptor );
			descriptor.bmiHeader.biSize		= sizeof(descriptor);
			descriptor.bmiHeader.biWidth	= width;
			descriptor.bmiHeader.biHeight	= height;
			descriptor.bmiHeader.biPlanes	= 1;
			descriptor.bmiHeader.biBitCount	= 8 * 4;

			hBitmap = CreateDIBSection( memoryDeviceContext, &descriptor, DIB_RGB_COLORS, &RenderTarget, nullptr, 0 );
		}

		if (hBitmap)
		{
			Fn(RenderTarget);

			SelectObject(memoryDeviceContext, hBitmap);
			BitBlt(targetDeviceContext, 0, 0, width, height, memoryDeviceContext, 0, 0, SRCCOPY);
			DeleteObject(hBitmap);
		}
	}
}