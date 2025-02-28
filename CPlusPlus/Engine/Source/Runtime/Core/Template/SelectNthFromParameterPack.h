#pragma once

#include "../Base.h"



namespace Engine
{
	template<SizeType Index, typename ...Ts>
	struct SelectNthFromParameterPack;


	template<typename First, typename ...Ts>
	struct SelectNthFromParameterPack<0, First, Ts ...>
	{
		using Type = First;
	};


	template<SizeType Index, typename First, typename ...Ts>
	struct SelectNthFromParameterPack<Index, First, Ts ...>
	{
		using Type = typename SelectNthFromParameterPack<Index - 1, Ts ...>::Type;
	};
}
