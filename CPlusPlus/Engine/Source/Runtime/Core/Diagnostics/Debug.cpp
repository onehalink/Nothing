#include "Debug.h"


// Tag uses to select console or file as output
#define USE_CONSOLE_AS_OUTPUT


#if defined(PLATFORM_WINDOWS)
#include "../../Platform/Windows/Windows.h"
#endif


#if defined(USE_CONSOLE_AS_OUTPUT)
    #if !defined(PLATFORM_WINDOWS)
    #include <iostream>
    #endif
#else
    #include <fstream>
#endif



namespace Engine
{
    constexpr const Char8* Tags[] =
    {
        "Trace",
        "Warn",
        "Error",
    };


	Void Debug::Log(Level level, const U8String& message)
	{
    #if defined(PLATFORM_WINDOWS)
        SYSTEMTIME datetime;
        GetLocalTime( &datetime );

        U8String format = "[{Year}/{Month}/{Day} {Hour}:{Minute}:{Second}][{Tag}]: {Message}\n";
        U8String combined = Format(
            format,
            datetime.wYear, datetime.wMonth, datetime.wDay, datetime.wHour, datetime.wMinute, datetime.wSecond,
            Tags[ static_cast<EnumUnderlyingType<Level>>(level) ],
            message
        );
    #else
        U8String format = "[{Tag}]: {Message}\n";
        U8String combined = Format( Tags[ static_cast<EnumUnderlyingType<Level>>(level) ], message );
    #endif


    #if defined(USE_CONSOLE_AS_OUTPUT)
        #if defined(PLATFORM_WINDOWS)
            constexpr UInt16 R = FOREGROUND_RED;
            constexpr UInt16 G = FOREGROUND_GREEN;
            constexpr UInt16 B = FOREGROUND_BLUE;

            constexpr UInt16 White  = R | G | B;
            constexpr UInt16 Yellow = R | G;
            constexpr UInt16 Red    = R;


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

            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handle, textAttributes);

            U16String u16 = static_cast<U16String>(combined);
            WriteConsoleW( handle, u16.GetBuffer(), u16.GetCount(), nullptr, nullptr );
        #else
            std::cout << combined;
        #endif
    #else
        static std::fstream output( "engine.log", std::ios::out | std::ios::app );
        output << combined;
    #endif
	}
}