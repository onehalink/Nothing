#pragma once

#include "../Type.h"



namespace Engine
{
	// Similar as operator?: but used to select a type
	template<Bool Predicate, typename TrueResult, typename FalseResult>
	struct Conditional;


	template<typename TrueResult, typename FalseResult>
	struct Conditional<false, TrueResult, FalseResult>
	{
		using Type = FalseResult;
	};


	template<typename TrueResult, typename FalseResult>
	struct Conditional<true, TrueResult, FalseResult>
	{
		using Type = TrueResult;
	};
}