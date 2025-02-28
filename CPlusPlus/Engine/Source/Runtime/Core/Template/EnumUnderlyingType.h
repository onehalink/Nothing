#pragma once

#include "EnableIf.h"
#include "IsEnum.h"



namespace Engine
{
	template<typename Enum>
	using EnumUnderlyingType = typename EnableIf<IsEnum<Enum>::Value, __underlying_type(Enum)>::Type;
}