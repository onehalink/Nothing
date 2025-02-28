#pragma once

#include "../NonCopyable.h"

#include "../String/Format.h"



namespace Engine
{
	class ENGINE_API LogSystem : NonCopyable
	{
	public:
		enum class LogLevel
		{
			Trace,
			Warn,
			Error,
			Fatal,
		};


		enum class OutputDevice
		{
			Console,
			File,
		};


		static LogSystem DefaultLogger;


		LogSystem(OutputDevice outputDivice, const U8String& outputDeviceName = "");
		~LogSystem();


		template<typename ...Parameters> Void Trace(const U8String& format, Parameters&&... parameters);
		template<typename ...Parameters> Void Warn(const U8String& format, Parameters&&... parameters);
		template<typename ...Parameters> Void Error(const U8String& format, Parameters&&... parameters);
		template<typename ...Parameters> Void Fatal(const U8String& format, Parameters&&... parameters);
	private:
		template<typename ...Parameters> Void Log(LogLevel level, const U8String& format, Parameters&&... parameters);


		Void Log(LogLevel level, const U8String& message);
		Void FatalCallback();
	private:
		OutputDevice outputDevice;

		Void* handle; // it is a file handle if used
	};


#pragma region Details

	template<typename ...Parameters>
	Void LogSystem::Trace(const U8String& format, Parameters&&... parameters)
	{
		Log( LogLevel::Trace, format, Forward<Parameters>(parameters)... );
	}

	template<typename ...Parameters>
	Void LogSystem::Warn(const U8String& format, Parameters&&... parameters)
	{
		Log( LogLevel::Warn, format, Forward<Parameters>(parameters)... );
	}

	template<typename ...Parameters>
	Void LogSystem::Error(const U8String& format, Parameters&&... parameters)
	{
		Log( LogLevel::Error, format, Forward<Parameters>(parameters)... );
	}

	template<typename ...Parameters>
	Void LogSystem::Fatal(const U8String& format, Parameters&&... parameters)
	{
		Log( LogLevel::Fatal, format, Forward<Parameters>(parameters)... );

		FatalCallback();
	}

	template<typename ...Parameters>
	Void LogSystem::Log(LogLevel level, const U8String& format, Parameters&&... parameters)
	{
		Log( level, Format( format, Forward<Parameters>(parameters)... ) );
	}

#pragma endregion
}
