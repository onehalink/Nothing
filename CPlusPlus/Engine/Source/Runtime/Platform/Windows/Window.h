#pragma once

#include "../Service/Input/InputSystem.h"



namespace Engine::Windows
{
	struct ENGINE_API Window : NonCopyable
	{
		Void*		handle;	// A Windows window handle that indicates which window it is on the desktop
		SizeType	width;	// The width of client area of this window
		SizeType	height;	// The height of client area of this window


		Window();
		~Window();


		// Create a Windows window and display it on the desktop
		Void Create(const U8String& title = "Default Window", SizeType width = 1280, SizeType height = 720, Void* userParameter = nullptr);
		// Poll events from OS
		Void Update();


		Void SetTitle(const U8String& title);
		Void SetResizable(Bool enable);
	};
}