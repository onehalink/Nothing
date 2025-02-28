#pragma once

#include "../../../TestFramework.h"



static Void Run()
{
	ASSERT(StartWith("StartWith"U8SV, "Start"U8SV));
	ASSERT(!StartWith("StartWith"U8SV, "StarT"U8SV));

	ASSERT(EndWith("EndWith"U8SV, "With"U8SV));
	ASSERT(!EndWith("EndWith"U8SV, "with"U8SV));

	//ASSERT(false);
}


EXEC_ONCE(Run);