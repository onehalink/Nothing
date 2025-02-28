#pragma once

#include "Type.h"



namespace Engine
{
	template<SizeType Size, typename T>
	constexpr SizeType CountArray(const T(&array)[Size])
	{
		return Size;
	}
}