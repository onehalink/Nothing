#pragma once

#include "../Mathematics/Numeric.h"



namespace Engine
{
	template<typename T, typename Predicate = Greater<>>
	Void QuickSort(T* array, Int32 low, Int32 high)
	{
		Function<Int32, T*, Int32, Int32> Partition = [](T* array, Int32 low, Int32 high)
			{
				T&		pivotElement	= array[high]; // select the last as pivot
				Int32	pivotIndex		= low;

				for(SizeType index = low; index < high; index++)
					if ( Predicate()( pivotElement, array[index] ) )
					{
						Swap( &array[pivotIndex], &array[index] );

						pivotIndex++;
					}

				Swap( &array[pivotIndex], &pivotElement );

				return pivotIndex;
			};


		if ( low >= high )
			return;

		Int32 pivotIndex = Partition(array, low, high);

		QuickSort<T, Predicate>( array, low,			pivotIndex - 1	);
		QuickSort<T, Predicate>( array, pivotIndex + 1,	high			);
	}
}