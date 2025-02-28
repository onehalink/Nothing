#pragma once

#include "../../../TestFramework.h"



static Void Run()
{
	U8StringView input = "012XYZABC, 0101";
	U8StringView oldValue = "01";
	U8StringView newValue = "|##|";
	U8StringView result = "|##|2XYZABC, |##||##|";

	auto value = Replace(input, oldValue, newValue);
	ASSERT((U8StringView)value == result);

	//ASSERT(false);
}


EXEC_ONCE(Run);