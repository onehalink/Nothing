#pragma once

#include "SameAsAny.h"



namespace Engine
{
	template<typename T>
	struct IsFloatPoint : BoolConstant<SameAsAny<T, Float32, Float64>::Value>
	{

	};
}