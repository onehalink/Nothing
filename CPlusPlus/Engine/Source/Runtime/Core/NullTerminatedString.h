#pragma once

#include "Type.h"

#include "Template/IsChar.h"



namespace Engine::NullTerminatedString
{
	template<typename T>
	SizeType Length(const T* string)
	{
		static_assert( IsChar<T>::Value );


		SizeType length = 0;
		while ( *string++ != '\0' ) ++length;

		return length;
	}
}