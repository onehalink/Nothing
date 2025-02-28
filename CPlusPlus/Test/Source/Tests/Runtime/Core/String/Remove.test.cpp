#pragma once

#include "../../../TestFramework.h"



static Void Run()
{
	U8StringView input = "0123456789";

	ASSERT((U8StringView)Remove(input, 3) == "012"U8SV);
	ASSERT((U8StringView)Remove(input, 2, 5) == "01789"U8SV);

	//ASSERT(false);
}


EXEC_ONCE(Run);