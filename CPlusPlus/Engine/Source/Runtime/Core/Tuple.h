#pragma once

#include "Template/Forward.h"
#include "Template/SelectNthFromParameterPack.h"



namespace Engine
{
	template<typename ...Types>
	struct Tuple;


	template<>
	struct Tuple<>
	{

	};


	template<typename First, typename ...Types>
	struct Tuple<First, Types ...> : Tuple<Types ...>
	{
		First value;


		Tuple(First&& value, Types&&... parameters) : value( Forward<First>(value) ), Tuple<Types ...>( Forward<Types>(parameters)... ) {}
	};


	template<SizeType Index, typename First, typename ...Types>
	typename SelectNthFromParameterPack<Index, First, Types ...>::Type& Visit(Tuple<First, Types ...>& tuple)
	{
		if constexpr ( Index == 0 )
			return tuple.value;
		else
			return Visit<Index - 1, Types ...>( (Tuple<Types ...>&)tuple );
	}
}