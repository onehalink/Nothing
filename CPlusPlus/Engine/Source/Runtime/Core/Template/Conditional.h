#pragma once

#include "SelectNthFromParameterPack.h"



namespace Engine
{
	// Similar as operator?: but used to select a type
	template<Bool Predicate, typename True, typename False>
	struct Conditional
	{
		using Type = typename SelectNthFromParameterPack<Predicate ? 0 : 1, True, False>::Type;
	};
}