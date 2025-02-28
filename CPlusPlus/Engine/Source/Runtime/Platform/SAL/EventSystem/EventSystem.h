#pragma once

#include "../../HAL/Keyboard.h"
#include "../../HAL/Mouse.h"



namespace Engine
{
	struct ENGINE_API EventSystem
	{
		struct Event
		{
			enum class Type
			{
				WindowResized,
				WindowFocused,
				WindowClosed,

				KeyTyped,

				MouseButtonTyped,
				MouseMoved,
				MouseWheelScrolled,
			};


			Type type;
			union
			{
				struct
				{
					SizeType width;
					SizeType height;
				} WindowResizedParameters;


				struct
				{
					Bool focused;
				} WindowFocusedParameters;


				struct
				{
					Key			key;
					KeyState	state;
				} KeyTypedParameters;


				struct
				{
					MouseButton			button;
					MouseButtonState	state;
				} MouseButtonTypedParameters;


				struct
				{
					Int32 x;
					Int32 y;
				} MouseMovedParameters;


				struct
				{
					Int32 delta;
				} MouseWheelScrolledParameters;
			};
		};


		static constexpr SizeType KeyCount		= static_cast<EnumUnderlyingType<Key>>( Key::Count );
		static constexpr SizeType ButtonCount	= static_cast<EnumUnderlyingType<MouseButton>>( MouseButton::Count );


		KeyState			keys[KeyCount];
		MouseButtonState	buttons[ButtonCount];

		Vector2Int	mousePosition;
		Int32		mouseWheelValue;

		DynamicArray<Event> eventQueue;


		EventSystem();


		Bool KeyPressed(Key key) const;
		Bool KeyReleased(Key key) const;
		Bool KeyClicked(Key key) const;

		Bool MouseButtonPressed(MouseButton button) const;
		Bool MouseButtonReleased(MouseButton button) const;
		Bool MouseButtonClicked(MouseButton button) const;


		Void AddWindowResizedEvent(SizeType width, SizeType height);
		Void AddWindowFocusedEvent(Bool focused);
		Void AddWindowClosedEvent();

		Void AddKeyTypedEvent(Key key, KeyState state);

		Void AddMouseButtonTypedEvent(MouseButton button, MouseButtonState state);
		Void AddMouseMovedEvent(Int32 x, Int32 y);
		Void AddMouseWheelScrolledEvent(Int32 delta);

		Void Reset();
	};
}