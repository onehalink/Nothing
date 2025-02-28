#pragma once

#include "IsFloatPoint.h"
#include "IsInteger.h"



namespace Engine
{
	template<typename T>
	struct IsArithmetic : BoolConstant<IsInteger<T>::Value || IsFloatPoint<T>::Value>
	{

	};
}