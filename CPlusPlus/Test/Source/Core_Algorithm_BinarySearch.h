#pragma once

#include "APISet.h"



inline Void Test_Core_Algorithm_BinarySearch()
{
	constexpr SizeType Size = 10;
	constexpr RealType Minimum = 0;
	constexpr RealType Maximum = 50;


	std::fstream output("Test_Core_Algorithm_BinarySearch.log", std::ios::out | std::ios::trunc);

	Array<Int32> input;
	for (SizeType index = 0; index < Size; index++)
		input.Add(Random(Minimum, Maximum));

	U8String format0 =
		"{name}\n"
		"elements: ";

	U8String format1 =
		"{name}\n"
		"SortOrder:{}\n"
		"elements: ";

	output << Format(format0, "Input");
	{
		for (auto& value : input)
			output << value << ", ";
	}
	output << "\n\n";


	QuickSort(input.GetBuffer(), 0, input.GetCount() - 1, false);
	output << Format(format1, "BinarySearch", "Ascending");
	{
		for (auto& value : input)
			output << value << ", ";

		output << "\n";

		Int32 target = input[Random(0, Size - 1)];
		Int32 findIndex = BinarySearch(input.GetBuffer(), input.GetCount(), target, false);
		output << Format(U8String("Target:{} | Find Index: {}\n"), target, findIndex);
	}
	output << "\n";

	QuickSort(input.GetBuffer(), 0, input.GetCount() - 1, true);
	output << Format(format1, "BinarySearch", "Descending");
	{
		for (auto& value : input)
			output << value << ", ";

		output << "\n";

		Int32 target = input[Random(0, Size - 1)];
		Int32 findIndex = BinarySearch(input.GetBuffer(), input.GetCount(), target, true);
		output << Format(U8String("Target:{} | Find Index: {}\n"), target, findIndex);
	}
	output << "\n";

	QuickSort(input.GetBuffer(), 0, input.GetCount() - 1, true);
	output << Format(format1, "BinarySearch", "Descending");
	{
		for (auto& value : input)
			output << value << ", ";

		output << "\n";

		Int32 target = Maximum * 2;
		Int32 findIndex = BinarySearch(input.GetBuffer(), input.GetCount(), target, true);
		output << Format(U8String("Target:{} | Find Index: {}\n"), target, findIndex);
	}
	output << "\n";

}

