#pragma once

#include "Keyboard.h"



namespace Engine
{
	enum class MouseButton
	{
		Unknown,

		Left,
		Right,
		Middle,

		Count,
	};


	using MouseButtonState = KeyState;


	MouseButton MouseButtonMap(Int32 platformSpecificMouseButtonCode);
}