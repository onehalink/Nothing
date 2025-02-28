#include "Window.h"

#include "Windows.h"



namespace Engine::Windows
{
	static LRESULT WINAPI WindowProcedure(HWND handle, UINT message, WPARAM parameter0, LPARAM parameter1)
	{
		static Void* userParameter = nullptr;
		if ( message == WM_CREATE )
		{
			userParameter = reinterpret_cast<CREATESTRUCTW*>(parameter1)->lpCreateParams;

			return 1;
		}

		if ( !userParameter )
			return DefWindowProcW(handle, message, parameter0, parameter1);

		EventSystem* eventSystem = reinterpret_cast<EventSystem*>(userParameter);
		switch (message)
		{
		case WM_SIZE:
			eventSystem->AddWindowResizedEvent(
				( parameter1 >>  0 ) & 0xFFFF,
				( parameter1 >> 16 ) & 0xFFFF
			);
			break;
		case WM_SETFOCUS:
		case WM_KILLFOCUS:
			eventSystem->AddWindowFocusedEvent( message == WM_SETFOCUS );
			break;
		case WM_CLOSE:
		case WM_DESTROY:
			eventSystem->AddWindowClosedEvent();
			break;

		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		{
			Key key = KeyMap(parameter0);
			if (
				key == Key::Alternate ||
				key == Key::F10
				)
				eventSystem->AddKeyTypedEvent( key, KeyState::Click );
		}
			break;
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			// dont received WM_KEYUP message, and need mannually to add it
			if ( KeyMap(parameter0) == Key::Window )
			{
				eventSystem->AddKeyTypedEvent( Key::Window, KeyState::Click );

				break;
			}

			eventSystem->AddKeyTypedEvent(
				KeyMap(parameter0),
				message == WM_KEYDOWN ? KeyState::Press : KeyState::Release
			);
		}
			break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		{
			// index of the last mouse button
			static WPARAM lastParameter0;

			// the last mouse button had been released if parameter0 == 0
			Bool released = parameter0 == 0 ? true : false;

			HWND captured = GetCapture();
			if( !captured )
				SetCapture(handle);
			else if( released && captured == handle )
				ReleaseCapture();

			eventSystem->AddMouseButtonTypedEvent(
				!released ? MouseButtonMap(parameter0) : MouseButtonMap(lastParameter0),
				!released ? MouseButtonState::Press : MouseButtonState::Release
			);

			lastParameter0 = parameter0;
		}
			break;
		case WM_MOUSEMOVE:
		{
			Int32 height;
			{
				RECT rect;
				GetClientRect( handle, &rect );

				height = rect.bottom - rect.top;
			}

			Int16 x = ( parameter1 >>  0 ) & 0xFFFF;
			Int16 y = ( parameter1 >> 16 ) & 0xFFFF;

			y =
				y < height ?
				height - 1 - y :
				-( y - ( height - 1 ) );

			eventSystem->AddMouseMovedEvent(x, y);
		}
			break;
		case WM_MOUSEWHEEL:
		{
			Int32 value = static_cast<Int16>( ( parameter0 >> 16 ) & 0xFFFF );

			eventSystem->AddMouseWheelScrolledEvent( value / WHEEL_DELTA );
		}
			break;
		default:
			return DefWindowProcW(handle, message, parameter0, parameter1);
		}

		return 1;
	}


	Window::Window()
	{
		handle = nullptr;

		width	= 0;
		height	= 0;

		windowClassName = "Window Class Entry";
	}

	Window::~Window()
	{
		UnregisterClassW( static_cast<U16String>(windowClassName), GetModuleHandleW(nullptr) );
	}

	Void Window::Create(const U16String& title, SizeType width, SizeType height, Void* userParameter)
	{
		UInt32 style		= WS_OVERLAPPEDWINDOW;
		UInt32 extendStyle	= 0;

		{
			WNDCLASSEXW descriptor;
			Memory::Clear( &descriptor, sizeof(descriptor) );
			descriptor.cbSize			= sizeof(descriptor);
			descriptor.hInstance		= GetModuleHandleW(nullptr);
			descriptor.lpszClassName	= windowClassName;
			descriptor.lpfnWndProc		= WindowProcedure;

			RegisterClassExW( &descriptor );
		}

		SizeType realWidth;
		SizeType realHeight;
		{
			RECT rect = { 0, 0, width, height };
			AdjustWindowRectEx( &rect, style, false, extendStyle );

			realWidth	= rect.right - rect.left;
			realHeight	= rect.bottom - rect.top;
		}

		HWND handle = CreateWindowExW(
			extendStyle,
			windowClassName,
			static_cast<U16String>(title),
			style,
			CW_USEDEFAULT, CW_USEDEFAULT, realWidth, realHeight,
			nullptr, nullptr, GetModuleHandleW(nullptr), userParameter
		);
		ShowWindow(handle, SW_SHOWDEFAULT);

		this->handle	= handle;
		this->width		= width;
		this->height	= height;
	}

	Void Window::Update()
	{
		MSG message;
		while ( PeekMessageW( &message, reinterpret_cast<HWND>(handle), 0, 0, PM_REMOVE ) )
		{
			DispatchMessageW( &message );
		}
	}

	Void Window::SetTitle(const U16String& title)
	{
		SetWindowTextW( reinterpret_cast<HWND>(handle), title );
	}

	Void Window::SetResizable(Bool enable)
	{
		LONG_PTR previous = GetWindowLongPtrW( reinterpret_cast<HWND>(handle), GWL_STYLE );

		LONG_PTR current;
		if (enable)
			current = previous | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
		else
			current = previous & ~WS_THICKFRAME & ~WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX;

		SetWindowLongPtrW( reinterpret_cast<HWND>(handle), GWL_STYLE, current );
	}

	Void Window::SetIcon(const Icon& icon)
	{
		SendMessageW(
			reinterpret_cast<HWND>(handle),
			WM_SETICON,
			ICON_SMALL,
			reinterpret_cast<LPARAM>( icon.GetHandle() )
		);

		SendMessageW(
			reinterpret_cast<HWND>(handle),
			WM_SETICON,
			ICON_BIG,
			reinterpret_cast<LPARAM>( icon.GetHandle() )
		);
	}

	Void Window::SetCursor(const Cursor& cursor)
	{
		::SetCursor(reinterpret_cast<HCURSOR>( cursor.GetHandle() ) );
	}

	Void Window::SetWidth(SizeType width)
	{
		this->width = width;
	}

	Void Window::SetHeight(SizeType height)
	{
		this->height = height;
	}

	Void* Window::GetHandle() const
	{
		return handle;
	}

	SizeType Window::GetWidth() const
	{
		return width;
	}

	SizeType Window::GetHeight() const
	{
		return height;
	}
}
