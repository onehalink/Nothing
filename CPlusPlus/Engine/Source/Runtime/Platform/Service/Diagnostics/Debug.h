#pragma once

#include "../../../Core.h"



namespace Engine
{
	class Debug
	{
	public:
		template<typename ...Parameters> static Void Trace(const U8String& format, Parameters&&... parameters);
		template<typename ...Parameters> static Void Warn(const U8String& format, Parameters&&... parameters);
		template<typename ...Parameters> static Void Error(const U8String& format, Parameters&&... parameters);
	private:
		enum class Level
		{
			Trace,
			Warn,
			Error,
		};


		template<typename ...Parameters> static Void Log(Level level, const U8String& format, Parameters&&... parameters);
		static ENGINE_API Void Log(Level level, const U8String& message);
	};


#pragma region Details

	template<typename ...Parameters>
	Void Debug::Trace(const U8String& format, Parameters&&... parameters)
	{
		Log( Level::Trace, format, Forward<Parameters>(parameters)... );
	}

	template<typename ...Parameters>
	Void Debug::Warn(const U8String& format, Parameters&&... parameters)
	{
		Log( Level::Warn, format, Forward<Parameters>(parameters)... );
	}

	template<typename ...Parameters>
	Void Debug::Error(const U8String& format, Parameters&&... parameters)
	{
		Log( Level::Error, format, Forward<Parameters>(parameters)... );
	}

	template<typename ...Parameters>
	Void Debug::Log(Level level, const U8String& format, Parameters&&... parameters)
	{
		Log( level, Format( format, Forward<Parameters>(parameters)... ) );
	}

#pragma endregion
}