#pragma once

#include "../Template/FunctionPointer.h"



namespace Engine
{
	template<typename T> Void QuickSort(T* array, Int32 low, Int32 high, Bool reversed = false);


#pragma region Details

	namespace Private
	{
		template<typename T>
		Int32 Partition(T* array, Int32 low, Int32 high, Bool reversed)
		{
			Function<Bool, T, T> Less		= [](T a, T b) { return a < b; };
			Function<Bool, T, T> Greater	= [](T a, T b) { return a > b; };


			Function<Bool, T, T> Op;
			if ( !reversed )
				Op = Greater;
			else
				Op = Less;

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
		};
	}


	template<typename T>
	Void QuickSort(T* array, Int32 low, Int32 high, Bool reversed)
	{
		if ( low >= high )
			return;

		Int32 pivotIndex = Private::Partition(array, low, high, reversed);

		QuickSort( array, low,				pivotIndex - 1,	reversed );
		QuickSort( array, pivotIndex + 1,	high,			reversed );
	}

#pragma endregion
}