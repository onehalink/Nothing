#include "Application.h"



Int32 EntryPoint()
{
	Runtime runtime;
	runtime.wantToQuit = false;

	OnAppInit(&runtime);

	auto& inputSystem = runtime.inputSystem;
	inputSystem.OnWindowResized = OnAppResize;
	inputSystem.OnWindowFocused = OnAppFocus;
	inputSystem.OnWindowClosed = OnAppQuit;

	auto& window = runtime.window;
	window.Create(runtime.title, 1600, 900, &inputSystem);

	GraphicDeviceInterface gdi(window.handle);

	while (!runtime.wantToQuit)
	{
		static Timer timer;
		static RealType timestep = 0;
		timestep = timer.Elapsed();
		timer.Reset();

		window.Update();

		OnUpdate(timestep);
		gdi.Present(window.width, window.height, OnRender);

		inputSystem.Reset();
	}

	return 0;
}


int main(int count, char** parameters)
{
	return EntryPoint();
}


#if defined(PLATFORM_WINDOWS)
#include <Windows.h>


int WINAPI wWinMain(HINSTANCE current, HINSTANCE previous, PWSTR commandLine, int command)
{
	return EntryPoint();
}

#endif