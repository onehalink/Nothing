#pragma once

#include "../Build.h"
#include "../Type.h"

#include "../Template/IsArithmetic.h"
#include "../Template/IsFloatPoint.h"

#include "Numeric.h"



namespace Engine
{
	/**
	* @remark
	* Minimum and maximum are included
	*/
	template<typename T> T Random(T minimum, T maximum);


#pragma region Details

	namespace Private
	{
		ENGINE_API RealType RandomReal(RealType minimum, RealType maximum);
	}


	template<typename T>
	T Random(T minimum, T maximum)
	{
		static_assert( IsArithmetic<T>::Value );

		
		if constexpr ( IsFloatPoint<T>::Value )
			return Private::RandomReal(minimum, maximum);
		else
			return Lerp( minimum, maximum, Private::RandomReal(0, 1) );
	}

#pragma endregion
}