#pragma once

#include "../Type.h"

#include "BoolConstant.h"
#include "SameAsAny.h"



namespace Engine
{
	template<typename T>
	struct IsSigned : BoolConstant<SameAsAny<T, Int8, Int16, Int32, Int64>::Value>
	{

	};


	template<typename T>
	struct IsUnsigned : BoolConstant<SameAsAny<T, UInt8, UInt16, UInt32, UInt64>::Value>
	{

	};


	template<typename T>
	struct IsIntegral : BoolConstant<IsSigned<T>::Value || IsUnsigned<T>::Value>
	{

	};
}