#pragma once

#include "ContainedFromParametePack.h"



namespace Engine
{
	template<typename T>
	struct IsChar : BoolConstant<ContainedFromParameterPack<T, Char8, Char16, Char32>::Value>
	{

	};
}
