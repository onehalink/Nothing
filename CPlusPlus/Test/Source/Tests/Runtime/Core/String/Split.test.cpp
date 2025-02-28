#pragma once

#include "../../../TestFramework.h"



static Void Run()
{
	U8StringView input = "0 1,2,3|4";
	ReadOnlySpan<Char8> delimiters = { " ,|", 3 };
	U8StringView result = "01234";

	auto v0 = result[0];

	SizeType index = 0;
	Split<Char8>(input, delimiters,
		[&](U8StringView view)
		{
			ASSERT(view[0] == result[index++]);
		}
	);

	//ASSERT(false);
}


EXEC_ONCE(Run);