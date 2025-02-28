#pragma once

#include "IntegralConstant.h"



namespace Engine
{
	template<typename From, typename To>
	struct IsConvertible : BoolConstant<__is_convertible_to(From, To)>
	{

	};
}