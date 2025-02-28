#include "Mouse.h"

#if defined(PLATFORM_WINDOWS)
#include "../Windows/Windows.h"
#endif



namespace Engine
{
	MouseButton MouseButtonMap(Int32 platformSpecificMouseCode)
	{
	#if defined(PLATFORM_WINDOWS)
		switch (platformSpecificMouseCode)
		{
		case 0x01: return MouseButton::Left;
		case 0x02: return MouseButton::Right;
		case 0x10: return MouseButton::Middle;
		}
	#else
	#error No implementation
	#endif

		return MouseButton::Unknown;
	}
}