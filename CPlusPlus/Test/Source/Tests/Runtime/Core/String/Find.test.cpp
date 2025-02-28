#pragma once

#include "../../../TestFramework.h"



static Void Run()
{
	U8StringView input = "0123456789ABCDEF";

	auto value0 = FindFirst<Char8>(input, "345");
	auto value1 = FindFirst<Char8>(input, "346");
	ASSERT(value0 == 3);
	ASSERT(value1 == -1);
	auto value2 = FindLast<Char8>(input, "ABC");
	auto value3 = FindLast<Char8>(input, "ABc");
	ASSERT(value2 == 10);
	ASSERT(value3 == -1);

	U8StringView search0[] = { "230", "234", "9aB", "89A" };
	ReadOnlySpan<U8StringView> searchViews = { search0, 4 };

	auto value4 = FindFirstOfAny(input, searchViews);
	auto value5 = FindLastOfAny(input, searchViews);
	ASSERT(value4 == 2);
	ASSERT(value5 == 8);

	auto value6 = FindFirstChar(input, 'A');
	auto value7 = FindLastChar(input, '1');
	ASSERT(value6 == 10);
	ASSERT(value7 == 1);

	ReadOnlySpan<Char8> searchChar8s = { "0F", 2 };
	auto value8 = FindFirstOfAnyChar(input, searchChar8s);
	auto value9 = FindLastOfAnyChar(input, searchChar8s);
	ASSERT(value8 == 0);
	ASSERT(value9 == 15);

	//ASSERT(false);
}


EXEC_ONCE(Run);