#pragma once

#include "Engine.h"
#include "ImageCodec.h"



using namespace Engine;
using namespace Engine::Windows;

using namespace Engine::Plugin;


struct Runtime
{
	Window window;
	EventSystem eventSystem;

	Bool wantToQuit;


	// Preset
	U8String windowTitle = "UI Checker";
};