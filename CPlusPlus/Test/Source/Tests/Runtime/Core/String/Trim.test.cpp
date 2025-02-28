#pragma once

#include "../../../TestFramework.h"



static Void Run()
{
	U8StringView input = " Trim Test  ";
	U8StringView trimStartResult = "Trim Test  ";
	U8StringView trimEndResult = " Trim Test";
	U8StringView trimBothResult = "Trim Test";

	auto trim0 = Trim(input, true, false);
	auto trim1 = Trim(input, false, true);
	auto trim2 = Trim(input, true, true);
	ASSERT(trim0 == trimStartResult);
	ASSERT(trim1 == trimEndResult);
	ASSERT(trim2 == trimBothResult);

	//ASSERT(false);
}


EXEC_ONCE(Run);