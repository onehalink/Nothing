#pragma once

#include "TypesAreSame.h"



namespace Engine
{
	// Test if E is included in Ts
	template<typename E, typename ...Ts>
	struct SameAsAny;


	template<typename E, typename First>
	struct SameAsAny<E, First> : BoolConstant<TypesAreSame<E, First>::Value>
	{

	};


	template<typename E, typename First, typename ...Ts>
	struct SameAsAny<E, First, Ts ...> : BoolConstant<SameAsAny<E, First>::Value || SameAsAny<E, Ts ...>::Value>
	{

	};
}
