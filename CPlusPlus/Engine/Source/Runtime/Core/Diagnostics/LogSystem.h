#pragma once

#include "../Datetime/TimeStamp.h"

#include "../String/Format.h"



namespace Engine
{
	#if defined(DEBUG)
		#define TRACE(format, ...)	LogSystem::ConsoleLogger.Trace(format, __VA_ARGS__)
		#define WARN(format, ...)	LogSystem::ConsoleLogger.Warn(format, __VA_ARGS__)
		#define ERROR(format, ...)	LogSystem::ConsoleLogger.Error(format, __VA_ARGS__)
		#define FATAL(format, ...)	LogSystem::ConsoleLogger.Fatal(format, __VA_ARGS__)
	#else
		#define TRACE(format, ...)
		#define WARN(format, ...)
		#define ERROR(format, ...)
		#define FATAL(format, ...)
	#endif


	class ENGINE_API LogSystem
	{
	public:
		enum class Output
		{
			Console,
			File,
		};


		enum class LogLevel
		{
			Trace,
			Warn,
			Error,
			Fatal,
		};


		static LogSystem ConsoleLogger;
		static LogSystem FileLogger;

		
		LogSystem(Output output, const U8String& outputFileName = "");
		~LogSystem();


		Void Log(LogLevel level, const U8String& message);
		Void FatalCallback();


		template<typename ...Parameters> Void Log(LogLevel level, const U8String& format, Parameters&&... parameters);
		template<typename ...Parameters> Void Trace(const U8String& format, Parameters&&... parameters);
		template<typename ...Parameters> Void Warn(const U8String& format, Parameters&&... parameters);
		template<typename ...Parameters> Void Error(const U8String& format, Parameters&&... parameters);
		template<typename ...Parameters> Void Fatal(const U8String& format, Parameters&&... parameters);
	private:
		Output output;

		Void*		file;
		U8String	outputFileName;
	};


#pragma region Details

	template<typename ...Parameters>
	Void LogSystem::Log(LogLevel level, const U8String& format, Parameters&&... parameters)
	{
		Log( level, Format( format, Forward<Parameters>(parameters)... ) );
	}

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

#pragma endregion
}