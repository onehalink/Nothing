#pragma once

#include "TypesAreSame.h"



namespace Engine
{
	// Test if typename Test is included in Types
	template<typename Test, typename ...Types>
	struct SameAsAny;


	template<typename Test, typename First>
	struct SameAsAny<Test, First> : BoolConstant<TypesAreSame<Test, First>::Value>
	{

	};


	template<typename Test, typename First, typename ...Types>
	struct SameAsAny<Test, First, Types ...> : BoolConstant<SameAsAny<Test, First>::Value || SameAsAny<Test, Types ...>::Value>
	{

	};
}
