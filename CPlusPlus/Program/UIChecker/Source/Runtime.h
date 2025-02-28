#pragma once

#include "Engine.h"



using namespace Engine;


struct Runtime
{
	Windows::Window window;
	U16String windowTitle = L"UI Checker";
	InputSystem inputSystem;

	Bool wantToQuit;
};