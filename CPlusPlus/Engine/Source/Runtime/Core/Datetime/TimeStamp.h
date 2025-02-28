#pragma once

#include "../Base.h"



namespace Engine
{
	struct TimeStamp
	{
		UInt16 year;
		UInt16 month;
		UInt16 day;
		UInt16 hour;
		UInt16 minute;
		UInt16 second;
		UInt16 millisecond;
	};


	// UTC+8
	ENGINE_API TimeStamp GetCurrentTimeStamp();
}