#pragma once

#include "../Template.h"



namespace Engine
{
	/**
	* @remark
	* Elements of the array should be sorted(ascending/descending)
	*/
	template<typename T> Int32 BinarySearch(T* array, SizeType size, T target, Bool reversed = false);


#pragma region Details

	template<typename T>
	Int32 BinarySearch(T* array, SizeType size, T target, Bool reversed)
	{
		Function<Bool, T, T> Less		= [](T a, T b) { return a < b; };
		Function<Bool, T, T> Greater	= [](T a, T b) { return a > b; };

		Function<Bool, T, T> OpA = !reversed ? Less : Greater;
		Function<Bool, T, T> OpB = !reversed ? Greater : Less;


		Int32 low	= 0;
		Int32 high	= size - 1;

		while ( low <= high )
		{
			Int32 middle = ( high + low ) / 2;

			T selected = array[middle];
			if ( selected == target )
				return middle;
			else if ( OpA(selected, target) )
				low = middle + 1;
			else if ( OpB(selected, target ) )
				high = middle - 1;
		}

		return -1;
	}

#pragma endregion
}