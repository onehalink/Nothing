#include "Keyboard.h"

#if defined(PLATFORM_WINDOWS)
#include "../../Windows/Windows.h"
#endif



namespace Engine
{
	Keyboard::Keyboard()
	{
		MemoryOp::Clear( keys, sizeof(keys) );
	}

	Void Keyboard::UpdateKeyState(Key key, State state)
	{
		keys[ static_cast<EnumUnderlyingType<Key>>(key) ] |= state;
	}

	Bool Keyboard::KeyPressed(Key key) const
	{
		return ( keys[ static_cast<EnumUnderlyingType<Key>>(key) ] & State::Press ) == State::Press;
	}

	Bool Keyboard::KeyReleased(Key key) const
	{
		return ( keys[ static_cast<EnumUnderlyingType<Key>>(key) ] & State::Release ) == State::Release;
	}

	Bool Keyboard::KeyClicked(Key key) const
	{
		return ( keys[ static_cast<EnumUnderlyingType<Key>>(key) ] & State::Click ) == State::Click;
	}

	Void Keyboard::Reset()
	{
		for (SizeType index = 0; index < KeyCount; index++)
		{
			State& selected = keys[index];
			if ( ( selected & State::Click ) == State::Click )
				selected &= ~State::Click;
		}
	}

    Char8 Keyboard::GetKeyContent(Key key, Bool shiftDown)
	{
		constexpr const Char8* NumberTables[] =
		{
			"0123456789",
			")!@#$%^&*("
		};

		constexpr const Char8* PunctuationTables[] =
		{
			"`-=[]\\;',./",
			"~_+{}|:\"<>?",
		};


		Int32 value = static_cast<Int32>(key);

		{
			Int32 begin	= static_cast<Int32>( Key::Zero );
			Int32 end	= static_cast<Int32>( Key::Nine );
			if ( IsBetween<Int32>(value, begin, end) )
				return NumberTables[ !shiftDown ? 0 : 1 ][ value - begin ];
		}

		{
			Int32 begin	= static_cast<Int32>( Key::Apostrophe );
			Int32 end	= static_cast<Int32>( Key::Slash );
			if ( IsBetween<Int32>(value, begin, end) )
				return PunctuationTables[ !shiftDown ? 0 : 1 ][ value - begin ];
		}

		return '\0';
	}

	Keyboard::Key Keyboard::KeyMap(Int32 keyCode)
	{
	#if defined(PLATFORM_WINDOWS)
		if ( IsBetween<Int32>(keyCode, VK_F1, VK_F12) )
			return Key( static_cast<Int32>( Key::F1 ) + ( keyCode - VK_F1 ) );

		if ( IsBetween<Int32>(keyCode, '0', '9') )
			return Key( static_cast<Int32>( Key::Zero ) + ( keyCode - '0' ) );

		if ( IsBetween<Int32>(keyCode, 'A', 'Z') )
			return Key( static_cast<Int32>( Key::A ) + ( keyCode - 'A' ) );

		switch (keyCode)
		{
		case VK_ESCAPE:		return Key::Escape;
		case VK_BACK:		return Key::BackSlash;
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
	#else
	#error No implementation
	#endif

		return Key::Unknown;
	}
}
