#include "../TestFramework.h"



static Void UnitTest_Core_Algorithm_BinarySearch()
{
	constexpr SizeType ArraySize = 16;

	constexpr Int32 Min = 0;
	constexpr Int32 Max = 50;


	U8String output;
	BUILD_OUTPUT_FILENAME(output);
	File file(output, File::Mode::Write);

	Array<Int32> input(ArraySize);
	for (SizeType index = 0; index < ArraySize; index++)
	{
		Int32 value = Random(Min, Max);

		input.Add(value);
	}

	WriteFormatString(file, "Input: {}\n\n", GetArrayString(input));

	{
		QuickSort(input.GetBuffer(), 0, ArraySize - 1, false);

		auto selected = input[Random(0, ArraySize - 1)];
		auto result = BinarySearch(input.GetBuffer(), ArraySize, selected, false);

		WriteFormatString(file, "Sorted(Ascending): {}\nTarget = {} Find Index = {}\n\n", GetArrayString(input), selected, result);
	}

	{
		QuickSort(input.GetBuffer(), 0, ArraySize - 1, true);


		auto selected = input[Random(0, ArraySize - 1)];
		auto result = BinarySearch(input.GetBuffer(), ArraySize, selected, true);

		WriteFormatString(file, "Sorted(Descending): {}\nTarget = {} Find Index = {}\n\n", GetArrayString(input), selected, result);
	}

	{
		QuickSort(input.GetBuffer(), 0, ArraySize - 1, true);


		auto selected = Max + 1;
		auto result = BinarySearch(input.GetBuffer(), ArraySize, selected, true);

		WriteFormatString(file, "Sorted(Descending): {}\nTarget = {} Find Index = {}\n\n", GetArrayString(input), selected, result);
	}
}


EXEC_ONCE(UnitTest_Core_Algorithm_BinarySearch);