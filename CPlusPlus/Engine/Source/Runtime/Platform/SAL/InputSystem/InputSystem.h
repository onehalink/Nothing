#pragma once

#include "Keyboard.h"
#include "Mouse.h"



namespace Engine
{
	struct InputSystem
	{
		Action<>					OnWindowClosed	= []() {};
		Action<Bool>				OnWindowFocused = [](Bool) {};
		Action<SizeType, SizeType>	OnWindowResized	= [](SizeType, SizeType){};


		Keyboard	keyboard;
		Mouse		mouse;
	};
}