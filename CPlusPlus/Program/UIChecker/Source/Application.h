#pragma once

#include "Runtime.h"



Void OnAppInit(Void* userParameter);
Void OnAppResize(SizeType width, SizeType height);
Void OnAppFocus(Bool focused);
Void OnAppQuit();

Void OnUpdate(RealType deltaTime);
Void OnRender(Void* RenderTarget);