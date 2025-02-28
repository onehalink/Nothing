#pragma once

#include "../SoftwareAbstractLayer/EventSystem.h"

#include "Cursor.h"



namespace Engine::Windows
{
	class ENGINE_API Window : INonCopyable
	{
	public:
		Window();
		~Window();


		// Create a Windows window and display it on the desktop
		Void Create(const U16String& title = "Default Window", SizeType width = 1280, SizeType height = 720, Void* userParameter = nullptr);
		// Poll events from OS
		Void Update();
		
		Void SetTitle(const U16String& title);
		Void SetResizable(Bool enable);

		Void SetIcon(const Icon& icon);
		Void SetCursor(const Cursor& cursor);

		Void SetWidth(SizeType width);
		Void SetHeight(SizeType height);


		Void* GetHandle() const;
		SizeType GetWidth() const;
		SizeType GetHeight() const;
	private:
		Void* handle; // A Windows window handle that indicates which window it is on the desktop

		SizeType width;		// The width of client area of this window
		SizeType height;	// The height of client area of this window


		U16String windowClassName; // Internal usage only
	};
}