#include "EventSystem.h"



namespace Engine
{
	EventSystem::EventSystem()
	{
		Memory::Clear( this, sizeof(EventSystem) );
	}

	Bool EventSystem::KeyPressed(Key key) const
	{
		return ( keys[ static_cast<EnumUnderlyingType<Key>>(key) ] & KeyState::Press ) == KeyState::Press;
	}

	Bool EventSystem::KeyReleased(Key key) const
	{
		return ( keys[ static_cast<EnumUnderlyingType<Key>>(key) ] & KeyState::Release ) == KeyState::Release;
	}

	Bool EventSystem::KeyClicked(Key key) const
	{
		return ( keys[ static_cast<EnumUnderlyingType<Key>>(key) ] & KeyState::Click ) == KeyState::Click;
	}

	Bool EventSystem::MouseButtonPressed(MouseButton button) const
	{
		return ( buttons[ static_cast<EnumUnderlyingType<MouseButton>>(button) ] & MouseButtonState::Press ) == MouseButtonState::Press;
	}

	Bool EventSystem::MouseButtonReleased(MouseButton button) const
	{
		return ( buttons[ static_cast<EnumUnderlyingType<MouseButton>>(button) ] & MouseButtonState::Release ) == MouseButtonState::Release;
	}

	Bool EventSystem::MouseButtonClicked(MouseButton button) const
	{
		return ( buttons[ static_cast<EnumUnderlyingType<MouseButton>>(button) ] & MouseButtonState::Click ) == MouseButtonState::Click;
	}

	Void EventSystem::AddWindowResizedEvent(SizeType width, SizeType height)
	{
		Event event;
		event.type								= Event::Type::WindowResized;
		event.WindowResizedParameters.width		= width;
		event.WindowResizedParameters.height	= height;

		eventQueue.Add(event);
	}

	Void EventSystem::AddWindowFocusedEvent(Bool focused)
	{
		Event event;
		event.type								= Event::Type::WindowFocused;
		event.WindowFocusedParameters.focused	= focused;

		eventQueue.Add(event);
	}

	Void EventSystem::AddWindowClosedEvent()
	{
		Event event;
		event.type = Event::Type::WindowClosed;
		
		eventQueue.Add(event);
	}

	Void EventSystem::AddKeyTypedEvent(Key key, KeyState state)
	{
		Event event;
		event.type						= Event::Type::KeyTyped;
		event.KeyTypedParameters.key	= key;
		event.KeyTypedParameters.state	= state;
		
		eventQueue.Add(event);
	}

	Void EventSystem::AddMouseButtonTypedEvent(MouseButton button, MouseButtonState state)
	{
		Event event;
		event.type								= Event::Type::MouseButtonTyped;
		event.MouseButtonTypedParameters.button	= button;
		event.MouseButtonTypedParameters.state	= state;

		eventQueue.Add(event);
	}

	Void EventSystem::AddMouseMovedEvent(Int32 x, Int32 y)
	{
		Event event;
		event.type						= Event::Type::MouseMoved;
		event.MouseMovedParameters.x	= x;
		event.MouseMovedParameters.y	= y;

		eventQueue.Add(event);
	}

	Void EventSystem::AddMouseWheelScrolledEvent(Int32 delta)
	{
		Event event;
		event.type									= Event::Type::MouseWheelScrolled;
		event.MouseWheelScrolledParameters.delta	= delta;

		eventQueue.Add(event);
	}

	Void EventSystem::Reset()
	{
		for (SizeType index = 0; index < KeyCount; index++)
			if ( ( keys[index] & KeyState::Click ) == KeyState::Click )
				keys[index] &= ~KeyState::Click;

		for ( SizeType index = 0; index < ButtonCount; index++ )
			if ( ( buttons[index] & MouseButtonState::Click ) == MouseButtonState::Click )
				buttons[index] &= ~MouseButtonState::Click;

		eventQueue.Clear();
	}
}