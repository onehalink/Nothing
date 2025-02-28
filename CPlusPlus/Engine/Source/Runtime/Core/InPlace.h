#pragma once

#include "Type.h"



namespace Engine
{
	// Tag uses to select a specific class's constructor

	struct InPlace
	{

	};


	template<typename T>
	struct InPlaceType
	{

	};


	template<SizeType Index>
	struct InPlaceIndex
	{

	};
}