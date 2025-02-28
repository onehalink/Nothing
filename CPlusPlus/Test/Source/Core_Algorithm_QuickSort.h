#pragma once

#include "APISet.h"



inline Void Test_Core_Algorithm_QuickSort()
{
	constexpr SizeType Size = 16;
	constexpr RealType Minimum = 0;
	constexpr RealType Maximum = 200;


	std::fstream output("Test_Core_Algorithm_QuickSort.log", std::ios::out | std::ios::trunc);

	Array<RealType> input;
	for (SizeType index = 0; index < Size; index++)
		input.Add(Random(Minimum, Maximum));

	U8String format =
		"{name}\n"
		"elements: ";

	output << Format(format, "Input");
	{
		for (auto& value : input)
			output << value << ", ";
	}
	output << "\n\n";

	auto temporary = input;

	QuickSort(temporary.GetBuffer(), 0, temporary.GetCount() - 1, false);
	output << Format(format, "QuickSort(Normal)");
	{
		for (auto& value : temporary)
			output << value << ", ";
	}
	output << "\n\n";

	QuickSort(temporary.GetBuffer(), 0, temporary.GetCount() - 1, true);
	output << Format(format, "QuickSort(Reversed)");
	{
		for (auto& value : temporary)
			output << value << ", ";
	}
	output << "\n\n";
}