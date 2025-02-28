#pragma once

#include "RemoveAllExtents.h"
#include "RemoveAllPointers.h"
#include "RemoveConst.h"
#include "RemoveReference.h"



namespace Engine
{
	template<typename T>
	struct RemoveAllQualifiers
	{
		using Type =
			typename RemoveConst<
			typename RemoveAllPointers<
			typename RemoveReference<
			typename RemoveAllExtents<T>::Type>::Type>::Type>::Type;
	};
}