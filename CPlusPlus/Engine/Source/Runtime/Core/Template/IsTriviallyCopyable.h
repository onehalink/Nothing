#pragma once

#include "BoolConstant.h"



namespace Engine
{
	template<typename T>
	struct IsTriviallyCopyable : BoolConstant<__is_trivially_copyable(T)>
	{

	};
}