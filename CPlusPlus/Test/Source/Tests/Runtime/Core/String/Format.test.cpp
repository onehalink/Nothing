#pragma once

#include "../../../TestFramework.h"



static Void Run()
{
	U8String value0 = Format<Char8>("Hello, {}", "Format");
	ASSERT((U8StringView)value0 == "Hello, Format"U8SV);

	U8String value1 = Format<Char8>("{} ^ {} = {}", 2, 10, 1024);
	ASSERT((U8StringView)value1 == "2 ^ 10 = 1024"U8SV);

	U8String value2 = Format<Char8>("float point value: {}", -0.555);
	ASSERT((U8StringView)value2 == "float point value: -0.555"U8SV);

	U8String value3 = Format<Char8>("condtion: {}", false);
	ASSERT((U8StringView)value3 == "condtion: false"U8SV);

	//ASSERT(false);
}


EXEC_ONCE(Run);