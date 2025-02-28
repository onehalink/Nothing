#pragma once

#include "../../TestFramework.h"



static Void Run()
{
	constexpr UInt16 uint16Value0 = 0x1234;
	constexpr UInt16 uint16Value1 = 0x3412;
	static_assert(ByteSwap(uint16Value0) == uint16Value1);

	constexpr UInt32 uint32Value0 = 0x12'34'56'78;
	constexpr UInt32 uint32Value1 = 0x78'56'34'12;
	static_assert(ByteSwap(uint32Value0) == uint32Value1);

	constexpr UInt64 uint64Value0 = 0x1122334455667788;
	constexpr UInt64 uint64Value1 = 0x8877665544332211;
	static_assert(ByteSwap(uint64Value0) == uint64Value1);
}


EXEC_ONCE(Run);