#pragma once

#include "../../../TestFramework.h"



static Void Run()
{
	U8StringView input = "red\rgreen\nblue\r\n";
	U8StringView result[] = { "red", "green", "blue", "" };

	SizeType index = 0;
	ParseLines<Char8>(input,
		[&](U8StringView view)
		{
			ASSERT(view == result[index++]);
		}
	);

	//ASSERT(false);
}


EXEC_ONCE(Run);