#pragma once

#include "../Type.h"

#include "IntegralConstant.h"



namespace Engine
{
	template<Bool InValue>
	using BoolConstant = IntegralConstant<Bool, InValue>;


	using FalseType	= BoolConstant<false>;
	using TrueType	= BoolConstant<true>;
}