#pragma once

#include "BoolConstant.h"



namespace Engine
{
	template<typename T, typename ...Parameters>
	struct IsConstructible : BoolConstant<__is_constructible(T, Parameters ...)>
	{

	};
}