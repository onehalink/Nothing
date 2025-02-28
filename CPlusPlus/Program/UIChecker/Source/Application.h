#pragma once

#include "Runtime.h"



Void AppInit(Void* userParameter);
Void AppResize(SizeType width, SizeType height);
Void AppQuit();

Void OnUpdate(RealType deltaTime);
Void OnRender(Void* renderTarget);