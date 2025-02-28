#pragma once

#include "../../../TestFramework.h"



static Void Run()
{
	static_assert(Absolute(10) == 10);
	static_assert(Absolute(-1) == 1);

	static_assert(Approximate(0, Epsilon / 2));

	static_assert(Clamp(1, 0, 10) == 1);
	static_assert(Clamp(-1, 0, 10) == 0);
	static_assert(Clamp(11, 0, 10) == 10);

	static_assert(CountDigits(1) == 1);
	static_assert(CountDigits(12) == 2);
	static_assert(CountDigits(123) == 3);

	static_assert(DivideRoundUp(11, 10) == 2);
	static_assert(DivideRoundUp(19, 10) == 2);
	static_assert(DivideRoundUp(20, 10) == 2);

	static_assert(IsBetween(1, 0, 10));
	static_assert(IsBetween(0, 0, 10));
	static_assert(IsBetween(10, 0, 10));
	static_assert(!IsBetween<false, true>(0, 0, 10));
	static_assert(IsBetween<false, true>(10, 0, 10));
	static_assert(!IsBetween<true, false>(10, 0, 10));
	static_assert(IsBetween<true, false>(0, 0, 10));

	static_assert(IsPowerOfTwo<UInt64>(1));
	static_assert(IsPowerOfTwo<UInt64>(2));
	static_assert(!IsPowerOfTwo<UInt64>(3));
	static_assert(!IsPowerOfTwo<UInt64>(1023));
	static_assert(IsPowerOfTwo<UInt64>(1024));

	static_assert(Approximate(Lerp<RealType, RealType>(1, 10, 0.5), 5.5));
	static_assert(Approximate(Lerp<RealType, RealType>(1, 10, 0), 1));
	static_assert(Approximate(Lerp<RealType, RealType>(1, 10, 1), 10));

	static_assert(Maximum(1, 2, 3, 4, 5) == 5);
	static_assert(Minimum(1, 2, 3, 4, 5) == 1);

	static_assert(Power(2, 10) == 1024);

	static_assert(Approximate(Remap<RealType, RealType>(82, 0, 100, 0, 1), 0.82));

	static_assert(Sign(100) == 1);
	static_assert(Sign(-100) == -1);

	static_assert(Approximate(SquareRoot(4), 2));
	static_assert(Approximate(SquareRoot(2), 1.41421356237309));

	Int32 a = 1, b = 2;
	Swap(&a, &b);
	ASSERT(a == 2 && b == 1);

	//ASSERT(false);
}


EXEC_ONCE(Run);