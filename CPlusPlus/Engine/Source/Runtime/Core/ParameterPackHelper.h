#pragma once

#include "Template/AndOrNot.h"
#include "Template/Forward.h"
#include "Template/IsConvertible.h"



namespace Engine
{
	struct ParameterPackHelper
	{
		// Copy the value from parameter pack recursively until it is empty to a pointer point to heap/stack memory
		template<typename T, typename First, typename ...Parameters>
		static Void CopyTo(T* pointer, First&& value, Parameters&&... parameters)
		{
			static_assert( And<IsConvertible<First, T>, IsConvertible<Parameters, T> ...>::Value );


			*pointer = Forward<First>(value);

			if constexpr ( sizeof...(parameters) > 0 )
				CopyTo( pointer + 1, Forward<Parameters>(parameters)... );
		}
	};
}