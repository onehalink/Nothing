#pragma once

#include "../../TestFramework.h"



static Void Run()
{
	auto intValue0 = Parse::Value<Int32>("123");
	ASSERT(intValue0);
	ASSERT(intValue0.GetValue() == 123);
	auto intValue1 = Parse::Value<Int32>("-8401");
	ASSERT(intValue1);
	ASSERT(intValue1.GetValue() == -8401);

	auto floatValue0 = Parse::Value<Float32>("10.888");
	ASSERT(floatValue0);
	ASSERT(Approximate(floatValue0.GetValue(), 10.888));
	auto floatValue1 = Parse::Value<Float32>("-0.12345");
	ASSERT(floatValue1);
	ASSERT(Approximate(floatValue1.GetValue(), -0.12345));

	auto boolValue0 = Parse::Value<Bool>(" false");
	ASSERT(boolValue0);
	ASSERT(Approximate(boolValue0.GetValue(), false));
	auto boolValue1 = Parse::Value<Bool>(" True ");
	ASSERT(boolValue1);
	ASSERT(Approximate(boolValue1.GetValue(), true));

	//ASSERT(false);
}


EXEC_ONCE(Run);