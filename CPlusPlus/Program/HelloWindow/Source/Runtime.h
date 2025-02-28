#pragma once

#include "Engine.h"



using namespace Engine;
using namespace Engine::Windows;


struct Runtime
{
	Window window;
	EventSystem eventSystem;

	Bool wantToQuit;
};