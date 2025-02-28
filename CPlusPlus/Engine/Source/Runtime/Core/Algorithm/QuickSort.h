#pragma once

#include "../Template.h"

#include "../Mathematics/NumericCalculation.h"



namespace Engine
{
	template<typename T> Void QuickSort(T* array, Int32 low, Int32 high, Bool reversed = false);


#pragma region Details

	template<typename T>
	Int32 Partition(T* array, Int32 low, Int32 high, Bool reversed)
	{
		Function<Bool, T, T> LEqual = [](T a, T b) { return a <= b; };
		Function<Bool, T, T> GEqual = [](T a, T b) { return a >= b; };


		Function<Bool, T, T> Op;
		if ( !reversed )
			Op = GEqual;
		else
			Op = LEqual;

		T&		pivotElement	= array[high]; // select the last as pivot
		Int32	pivotIndex		= low;

		for(SizeType index = low; index < high; index++)
			if ( Op( pivotElement, array[index] ) )
			{
				Swap( &array[pivotIndex], &array[index] );

				pivotIndex++;
			}

		Swap( &array[pivotIndex], &pivotElement );

		return pivotIndex;
	}

	template<typename T>
	Void QuickSort(T* array, Int32 low, Int32 high, Bool reversed)
	{
		if ( low >= high )
			return;

		Int32 pivotIndex = Partition(array, low, high, reversed);

		QuickSort( array, low,			pivotIndex - 1,	reversed );
		QuickSort( array, pivotIndex,	high,			reversed );
	}

#pragma endregion
}