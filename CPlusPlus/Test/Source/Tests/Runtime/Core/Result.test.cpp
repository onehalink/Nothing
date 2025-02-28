#pragma once

#include "../../TestFramework.h"



static Void Run()
{
	Result<Int32> invalid;
	//ASSERT(false);
	invalid.SetValue(1);
	ASSERT(invalid.GetValue() == 1);
	invalid.SetError("error text");
	ASSERT(invalid.GetError() == "error text"U8SV);

	Result<RealType> hasError = { InPlaceIndex<0>(), "An error occurred"};
	Result<RealType> hasValue = { InPlaceIndex<1>(), 3.1415 };
	ASSERT(hasError.GetError() == "An error occurred"U8SV);
	ASSERT(Approximate(hasValue.GetValue(), 3.1415));

	//ASSERT(false);
}


EXEC_ONCE(Run);