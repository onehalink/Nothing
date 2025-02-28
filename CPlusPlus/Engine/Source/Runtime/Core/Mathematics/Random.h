#pragma once

#include "../Template.h"



namespace Engine::Private
{
	ENGINE_API RealType RandomReal(RealType minimum, RealType maximum);
}


namespace Engine
{
	// Minimum and maximum are included
	template<typename T>
	T Random(T minimum, T maximum)
	{
		static_assert( IsConvertible<T, RealType>::Value );
		static_assert( IsConvertible<RealType, T>::Value );


		return Private::RandomReal(minimum, maximum);
	}
}