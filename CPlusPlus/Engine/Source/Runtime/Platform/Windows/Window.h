#pragma once

#include "../Service/Input/InputSystem.h"



namespace Engine::Windows
{
	struct ENGINE_API Window
	{
		Action<SizeType, SizeType>	OnResize;
		Action<Bool>				OnFocus;
		Action<>					OnClose;

		Void*		handle;	// A Windows window handle that indicates which window it is on the desktop
		SizeType	width;	// The width of client area of this window
		SizeType	height;	// The height of client area of this window

		InputSystem* inputSystem;


		NONCOPYABLE(Window)
		Window();
		~Window();


		// Create a Windows window and display it on the desktop
		Void Create(const U16String& title = L"Default Window", SizeType width = 1280, SizeType height = 720);
		// Poll events from OS
		Void Update();


		Void Attach(InputSystem* inputSystem);


		Void SetTitle(const U16String& title);
		Void SetResizable(Bool enable);


		// Invoked by OS
		Int64 OnEvent(UInt32 message, UInt64 parameter0, Int64 parameter1);
	};
}