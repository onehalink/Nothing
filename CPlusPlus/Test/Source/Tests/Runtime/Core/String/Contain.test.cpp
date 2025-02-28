#pragma once

#include "../../../TestFramework.h"



static Void Run()
{
	U8StringView input = "0123456789ABCDEF";

	SizeType index;
	Contain<Char8>(input, "ABC", &index);
	ASSERT(index == 10);
	auto test = Contain<Char8>(input, "aBC", &index);
	ASSERT(!test);

	//ASSERT(false);
}


EXEC_ONCE(Run);