#pragma once

#include "BoolConstant.h"



namespace Engine
{
	template<typename T>
	struct IsTriviallyDestructible : BoolConstant<__is_trivially_destructible(T)>
	{

	};
}