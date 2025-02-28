#pragma once

#include "../Base.h"



namespace Engine
{
	// Similar as operator?: but it uses to select type
	template<Bool Predicate, typename TrueType, typename FalseType>
	struct Conditional;


	template<typename TrueType, typename FalseType>
	struct Conditional<false, TrueType, FalseType>
	{
		using Type = FalseType;
	};


	template<typename TrueType, typename FalseType>
	struct Conditional<true, TrueType, FalseType>
	{
		using Type = TrueType;
	};
}