#pragma once

#include "BoolConstant.h"



namespace Engine
{
	template<typename ClassType, typename ...Parameters>
	struct IsConstructible : BoolConstant<__is_constructible(ClassType, Parameters ...)>
	{

	};
}