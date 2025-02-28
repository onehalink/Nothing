#include "Window.h"

#include "Windows.h"



namespace Engine::Windows
{
	constexpr const Char16* WindowClassName = L"Class Entry";


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
			Keyboard::Key key = Keyboard::KeyMap(parameter0);
			if (
				key == Keyboard::Key::Alternate ||
				key == Keyboard::Key::F10
				)
				inputSystem->keyboard.UpdateKeyState( key, Keyboard::State::Click );
		}
			break;
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			Keyboard::Key key = Keyboard::KeyMap(parameter0);

			// dont received WM_KEYUP message, and need mannually to add it
			if ( key == Keyboard::Key::Window )
			{
				inputSystem->keyboard.UpdateKeyState( key, Keyboard::State::Click );

				break;
			}

			inputSystem->keyboard.UpdateKeyState(
				key,
				message == WM_KEYDOWN ? Keyboard::State::Press : Keyboard::State::Release
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

			inputSystem->mouse.UpdateButtonState(
				!released ? Mouse::ButtonMap(parameter0)	: Mouse::ButtonMap(lastParameter0),
				!released ? Mouse::State::Press				: Mouse::State::Release
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

			inputSystem->mouse.position = { x, y };
		}
			break;
		case WM_MOUSEWHEEL:
			inputSystem->mouse.wheelValue += static_cast<Int16>( ( parameter0 >> 16 ) & 0xFFFF ) / WHEEL_DELTA;
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
			MemoryOp::Clear( &descriptor );
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
