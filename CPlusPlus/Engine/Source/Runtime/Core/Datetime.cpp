#include "Datetime.h"

#if defined(PLATFORM_WINDOWS)
#include "../Platform/Windows/Windows.h"
#endif



namespace Engine
{
	Datetime Datetime::GetCoordinatedUniversalTime(Int32 offsetInHours)
	{
	#if defined(PLATFORM_WINDOWS)
		SYSTEMTIME systemTime;
		GetSystemTime( &systemTime );

		Datetime ret;
		ret.year		= systemTime.wYear;
		ret.month		= systemTime.wMonth;
		ret.day			= systemTime.wDay;
		ret.hour		= systemTime.wHour;
		ret.minute		= systemTime.wMinute;
		ret.second		= systemTime.wSecond;
		ret.millisecond	= systemTime.wMilliseconds;

		Int32 currentHours = systemTime.wHour + offsetInHours;

		if ( currentHours >= HoursPerDay )
		{
			ret.day++;

			ret.hour = currentHours % HoursPerDay;
		}
		else if ( currentHours < 0 )
		{
			ret.day--;

			ret.hour = static_cast<Int32>(HoursPerDay) + currentHours;
		}
		else
		{
			ret.hour = currentHours;

			return ret;
		}

		if ( ret.day == 0 )
		{
			ret.month--;

			if ( ret.month == 0 )
				ret.day = 31;
			else
				ret.day = GetDaysOfMonth( ret.year, ret.month );
		}
		else
		{
			Int32 daysPerMonth = GetDaysOfMonth( ret.year, ret.month );

			if ( ret.day > daysPerMonth )
			{
				ret.month++;

				ret.day = 1;
			}
		}

		if ( ret.month == 0 )
		{
			ret.year--;

			ret.month = 12;
		}
		else if ( ret.month > 12 )
		{
			ret.year++;

			ret.month = 1;
		}

		return ret;
	#else
	#error No implementation
	#endif
	}

	Datetime Datetime::GetChinaStandardTime()
	{
		return GetCoordinatedUniversalTime(8);
	}

	Bool Datetime::IsEvenMonth(SizeType month)
	{
		return month <= 7 ?
			month % 2 == 0 :	// 2, 4, 6
			month % 2 == 1;		// 9, 11
	}

	Bool Datetime::IsLeapYear(SizeType year)
	{
		return year % 100 == 0 ? // century year
			year % 400	== 0 :
			year % 4	== 0;
	}

	SizeType Datetime::GetDaysOfMonth(SizeType year, SizeType month)
	{
		return !IsEvenMonth(month) ?
			31 :
			month == 2 ? ( !IsLeapYear(year) ? 28 : 29 ) : 30;
	}

	SizeType Datetime::GetDaysOfYear(SizeType year)
	{
		return IsLeapYear(year) ? DaysPerLeapYear : DaysPerNonleapYear;
	}
}