#pragma once

#include "BoolConstant.h"



namespace Engine
{
	template<typename FromType, typename ToType>
	struct IsConvertible : BoolConstant<__is_convertible_to(FromType, ToType)>
	{

	};
}