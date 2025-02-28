#pragma once

#include "APISet.h"



enum class Channel
{
	R = 1 << 0,
	G = 1 << 1,
	B = 1 << 2,
};
ENABLE_BITWISE_OPERATORS(Channel);


inline Void Test_Core_Template_EnumClass()
{
	constexpr auto result0 = Channel::R | Channel::G;
	constexpr auto result1 = result0 & Channel::R;
	constexpr auto result2 = result0 ^ Channel::B;
	constexpr auto result3 = ~result2;
}