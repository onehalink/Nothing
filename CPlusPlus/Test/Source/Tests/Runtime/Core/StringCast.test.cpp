#pragma once

#include "../../TestFramework.h"



static Void Run()
{
	auto value0 = StringCast<U8String>(100);
	auto value1 = StringCast<U8String>(-50);
	ASSERT((U8StringView)value0 == "100"U8SV);
	ASSERT((U8StringView)value1 == "-50"U8SV);

	auto value2 = StringCast<U8String>(123.54321);
	auto value3 = StringCast<U8String>(0.1456);
	auto value4 = StringCast<U8String>(-0.78231);
	auto value5 = StringCast<U8String>(-842.0101);
	//ASSERT((U8StringView)value2 == "123.54321"U8SV);
	//ASSERT((U8StringView)value3 == "0.1456"U8SV);
	//ASSERT((U8StringView)value4 == "-0.78231"U8SV);
	//ASSERT((U8StringView)value5 == "-842.0101"U8SV);

	auto boolValue0 = StringCast<U8String>(false);
	auto boolValue1 = StringCast<U8String>(true);
	ASSERT((U8StringView)boolValue0 == "false"U8SV);
	ASSERT((U8StringView)boolValue1 == "true"U8SV);

	//ASSERT(false);
}


EXEC_ONCE(Run);