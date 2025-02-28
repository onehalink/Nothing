#pragma once

#include "../Type.h"



namespace Engine
{
	template<typename T> struct NumericLimit;

	template<> struct NumericLimit<Int8>;
	template<> struct NumericLimit<Int16>;
	template<> struct NumericLimit<Int32>;
	template<> struct NumericLimit<Int64>;

	template<> struct NumericLimit<UInt8>;
	template<> struct NumericLimit<UInt16>;
	template<> struct NumericLimit<UInt32>;
	template<> struct NumericLimit<UInt64>;

	template<> struct NumericLimit<Float32>;
	template<> struct NumericLimit<Float64>;


#pragma region Details

	template<>
	struct NumericLimit<Int8>
	{
		static constexpr Int8 Minimum = 0x80;
		static constexpr Int8 Maximum = 0x7F;
	};

	template<>
	struct NumericLimit<Int16>
	{
		static constexpr Int16 Minimum = 0x8000;
		static constexpr Int16 Maximum = 0x7FFF;
	};

	template<>
	struct NumericLimit<Int32>
	{
		static constexpr Int32 Minimum = 0x80000000;
		static constexpr Int32 Maximum = 0x7FFFFFFF;
	};

	template<>
	struct NumericLimit<Int64>
	{
		static constexpr Int64 Minimum = 0x8000000000000000;
		static constexpr Int64 Maximum = 0x7FFFFFFFFFFFFFFF;
	};

	template<>
	struct NumericLimit<UInt8>
	{
		static constexpr UInt8 Minimum = 0x00;
		static constexpr UInt8 Maximum = 0xFF;
	};

	template<>
	struct NumericLimit<UInt16>
	{
		static constexpr UInt16 Minimum = 0x0000;
		static constexpr UInt16 Maximum = 0xFFFF;
	};

	template<>
	struct NumericLimit<UInt32>
	{
		static constexpr UInt32 Minimum = 0x00000000;
		static constexpr UInt32 Maximum = 0xFFFFFFFF;
	};

	template<>
	struct NumericLimit<UInt64>
	{
		static constexpr UInt64 Minimum = 0x0000000000000000;
		static constexpr UInt64 Maximum = 0xFFFFFFFFFFFFFFFF;
	};

	template<>
	struct NumericLimit<Float32>
	{
		static constexpr Float32 Minimum = 1.175494351E-38F; // minimum positive
		static constexpr Float32 Maximum = 3.402823466E+38F;
	};

	template<>
	struct NumericLimit<Float64>
	{
		static constexpr Float64 Minimum = 2.2250738585072014E-308; // minimum positive
		static constexpr Float64 Maximum = 1.7976931348623158E+308;
	};

#pragma endregion
}