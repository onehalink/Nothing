#pragma once

#include "BoolConstant.h"



namespace Engine
{
	// Test if two or more types are same
	template<typename ...Types>
	struct TypesAreSame;


	template<typename T>
	struct TypesAreSame<T, T> : TrueType
	{

	};


	template<typename T, typename U>
	struct TypesAreSame<T, U> : FalseType
	{

	};
	

	template<typename First, typename Second, typename ...Types>
	struct TypesAreSame<First, Second, Types ...> : BoolConstant<TypesAreSame<First, Second>::Value && TypesAreSame<Second, Types ...>::Value>
	{

	};
}