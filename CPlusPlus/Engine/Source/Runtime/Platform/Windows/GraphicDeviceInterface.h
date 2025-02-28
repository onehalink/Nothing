#pragma once

/**
* Windows GDI wrapper
*/

#include "../../Core.h"



namespace Engine::Windows
{
	class ENGINE_API GraphicDeviceInterface : INonCopyable
	{
	public:
		using RenderCallback = Action<Void*>;


		GraphicDeviceInterface(Void* windowHandle);
		~GraphicDeviceInterface();


		/**
		* Overwrite RenderTarget by a function pointer(Fn) to update the client area of the window 
		* 
		* @remark
		* A pointer(RenderTarget) point to heap memory's size in bytes defined by width * height * 4
		* RenderTarget's pixel format is B8G8R8A8
		*/
		Void Present(SizeType width, SizeType height, RenderCallback Fn);
	private:
		Void* handle;
		Void* memoryDeviceContext;
		Void* targetDeviceContext;
	};
}