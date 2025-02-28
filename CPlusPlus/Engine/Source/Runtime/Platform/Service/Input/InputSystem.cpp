#include "InputSystem.h"



namespace Engine
{
	InputSystem::InputSystem()
	{
		MemoryClear(this);

		OnWindowClosed	= []() {};
		OnWindowFocused = [](Bool) {};
		OnWindowResized = [](SizeType, SizeType) {};
	}

	Void InputSystem::UpdateKeyState(Key key, KeyState keyState)
	{
		keys[ static_cast<EnumUnderlyingType<Key>>(key) ] |= keyState;
	}

	Void InputSystem::UpdateMouseButtonState(MouseButton mouseButton, MouseButtonState mouseButtonState)
	{
		mouseButtons[ static_cast<EnumUnderlyingType<MouseButton>>(mouseButton) ] |= mouseButtonState;
	}

	Void InputSystem::AddInputChar32(Char32 unicode)
	{
		if ( unicode < ' ' )
			return;

		if ( inputChar32WritePosition >= InputSystem::MaxinimuInputChar32Count - 1 )
			return;

		inputChar32s[inputChar32WritePosition]		= unicode;
		inputChar32s[ ++inputChar32WritePosition ]	= '\0';
	}

	Void InputSystem::Reset()
	{
		for (KeyState& key : keys)
			if ( ( key & KeyState::Click ) == KeyState::Click )
				key &= ~KeyState::Click;

		for (KeyState& mouseButton : mouseButtons)
			if ( ( mouseButton & MouseButtonState::Click ) == MouseButtonState::Click )
				mouseButton &= ~MouseButtonState::Click;

		inputChar32s[ inputChar32WritePosition = 0 ] = '\0';
	}

	Bool InputSystem::KeyPressed(Key key) const
	{
		return ( keys[ static_cast<EnumUnderlyingType<Key>>(key) ] & KeyState::Press ) == KeyState::Press;
	}

	Bool InputSystem::KeyReleased(Key key) const
	{
		return ( keys[ static_cast<EnumUnderlyingType<Key>>(key) ] & KeyState::Release) == KeyState::Release;
	}

	Bool InputSystem::KeyClicked(Key key) const
	{
		return ( keys[ static_cast<EnumUnderlyingType<Key>>(key) ] & KeyState::Click ) == KeyState::Click;
	}

	Bool InputSystem::MouseButtonPressed(MouseButton mouseButton) const
	{
		return ( mouseButtons[ static_cast<EnumUnderlyingType<MouseButton>>(mouseButton) ] & MouseButtonState::Press ) == MouseButtonState::Press;
	}

	Bool InputSystem::MouseButtonReleased(MouseButton mouseButton) const
	{
		return ( mouseButtons[ static_cast<EnumUnderlyingType<MouseButton>>(mouseButton) ] & MouseButtonState::Release) == MouseButtonState::Release;
	}

	Bool InputSystem::MouseButtonClicked(MouseButton mouseButton) const
	{
		return ( mouseButtons[ static_cast<EnumUnderlyingType<MouseButton>>(mouseButton) ] & MouseButtonState::Click) == MouseButtonState::Click;
	}
}