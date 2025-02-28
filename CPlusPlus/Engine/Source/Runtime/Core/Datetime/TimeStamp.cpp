#include "TimeStamp.h"

#if defined(PLATFORM_WINDOWS)
#include "../../Platform/Windows/Windows.h"
#endif



namespace Engine
{
	TimeStamp GetCurrentTimeStamp()
	{
	#if defined(PLATFORM_WINDOWS)
		SYSTEMTIME systemTime;
		GetSystemTime( &systemTime );

		TimeStamp ret;
		ret.year		= systemTime.wYear;
		ret.month		= systemTime.wMonth;
		ret.day			= systemTime.wDay;
		ret.hour		= systemTime.wHour + 8;
		ret.minute		= systemTime.wMinute;
		ret.second		= systemTime.wSecond;
		ret.millisecond	= systemTime.wMilliseconds;

		if ( ret.hour >= 24 )
		{
			ret.day++;

			ret.hour %= 24;
		}

		return ret;
	#else
	#error No implementation
	#endif
	}
}