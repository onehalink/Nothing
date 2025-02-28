#pragma once

/**
* Windows GDI wrapper
*/

#include "../../Core.h"



namespace Engine::Windows
{
	class ENGINE_API GraphicsDeviceInterface
	{
	public:
		NONCOPYABLE(GraphicsDeviceInterface)
		GraphicsDeviceInterface(Void* windowHandle);
		~GraphicsDeviceInterface();


		/**
		* Overwrite RenderTarget by a function pointer(Fn) to update the client area of the window 
		* 
		* @remark
		* A pointer(RenderTarget) point to heap memory's size in bytes defined by width * height * 4
		* RenderTarget's pixel format is B8G8R8A8
		*/
		Void Present(SizeType width, SizeType height, Action<Void*> Fn /** Void Callback(Void* RenderTarget) */);
	private:
		Void* windowHandle;
		Void* memoryDeviceContext;
		Void* targetDeviceContext;
	};
}