#pragma once

#include "TypesAreSame.h"



namespace Engine
{
	// Test if input types(Ts) have a type that is E(expected)
	template<typename E, typename ...Ts>
	struct ContainedFromParameterPack;


	template<typename E, typename First>
	struct ContainedFromParameterPack<E, First> : BoolConstant<TypesAreSame<E, First>::Value>
	{

	};


	template<typename E, typename First, typename ...Ts>
	struct ContainedFromParameterPack<E, First, Ts ...> : BoolConstant<ContainedFromParameterPack<E, First>::Value || ContainedFromParameterPack<E, Ts ...>::Value>
	{

	};
}