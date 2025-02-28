#pragma once

#include "Forward.h"
#include "IsConvertible.h"



namespace Engine
{
	struct ParameterPackHelper
	{
		// Copy the value from parameter pack recursively(until it is empty) to a pointer point to heap/stack memory
		template<typename T, typename First, typename ...Parameters>
		static Void CopyTo(T* pointer, First&& value, Parameters&&... parameters)
		{
			static_assert( IsConvertible<First, T>::Value );


			*pointer = Forward<First>(value);

			if constexpr ( sizeof...(parameters) > 0 )
				CopyTo( pointer + 1, Forward<Parameters>(parameters)... );
		}
	};
}