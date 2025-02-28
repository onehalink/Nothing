#pragma once

#include "Engine.h"
#include "ImageCodec.h"



using namespace Engine;
using namespace Engine::Windows;

using namespace Engine::Plugin;


struct Runtime
{
	Window window;
	U8String windowTitle = "Image Viewer";
	EventSystem eventSystem;

	Bool wantToQuit;


	//static constexpr RealType MinimumScale = 0.01; // 1%
	static constexpr RealType MaximumScale = 8; // 800%
	static constexpr RealType MouseWheelSense = 0.08; // 8%

	Bool imageLoaded = false;
	Texture image;

	RealType imageRequiredScale; // display area is full filled
	RealType imageCurrentScale;

	Bool isHold = false;
	Vector2Int beginDragPoint = Vector2Int::Zero;
	Vector2Int imageOffset = Vector2Int::Zero;
	Vector2Int imageLastOffset = Vector2Int::Zero;
};