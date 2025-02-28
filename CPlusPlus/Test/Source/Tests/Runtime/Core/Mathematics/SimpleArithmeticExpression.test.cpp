#pragma once

#include "../../../TestFramework.h"



static Void Run()
{
	auto value0 = SimpleArithmeticExpression::Evaluate<Int32>("1 + 1");
	auto value1 = SimpleArithmeticExpression::Evaluate<Int32>("1 - 2");
	auto value2 = SimpleArithmeticExpression::Evaluate<Int32>("3 * 2");
	auto value3 = SimpleArithmeticExpression::Evaluate<Int32>("4 / 2");
	auto value4 = SimpleArithmeticExpression::Evaluate<Int32>("2^10");
	ASSERT(value0.GetValue() == 2);
	ASSERT(value1.GetValue() == -1);
	ASSERT(value2.GetValue() == 6);
	ASSERT(value3.GetValue() == 2);
	ASSERT(value4.GetValue() == 1024);

	auto value5 = SimpleArithmeticExpression::Evaluate<Int32>("2 * (1 + 1)");
	auto value6 = SimpleArithmeticExpression::Evaluate<Int32>("1 + 2 * 3 + 4 / 2 + 10^2");
	auto value7 = SimpleArithmeticExpression::Evaluate<Int32>("(1 + (1 + 2) * (3 + 4)) / 2 + 10^(2^3)");
	ASSERT(value5.GetValue() == 4);
	ASSERT(value6.GetValue() == 100 + 9);
	ASSERT(value7.GetValue() == 100000000 + 11);

	//ASSERT(false);
}


EXEC_ONCE(Run);