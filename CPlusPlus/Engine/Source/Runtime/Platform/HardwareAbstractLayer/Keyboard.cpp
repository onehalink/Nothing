#include "Keyboard.h"

#if defined(PLATFORM_WINDOWS)
#include "../Windows/Windows.h"
#endif



namespace Engine
{
	Char8 GetKeyContent(Key key, Bool shiftDown)
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
			if ( IsBetweenClosed<Int32>(value, begin, end) )
				return NumberTables[ !shiftDown ? 0 : 1 ][ value - begin ];
		}

		{
			Int32 begin	= static_cast<Int32>( Key::Apostrophe );
			Int32 end	= static_cast<Int32>( Key::Slash );
			if ( IsBetweenClosed<Int32>(value, begin, end) )
				return PunctuationTables[ !shiftDown ? 0 : 1 ][ value - begin ];
		}

		return NullTerminator;
	}

	Key KeyMap(Int32 platformSpecificKeyCode)
	{
	#if defined(PLATFORM_WINDOWS)
		if ( IsBetweenClosed<Int32>(platformSpecificKeyCode, VK_F1, VK_F12) )
			return Key( static_cast<Int32>( Key::F1 ) + ( platformSpecificKeyCode - VK_F1 ) );

		if ( IsBetweenClosed<Int32>(platformSpecificKeyCode, '0', '9') )
			return Key( static_cast<Int32>( Key::Zero ) + ( platformSpecificKeyCode - '0' ) );

		if ( IsBetweenClosed<Int32>(platformSpecificKeyCode, 'A', 'Z') )
			return Key( static_cast<Int32>( Key::A ) + ( platformSpecificKeyCode - 'A' ) );

		switch (platformSpecificKeyCode)
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