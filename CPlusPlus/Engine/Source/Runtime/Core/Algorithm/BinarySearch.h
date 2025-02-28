#pragma once

#include "../CoreMinimal.h"



namespace Engine
{
	/**
	* @remark
	* Elements of the array should be sorted(ascending/descending)
	*/
	template<typename Predicate = Less<>, typename T>
	Int32 BinarySearch(const T* array, SizeType size, T target)
	{
		Int32 low	= 0;
		Int32 high	= size - 1;

		while ( low <= high )
		{
			Int32 middle = ( high + low ) / 2;

			T selected = array[middle];
			if ( selected == target )
				return middle;
			else if ( Predicate()(selected, target) )
				low = middle + 1;
			else
				high = middle - 1;
		}

		return -1;
	}
}