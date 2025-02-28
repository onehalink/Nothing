#pragma once

#include "../Template/FunctionPointer.h"



namespace Engine
{
	/**
	* @remark
	* Elements of the array should be sorted(ascending/descending)
	*/
	template<typename T>
	Int32 BinarySearch(T* array, SizeType size, T target, Bool reversed)
	{
		Function<Bool, T, T> Less		= [](T a, T b) { return a < b; };
		Function<Bool, T, T> Greater	= [](T a, T b) { return a > b; };

		Function<Bool, T, T> Op = !reversed ? Less : Greater;


		Int32 low	= 0;
		Int32 high	= size - 1;

		while ( low <= high )
		{
			Int32 middle = ( high + low ) / 2;

			T selected = array[middle];
			if ( selected == target )
				return middle;
			else if ( Op(selected, target) )
				low = middle + 1;
			else
				high = middle - 1;
		}

		return -1;
	}
}