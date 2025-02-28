#pragma once

#include "../../../Core.h"



namespace Engine
{
	class Debug
	{
	public:
		template<typename ...Parameters> static Void Trace(U8StringView format, Parameters&&... parameters);
		template<typename ...Parameters> static Void Warn(U8StringView format, Parameters&&... parameters);
		template<typename ...Parameters> static Void Error(U8StringView format, Parameters&&... parameters);
	private:
		enum class Level
		{
			Trace,
			Warn,
			Error,
		};


		template<typename ...Parameters> static Void Log(Level level, U8StringView format, Parameters&&... parameters);
		static ENGINE_API Void Log(Level level, U8StringView message);
	};


#pragma region Details

	template<typename ...Parameters>
	Void Debug::Trace(U8StringView format, Parameters&&... parameters)
	{
		Log( Level::Trace, format, Forward<Parameters>(parameters)... );
	}

	template<typename ...Parameters>
	Void Debug::Warn(U8StringView format, Parameters&&... parameters)
	{
		Log( Level::Warn, format, Forward<Parameters>(parameters)... );
	}

	template<typename ...Parameters>
	Void Debug::Error(U8StringView format, Parameters&&... parameters)
	{
		Log( Level::Error, format, Forward<Parameters>(parameters)... );
	}

	template<typename ...Parameters>
	Void Debug::Log(Level level, U8StringView format, Parameters&&... parameters)
	{
		auto message = Format( format, Forward<Parameters>(parameters)... );

		Log(level, message);
	}

#pragma endregion
}