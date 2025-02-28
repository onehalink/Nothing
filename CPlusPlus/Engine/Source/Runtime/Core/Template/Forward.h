#pragma once

#include "RemoveReference.h"



namespace Engine
{
	// Forward lvalue as lvalue
	template<typename T> constexpr T&& Forward(typename RemoveReference<T>::Type& parameter);
	// Forward rvalue as rvalue
	template<typename T> constexpr T&& Forward(typename RemoveReference<T>::Type&& parameter);

	// Forward as movable(used when moving construction or assignment is required)
	template<typename T> constexpr typename RemoveReference<T>::Type&& Move(T&& parameter);


#pragma region Details

	template<typename T>
	constexpr T&& Forward(typename RemoveReference<T>::Type& parameter)
	{
		return static_cast<T&&>(parameter);
	}

	template<typename T>
	constexpr T&& Forward(typename RemoveReference<T>::Type&& parameter)
	{
		return static_cast<T&&>(parameter);
	}

	template<typename T>
	constexpr typename RemoveReference<T>::Type&& Move(T&& parameter)
	{
		return static_cast<typename RemoveReference<T>::Type&&>(parameter);
	}

#pragma endregion
}