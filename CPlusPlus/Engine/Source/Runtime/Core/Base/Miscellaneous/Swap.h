#pragma once

#include "../Type.h"



namespace Engine
{
	// Swap the value of a and b
	template<typename T>
	Void Swap(T* a, T* b)
	{
		T temporary	= *a;
		*a			= *b;
		*b			= temporary;
	}
}
