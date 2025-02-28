#include "InputSystem.h"



namespace Engine
{
	InputSystem::InputSystem()
	{
		MemoryClear(this, 1);
	}

	Void InputSystem::UpdateKeyState(Key key, KeyState keyState)
	{
		Enum::Add( keys[ Enum::To(key) ], keyState );
	}

	Void InputSystem::UpdateMouseButtonState(MouseButton mouseButton, MouseButtonState mouseButtonState)
	{
		Enum::Add( mouseButtons[ Enum::To(mouseButton) ], mouseButtonState );
	}

	Void InputSystem::AddInputChar32(Char32 unicode)
	{
		if ( unicode < ' ' )
			return;

		// currently only ASCII chars are supported
		if (unicode > 0x7F)
			return;

		if ( inputChar32WritePosition >= CountArray(inputChar32s) - 1 )
			return;

		inputChar32s[inputChar32WritePosition]		= unicode;
		inputChar32s[ ++inputChar32WritePosition ]	= '\0';
	}

	Void InputSystem::Reset()
	{
		for (KeyState& key : keys)
			if( Enum::HasAll( key, KeyState::Click ) )
				Enum::Remove( key, KeyState::Click );

		for (MouseButtonState& mouseButton : mouseButtons)
			if( Enum::HasAll( mouseButton, MouseButtonState::Click ) )
				Enum::Remove( mouseButton, MouseButtonState::Click );

		inputChar32s[ inputChar32WritePosition = 0 ] = '\0';
	}

	Bool InputSystem::KeyPressed(Key key) const
	{
		return Enum::HasAll( keys[ Enum::To(key) ], KeyState::Press );
	}

	Bool InputSystem::KeyReleased(Key key) const
	{
		return Enum::HasAll( keys[ Enum::To(key) ], KeyState::Release );
	}

	Bool InputSystem::KeyClicked(Key key) const
	{
		return Enum::HasAll( keys[ Enum::To(key) ], KeyState::Click );
	}

	Bool InputSystem::MouseButtonPressed(MouseButton mouseButton) const
	{
		return Enum::HasAll( mouseButtons[ Enum::To(mouseButton) ], MouseButtonState::Press );
	}

	Bool InputSystem::MouseButtonReleased(MouseButton mouseButton) const
	{
		return Enum::HasAll( mouseButtons[ Enum::To(mouseButton) ], MouseButtonState::Release );
	}

	Bool InputSystem::MouseButtonClicked(MouseButton mouseButton) const
	{
		return Enum::HasAll( mouseButtons[ Enum::To(mouseButton) ], MouseButtonState::Click );
	}
}