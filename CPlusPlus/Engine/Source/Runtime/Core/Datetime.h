#pragma once

#include "Base.h"



namespace Engine
{
	/*
	enum class DaysOfWeek
	{
		Monday,
		Tuesday,
		Wednesday,
		Thursday,
		Friday,
		Saturday,
		Sunday,
	};


	enum class MonthsOfYear
	{
		January = 1,
		February,
		March,
		April,
		May,
		June,
		July,
		August,
		September,
		October,
		November,
		December,
	};
	*/


	struct ENGINE_API Datetime
	{
		static constexpr SizeType NanosecondsPerMicrosecond		= 1000;
		static constexpr SizeType MicrosecondsPerMillisecond	= 1000;
		static constexpr SizeType MillisecondsPerSecond			= 1000;
		static constexpr SizeType SecondsPerMinute				= 60;
		static constexpr SizeType MinutesPerHour				= 60;
		static constexpr SizeType HoursPerDay					= 24;
		static constexpr SizeType DaysPerWeek					= 7;
		static constexpr SizeType DaysPerLeapYear				= 366;
		static constexpr SizeType DaysPerNonleapYear			= DaysPerLeapYear - 1;

		static constexpr SizeType DaysPerYear					= DaysPerNonleapYear;
		static constexpr SizeType HoursPerYear					= DaysPerYear			* HoursPerDay;
		static constexpr SizeType MinutesPerYear				= HoursPerYear			* MinutesPerHour;
		static constexpr SizeType SecondsPerYear				= MinutesPerYear		* SecondsPerMinute;
		static constexpr SizeType MillisecondsPerYear			= SecondsPerYear		* MillisecondsPerSecond;
		static constexpr SizeType MicrosecondsPerYear			= MillisecondsPerYear	* MicrosecondsPerMillisecond;
		static constexpr SizeType NanosecondsPerYear			= MicrosecondsPerYear	* NanosecondsPerMicrosecond;

		static constexpr SizeType MinutePerDay					= HoursPerDay			* MinutesPerHour;
		static constexpr SizeType SecondsPerDay					= MinutePerDay			* SecondsPerMinute;
		static constexpr SizeType MillisecondsPerDay			= SecondsPerDay			* MillisecondsPerSecond;
		static constexpr SizeType MicrosecondsPerDay			= MillisecondsPerDay	* MicrosecondsPerMillisecond;
		static constexpr SizeType NanosecondsPerDay				= MicrosecondsPerDay	* NanosecondsPerMicrosecond;


		UInt16 year;
		UInt16 month;
		UInt16 day;
		UInt16 hour;
		UInt16 minute;
		UInt16 second;
		UInt16 millisecond;


		// Retrieves the current system date and time in Coordinated Universal Time (UTC) format.
		static Datetime GetCoordinatedUniversalTime(Int32 offsetInHours = 0);
		// UTC+8
		static Datetime GetChinaStandardTime();

		/**
		* @remark
		* Even Month:
		* Days per month is 30, and February excluded.
		* Days of February should is 28(nonleap year) or 29(leap year)
		* 
		* Even Month:
		* Days per month is 31
		*/
		static Bool IsEvenMonth(SizeType month);
		static Bool IsLeapYear(SizeType year);
		static SizeType GetDaysOfMonth(SizeType year, SizeType month);
		static SizeType GetDaysOfYear(SizeType year);
	};
}