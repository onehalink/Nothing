#include "LogSystem.h"

#if defined(PLATFORM_WINDOWS)
#include "../../Platform/Windows/Windows.h"
#endif

#include <fstream>



namespace Engine
{
    LogSystem LogSystem::ConsoleLogger  = { LogSystem::Output::Console };
    LogSystem LogSystem::FileLogger     = { LogSystem::Output::File, "engine.log" };


    LogSystem::LogSystem(Output output, const U8String& outputFileName)
    {
        this->output            = output;
        this->file              = nullptr;
        this->outputFileName    = outputFileName;

        if( output == Output::File )
            this->file = new std::fstream( outputFileName, std::ios::out | std::ios::app );
    }

    LogSystem::~LogSystem()
    {
        if ( output == Output::File )
            delete reinterpret_cast<std::fstream*>(file);
    }

    Void LogSystem::Log(LogLevel level, const U8String& message)
    {
        if ( output == Output::Console )
        {
            constexpr UInt16 R = FOREGROUND_RED;
            constexpr UInt16 G = FOREGROUND_GREEN;
            constexpr UInt16 B = FOREGROUND_BLUE;

            constexpr UInt16 White      = R | G | B;
            constexpr UInt16 Yellow     = R | G;
            constexpr UInt16 Red        = R;
            constexpr UInt16 Magenta    = R | B;


            UInt16 textAttributes = 0;
            switch (level)
            {
            case LogLevel::Trace:
                textAttributes = White;
                break;
            case LogLevel::Warn:
                textAttributes = Yellow;
                break;
            case LogLevel::Error:
                textAttributes = Red;
                break;
            case LogLevel::Fatal:
                textAttributes = Magenta;
                break;
            }

            HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(outputHandle, textAttributes);

            U16String u16 = static_cast<U16String>(message);
            WriteConsoleW( outputHandle, u16.GetBuffer(), u16.GetCount(), nullptr, nullptr );
        }
        else if ( output == Output::File )
        {
            U8String tag;
            switch (level)
            {
            case LogLevel::Trace:
                tag = "Trace";
                break;
            case LogLevel::Warn:
                tag = "Warn";
                break;
            case LogLevel::Error:
                tag = "Error";
                break;
            case LogLevel::Fatal:
                tag = "Fatal";
                break;
            }

            TimeStamp time = GetCurrentTimeStamp();
            *reinterpret_cast<std::fstream*>(file) << Format(
                U8String( "[{Year}/{Month}/{Day} {Hour}:{Minute}][{Tag}]: {}\n" ),
                time.year, time.month, time.day, time.hour, time.minute,
                tag,
                message
            );
        }
    }

    Void LogSystem::FatalCallback()
    {
        ASSERT(false, "Fatal error");
    }
}