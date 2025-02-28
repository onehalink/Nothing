#pragma once

#include "IsFloatPoint.h"
#include "IsIntegral.h"



namespace Engine
{
	template<typename T>
	struct IsArithmetic : BoolConstant<IsIntegral<T>::Value || IsFloatPoint<T>::Value>
	{

	};
}