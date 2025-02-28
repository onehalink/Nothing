#pragma once

#include "Engine.h"


using namespace Engine;
using namespace Engine::Windows;



struct Runtime
{
	Window window;
	U8String windowTitle = "IMUI Checker";
	EventSystem eventSystem;

	Bool wantToQuit;
};