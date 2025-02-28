#include "Window.h"

#include "Windows.h"



namespace Engine::Windows
{
	constexpr const Char16* WindowClassName = L"Class Entry";


	static Key KeyMap(Int32 keyCode)
	{
		if ( IsBetween(keyCode, VK_F1, VK_F12) )
			return Key( static_cast<Int32>( Key::F1		) + ( keyCode - VK_F1	) );

		if ( IsBetween(keyCode, '0', '9') )
			return Key( static_cast<Int32>( Key::Zero	) + ( keyCode - '0'		) );

		if ( IsBetween(keyCode, 'A', 'Z') )
			return Key( static_cast<Int32>( Key::A		) + ( keyCode - 'A'		) );

		switch (keyCode)
		{
		case VK_ESCAPE:		return Key::Escape;
		case VK_BACK:		return Key::BackSpace;
		case VK_TAB:		return Key::Tabulation;
		case VK_CAPITAL:	return Key::CapitalsLock;
		case VK_RETURN:		return Key::Enter;
		case VK_SPACE:		return Key::SpaceBar;

		case VK_INSERT:		return Key::Insert;
		case VK_DELETE:		return Key::Delete;
		case VK_HOME:		return Key::Home;
		case VK_END:		return Key::End;
		case VK_PRIOR:		return Key::PageUp;
		case VK_NEXT:		return Key::PageDown;

		case VK_LEFT:		return Key::LeftArrow;
		case VK_RIGHT:		return Key::RightArrow;
		case VK_DOWN:		return Key::DownArrow;
		case VK_UP:			return Key::UpArrow;


		case VK_SHIFT:		return Key::Shift;
		case VK_CONTROL:	return Key::Control;
		case VK_LWIN:
		case VK_RWIN:		return Key::Window;
		case VK_MENU:		return Key::Alternate;


		case VK_OEM_3:		return Key::GraveAccent;
		case VK_OEM_MINUS:	return Key::Minus;
		case VK_OEM_PLUS:	return Key::Equal;
		case VK_OEM_4:		return Key::LeftSquareBracket;
		case VK_OEM_6:		return Key::RightSquareBracket;
		case VK_OEM_5:		return Key::BackSlash;
		case VK_OEM_1:		return Key::Semicolon;
		case VK_OEM_7:		return Key::Apostrophe;
		case VK_OEM_COMMA:	return Key::Comma;
		case VK_OEM_PERIOD: return Key::Period;
		case VK_OEM_2:		return Key::Slash;
		}

		return Key::Unknown;
	}

	static MouseButton MouseButtonMap(Int32 mouseButtonCode)
	{
		switch (mouseButtonCode)
		{
		case 0x01: return MouseButton::Left;
		case 0x02: return MouseButton::Right;
		case 0x10: return MouseButton::Middle;
		}

		return MouseButton::Unknown;
	}

	static LRESULT WINAPI WindowProcedure(HWND handle, UINT message, WPARAM parameter0, LPARAM parameter1)
	{
		static Void* userParameter = nullptr;
		if ( message == WM_CREATE )
		{
			userParameter = reinterpret_cast<CREATESTRUCTW*>(parameter1)->lpCreateParams;

			return LRESULT(0);
		}

		if ( !userParameter )
			return DefWindowProcW(handle, message, parameter0, parameter1);

		InputSystem* inputSystem = reinterpret_cast<InputSystem*>(userParameter);
		switch (message)
		{
		case WM_SIZE:
		{
			SizeType width	= ( parameter1 >>  0 ) & 0xFFFF;
			SizeType height = ( parameter1 >> 16 ) & 0xFFFF;

			inputSystem->OnWindowResized(width, height);
		}
			break;
		case WM_SETFOCUS:
		case WM_KILLFOCUS:
			inputSystem->OnWindowFocused( message == WM_SETFOCUS );
			break;
		case WM_CLOSE:
		case WM_DESTROY:
			inputSystem->OnWindowClosed();
			break;

		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		{
			Key key = KeyMap(parameter0);
			if (
				key == Key::Alternate ||
				key == Key::F10
				)
				inputSystem->UpdateKeyState( key, KeyState::Click );
		}
			break;
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			Key key = KeyMap(parameter0);

			// dont received WM_KEYUP message, and need mannually to add it
			if ( key == Key::Window )
			{
				inputSystem->UpdateKeyState( Key::Window, KeyState::Click );

				break;
			}

			inputSystem->UpdateKeyState(
				key,
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

			inputSystem->UpdateMouseButtonState(
				!released ? MouseButtonMap(parameter0)	: MouseButtonMap(lastParameter0),
				!released ? MouseButtonState::Press		: MouseButtonState::Release
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

			y = y < height ? height - 1 - y :
				-( y - ( height - 1 ) );

			inputSystem->mousePosition = { x, y };
		}
			break;
		case WM_MOUSEWHEEL:
			inputSystem->mouseWheelValue += static_cast<Int16>( ( parameter0 >> 16 ) & 0xFFFF ) / WHEEL_DELTA;
			break;
		case WM_CHAR:
		{
			static Char16 buffer[2];

			UInt32 unicode;
			// high surrogate
			if ( ( parameter0 & 0xFC00 ) == 0xD800 )
			{
				buffer[0] = parameter0;

				break;
			}
			// low surrogate
			else if ( ( parameter0 & 0xFC00 ) == 0xDC00 )
			{
				buffer[1] = parameter0;

				FromUTF<TextEncoding::UTF16>( &unicode, buffer );
			}
			else
			{
				unicode = parameter0;
			}

			inputSystem->AddInputChar32(unicode);
		}
			break;
		default:
			return DefWindowProcW(handle, message, parameter0, parameter1);
		}

		return LRESULT(0);
	}


	Window::Window()
	{

	}

	Window::~Window()
	{
		UnregisterClassW( WindowClassName, GetModuleHandleW(nullptr) );
	}

	Void Window::Create(const U8String& title, SizeType width, SizeType height, Void* userParameter)
	{
		UInt32 style		= WS_OVERLAPPEDWINDOW;
		UInt32 extendStyle	= 0;

		{
			WNDCLASSEXW descriptor;
			MemoryClear( &descriptor );
			descriptor.cbSize			= sizeof(descriptor);
			descriptor.hInstance		= GetModuleHandleW(nullptr);
			descriptor.lpszClassName	= WindowClassName;
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
			WindowClassName,
			static_cast<U16String>(title),
			style,
			CW_USEDEFAULT, CW_USEDEFAULT, realWidth, realHeight,
			nullptr, nullptr, GetModuleHandleW(nullptr), userParameter
		);
		ShowWindow(handle, SW_SHOWDEFAULT);

		{
			this->handle	= handle;
			this->width		= width;
			this->height	= height;
		}
	}

	Void Window::Update()
	{
		MSG message;
		while ( PeekMessageW( &message, reinterpret_cast<HWND>(handle), 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &message );
			DispatchMessageW( &message );
		}
	}

	Void Window::SetTitle(const U8String& title)
	{
		SetWindowTextW( reinterpret_cast<HWND>(handle), static_cast<U16String>(title) );
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
}
