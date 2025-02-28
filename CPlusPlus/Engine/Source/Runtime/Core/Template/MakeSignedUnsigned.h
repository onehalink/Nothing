#pragma once

#include "../ParameterPack.h"
#include "../Type.h"

#include "IsIntegral.h"



namespace Engine
{
	template<typename T>
	struct MakeSigned
	{
		using Type = typename ParameterPack::Nth<
			sizeof(T) == 1 ? 0 :
			sizeof(T) == 2 ? 1 :
			sizeof(T) == 4 ? 2 :
			sizeof(T) == 8 ? 3 : -1,
			Int8, Int16, Int32, Int64>::Type;
	};


	template<typename T>
	struct MakeUnsigned
	{
		using Type = typename ParameterPack::Nth<
			sizeof(T) == 1 ? 0 :
			sizeof(T) == 2 ? 1 :
			sizeof(T) == 4 ? 2 :
			sizeof(T) == 8 ? 3 : -1,
			UInt8, UInt16, UInt32, UInt64>::Type;
	};
}