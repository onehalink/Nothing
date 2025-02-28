#pragma once

#include "IsArithmetic.h"
#include "IsChar.h"
#include "TypesAreSame.h"



namespace Engine
{
	template<typename T>
	struct IsFundamental : BoolConstant<IsArithmetic<T>::Value || IsChar<T>::Value || TypesAreSame<T, Void>::Value>
	{

	};
}