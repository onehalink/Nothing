#pragma once

#include "../../TestFramework.h"



static Void Run()
{
	Tuple<Int32, U8String, Bool> tuple = {1, "Text", false};

	ASSERT(tuple.Get<0>() == 1);
	ASSERT((U8StringView)tuple.Get<1>() == "Text"U8SV);
	ASSERT(tuple.Get<2>() == false);

	auto newTuple = tuple.Swizzle<0, 0, 1, 1, 2, 2>();
	ASSERT(newTuple.Get<1>() == 1);
	ASSERT((U8StringView)newTuple.Get<3>() == "Text"U8SV);
	ASSERT(newTuple.Get<5>() == false);

	//ASSERT(false);
}


EXEC_ONCE(Run);