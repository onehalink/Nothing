#pragma once

#include "Engine.h"
#include "ImageCodec.h"



using namespace Engine;

using namespace Engine::UI;

using namespace Engine::Windows;
using namespace Engine::FileSystem;

using namespace Engine::Plugin;


struct Runtime
{
	Window window;
	U8String title = "UI Checker Viewer";
	InputSystem inputSystem;

	Bool wantToQuit;
};