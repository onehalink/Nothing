#pragma once

#include "../Type.h"



namespace Engine
{
	/**
	* @remark
	* The index must be less than sizeof...(Types)
	*/
	template<SizeType Index, typename ...Types>
	struct SelectNthFromParameterPack;


	template<typename First, typename ...Types>
	struct SelectNthFromParameterPack<0, First, Types ...>
	{
		using Type = First;
	};


	template<SizeType Index, typename First, typename ...Types>
	struct SelectNthFromParameterPack<Index, First, Types ...>
	{
		using Type = typename SelectNthFromParameterPack<Index - 1, Types ...>::Type;
	};
}
