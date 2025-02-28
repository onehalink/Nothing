#pragma once

#include "../Type.h"



namespace Engine
{
	template<Bool InValue>
	struct BoolConstant
	{
		static constexpr Bool Value = InValue;
	};


	using FalseType	= BoolConstant<false>;
	using TrueType	= BoolConstant<true>;
}