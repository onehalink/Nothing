#pragma once

#include "../Base.h"



namespace Engine
{
	template<typename T, T InValue>
	struct IntegralConstant
	{
		static constexpr T Value = InValue;
	};
}