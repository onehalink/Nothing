#pragma once

#include "SameAsAny.h"



namespace Engine
{
	template<typename T>
	struct IsChar : BoolConstant<SameAsAny<T, Char8, Char16, Char32>::Value>
	{

	};
}
