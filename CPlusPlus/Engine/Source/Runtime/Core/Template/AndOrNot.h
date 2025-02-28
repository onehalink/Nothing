#pragma once

#include "BoolConstant.h"



namespace Engine
{
	// Does a boolean AND of the ::Value static members of each type, but short-circuits if any Type::Value == false
	template<typename ...Types>					struct And;
	template<>									struct And<>					: TrueType {};
	template<typename First, typename ...Types>	struct And<First, Types ...>	: BoolConstant<First::Value && And<Types ...>::Value> {};


	// Does a boolean OR of the ::Value static members of each type, but short-circuits if any Type::Value == true
	template<typename ...Types>					struct Or;
	template<>									struct Or<>						: FalseType {};
	template<typename First, typename ...Types>	struct Or<First, Types ...>		: BoolConstant<First::Value || Or<Types ...>::Value> {};


	// Does a boolean NOT of the ::Value static members of the type
	template<typename Type>						struct Not						: BoolConstant<!Type::Value> {};
}