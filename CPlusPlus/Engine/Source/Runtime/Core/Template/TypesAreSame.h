#pragma once

#include "BoolConstant.h"



namespace Engine
{
	// Test if two or more types are same
	template<typename ...Types>
	struct TypesAreSame;

	template<typename First>
	struct TypesAreSame<First, First> : TrueType
	{
	
	};

	template<typename First, typename Second>
	struct TypesAreSame<First, Second> : FalseType
	{

	};

	template<typename First, typename Second, typename ...Types>
	struct TypesAreSame<First, Second, Types ...> : BoolConstant<TypesAreSame<First, Second>::Value && TypesAreSame<Second, Types ...>::Value>
	{

	};
}