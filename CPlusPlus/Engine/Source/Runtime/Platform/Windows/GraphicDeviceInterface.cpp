#include "GraphicDeviceInterface.h"

#include "Windows.h"



namespace Engine::Windows
{
	GraphicDeviceInterface::GraphicDeviceInterface(Void* windowHandle)
	{
		this->windowHandle	= windowHandle;
		targetDeviceContext = GetDC( reinterpret_cast<HWND>(windowHandle) );
		memoryDeviceContext = CreateCompatibleDC( reinterpret_cast<HDC>(targetDeviceContext) );
	}

	GraphicDeviceInterface::~GraphicDeviceInterface()
	{
		DeleteDC( reinterpret_cast<HDC>(memoryDeviceContext) );
		ReleaseDC( reinterpret_cast<HWND>(windowHandle), reinterpret_cast<HDC>(targetDeviceContext) );
	}

	Void GraphicDeviceInterface::Present(SizeType width, SizeType height, RenderCallback Fn)
	{
		HDC targetDeviceContext = reinterpret_cast<HDC>( this->targetDeviceContext );
		HDC memoryDeviceContext = reinterpret_cast<HDC>( this->memoryDeviceContext );

		Void* RenderTarget	= nullptr;
		HBITMAP hBitmap		= nullptr;
		{
			BITMAPINFO descriptor;
			MemoryOp::Clear( &descriptor );
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