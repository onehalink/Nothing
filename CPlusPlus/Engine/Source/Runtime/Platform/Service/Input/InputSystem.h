#pragma once

#include "Keyboard.h"
#include "Mouse.h"



namespace Engine
{
	struct ENGINE_API InputSystem
	{
		KeyState			keys[ Enum::To( Key::Count ) ];

		MouseButtonState	mouseButtons[ Enum::To( MouseButton::Count ) ];
		Vector2Int			mousePosition;
		Int32				mouseWheelValue;

		Char32				inputChar32s[8];
		Int32				inputChar32WritePosition;


		InputSystem();


		Void UpdateKeyState(Key key, KeyState state);
		Void UpdateMouseButtonState(MouseButton mouseButton, MouseButtonState mouseButtonState);
		Void AddInputChar32(Char32 unicode);

		Void Reset();


		Bool KeyPressed(Key key) const;
		Bool KeyReleased(Key key) const;
		Bool KeyClicked(Key key) const;

		Bool MouseButtonPressed(MouseButton mouseButton) const;
		Bool MouseButtonReleased(MouseButton mouseButton) const;
		Bool MouseButtonClicked(MouseButton mouseButton) const;
	};
}