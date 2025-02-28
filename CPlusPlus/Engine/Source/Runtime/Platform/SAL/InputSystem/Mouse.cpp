#include "Mouse.h"



namespace Engine
{
	Mouse::Mouse()
	{
		MemoryOp::Clear( buttons, sizeof(buttons) );

		position	= Vector2Int::Zero;
		wheelValue	= 0;
	}

	Void Mouse::UpdateButtonState(Button button, State state)
	{
		buttons[ static_cast<EnumUnderlyingType<Button>>(button) ] |= state;
	}

	Bool Mouse::ButtonPressed(Button button) const
	{
		return ( buttons[ static_cast<EnumUnderlyingType<Button>>(button) ] & State::Press ) == State::Press;
	}

	Bool Mouse::ButtonReleased(Button button) const
	{
		return ( buttons[ static_cast<EnumUnderlyingType<Button>>(button) ] & State::Release ) == State::Release;
	}

	Bool Mouse::ButtonClicked(Button button) const
	{
		return ( buttons[ static_cast<EnumUnderlyingType<Button>>(button) ] & State::Click ) == State::Click;
	}

	Void Mouse::Reset()
	{
		for (SizeType index = 0; index < ButtonCount; index++)
		{
			State& selected = buttons[index];
			if ( ( selected & State::Click ) == State::Click )
				selected &= ~State::Click;
		}
	}

	Mouse::Button Mouse::ButtonMap(Int32 buttonCode)
	{
	#if defined(PLATFORM_WINDOWS)
		switch (buttonCode)
		{
		case 0x01: return Button::Left;
		case 0x02: return Button::Right;
		case 0x10: return Button::Middle;
		}
	#else
	#error No implementation
	#endif

		return Button::Unknown;
	}
}