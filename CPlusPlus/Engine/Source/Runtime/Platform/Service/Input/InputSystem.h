#pragma once

#include "Keyboard.h"
#include "Mouse.h"



namespace Engine
{
	struct ENGINE_API InputSystem
	{
		static constexpr SizeType KeyCount					= static_cast<EnumUnderlyingType<Key>>(Key::Count);
		static constexpr SizeType MouseButtonCount			= static_cast<EnumUnderlyingType<MouseButton>>(MouseButton::Count);

		static constexpr SizeType MaxinimuInputChar32Count	= 16;


		Action<>					OnWindowClosed;
		Action<Bool>				OnWindowFocused;
		Action<SizeType, SizeType>	OnWindowResized;


		KeyState					keys[KeyCount];

		MouseButtonState			mouseButtons[MouseButtonCount];
		Vector2Int					mousePosition;
		Int32						mouseWheelValue;

		Char32						inputChar32s[MaxinimuInputChar32Count];
		Int32						inputChar32WritePosition;


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