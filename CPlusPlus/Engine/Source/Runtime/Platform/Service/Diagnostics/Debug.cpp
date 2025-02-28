#include "Debug.h"


// Tag uses to select console or file as output
#define USE_CONSOLE_AS_OUTPUT


#if defined(PLATFORM_WINDOWS)
#include "../../Windows/Windows.h"
#endif


#if defined(USE_CONSOLE_AS_OUTPUT)
    #if !defined(PLATFORM_WINDOWS)
    #include <iostream>
    #endif
#else
    #include "../FileSystem/File.h"
#endif



namespace Engine
{
    U8StringView Tags[] =
    {
        "Trace",
        "Warn",
        "Error",
    };


#if defined(PLATFORM_WINDOWS)
    static U8StringView format = "[{Year}/{Month}/{Day} {Hour}:{Minute}:{Second}][{Tag}]: {Message}\n";
#else
    static U8StringView format = "[{Tag}]: {Message}\n";
#endif


    Void Debug::Log(Level level, U8StringView message)
	{
    #if defined(PLATFORM_WINDOWS)
        SYSTEMTIME datetime;
        GetLocalTime( &datetime );

        U8String combined = Format(
            format,
            datetime.wYear, datetime.wMonth, datetime.wDay, datetime.wHour, datetime.wMinute, datetime.wSecond,
            Tags[ Enum::To(level) ],
            message
        );
    #else
        U8String combined   = Format( format, Tags[ Enum::To(level) ],, message );
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
        static File file( "engine.log", File::Mode::Write );
        file.Write( { reinterpret_cast<Byte*>( combined.GetBuffer() ), combined.GetCount() } );
    #endif
	}
}