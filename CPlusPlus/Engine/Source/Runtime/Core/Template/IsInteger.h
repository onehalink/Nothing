#pragma once

#include "SameAsAny.h"



namespace Engine
{
	template<typename T>
	struct IsSignedInteger : BoolConstant<SameAsAny<T, Int8, Int16, Int32, Int64>::Value>
	{

	};


	template<typename T>
	struct IsUnsignedInteger : BoolConstant<SameAsAny<T, UInt8, UInt16, UInt32, UInt64>::Value>
	{

	};


	template<typename T>
	struct IsInteger : BoolConstant<IsSignedInteger<T>::Value || IsUnsignedInteger<T>::Value>
	{

	};
}
