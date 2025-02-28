#pragma once

#include "BoolConstant.h"
#include "TypesAreSame.h"



namespace Engine
{
	// Test if LookupType is included in Types
	template<typename LookupType, typename ...Types>
	struct SameAsAny;


	template<typename LookupType, typename First>
	struct SameAsAny<LookupType, First> : BoolConstant<TypesAreSame<LookupType, First>::Value>
	{

	};


	template<typename LookupType, typename First, typename ...Types>
	struct SameAsAny<LookupType, First, Types ...> : BoolConstant<SameAsAny<LookupType, First>::Value || SameAsAny<LookupType, Types ...>::Value>
	{

	};
}