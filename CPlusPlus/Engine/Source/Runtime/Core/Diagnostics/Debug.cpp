#include "Debug.h"

#if defined(PLATFORM_WINDOWS)
#include "../../Platform/Windows/Windows.h"
#endif



namespace Engine
{
	Void Debug::Log(Level level, const U8String& message)
	{
	#if defined(PLATFORM_WINDOWS)
		constexpr UInt16 R          = FOREGROUND_RED;
		constexpr UInt16 G          = FOREGROUND_GREEN;
		constexpr UInt16 B          = FOREGROUND_BLUE;

		constexpr UInt16 White      = R | G | B;
		constexpr UInt16 Yellow     = R | G;
		constexpr UInt16 Red        = R;


        UInt16 textAttributes = 0;
        switch (level)
        {
        case Level::Trace:
            textAttributes = White;
            break;
        case Level::Warn:
            textAttributes = Yellow;
            break;
        case Level::Error:
            textAttributes = Red;
            break;
        }

        U8String tag;
        switch (level)
        {
        case Level::Trace:
            tag = "Trace";
            break;
        case Level::Warn:
            tag = "Warn";
            break;
        case Level::Error:
            tag = "Error";
            break;
        }

        HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(outputHandle, textAttributes);

        Datetime datetime = Datetime::GetChinaStandardTime();

        U8String format     = "[{Year}/{Month}/{Day} {Hour}:{Minute}:{Second}][{Tag}]: {Message}\n";
        U8String combined   = Format(
            format,
            datetime.year, datetime.month, datetime.day, datetime.hour, datetime.minute, datetime.second,
            tag,
            message
        );

        U16String u16 = static_cast<U16String>(combined);
        WriteConsoleW( outputHandle, u16.GetBuffer(), u16.GetCount(), nullptr, nullptr );
	#else
	#error No implementation
	#endif
	}
}