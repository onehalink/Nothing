#include "LogSystem.h"

#if defined(PLATFORM_WINDOWS)
#include "../../Platform/Windows/Windows.h"
#endif

#include <fstream>



namespace Engine
{
	LogSystem LogSystem::DefaultLogger = { LogSystem::OutputDevice::Console };


	LogSystem::LogSystem(OutputDevice outputDivice, const U8String& outputDeviceName)
	{
		this->outputDevice = outputDivice;

		if ( outputDevice == OutputDevice::File )
			handle = new std::fstream( outputDeviceName, std::ios::out | std::ios::app );
	}

	LogSystem::~LogSystem()
	{
		if ( outputDevice == OutputDevice::File )
			delete reinterpret_cast<std::fstream*>(handle);
	}

	Void LogSystem::Log(LogLevel level, const U8String& message)
	{
		if ( outputDevice == OutputDevice::Console )
		{
		#if defined(PLATFORM_WINDOWS)
			constexpr UInt16 R = FOREGROUND_RED;
			constexpr UInt16 G = FOREGROUND_GREEN;
			constexpr UInt16 B = FOREGROUND_BLUE;
			constexpr UInt16 I = FOREGROUND_INTENSITY;

			constexpr UInt16 White		= R | G | B;
			constexpr UInt16 Yellow		= R | G;
			constexpr UInt16 Red		= R;
			constexpr UInt16 Meganta	= R | B;


			UInt16 attributes = 0;
			switch (level)
			{
			case LogLevel::Trace:
				attributes = White;
				break;
			case LogLevel::Warn:
				attributes = Yellow;
				break;
			case LogLevel::Error:
				attributes = Red;
				break;
			case LogLevel::Fatal:
				attributes = Meganta | I;
				break;
			}

			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(handle, attributes);

			U16String u16 = static_cast<U16String>(message);
			WriteConsoleW(handle, u16, u16.GetCount(), nullptr, nullptr);
		#else
		#error No implementation
		#endif
		}
		else
		{
			*reinterpret_cast<std::fstream*>(handle) << message;
		}
	}

	Void LogSystem::FatalCallback()
	{
		ASSERT(false, "Fatal error");
	}
}
