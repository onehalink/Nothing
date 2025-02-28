#include "Application.h"



int main()
{
	Runtime runtime;
	runtime.wantToQuit = false;

	AppInit(&runtime);

	auto& inputSystem = runtime.inputSystem;

	auto& window = runtime.window;
	window.Attach(&inputSystem);
	window.OnResize = AppResize;
	window.OnClose = AppQuit;
	window.Create(runtime.windowTitle);
	
	Windows::GraphicsDeviceInterface gdi(window.handle);

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