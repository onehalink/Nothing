#include "Application.h"



Int32 EntryPoint()
{
	Runtime runtime;
	runtime.wantToQuit = false;

	auto& window = runtime.window;
	auto& eventSystem = runtime.eventSystem;

	window.Create(runtime.windowTitle, 1600, 900, &eventSystem);

	GraphicDeviceInterface gdi(window.GetHandle());

	OnAppInit(&runtime);

	while (!runtime.wantToQuit)
	{
		static Timer timer;
		static RealType timestep = 0;
		timestep = timer.Elapsed();
		timer.Reset();

		window.Update();
		for (auto& event : eventSystem.eventQueue)
		{
			using EventType = EventSystem::Event::Type;


			switch (event.type)
			{
			case EventType::WindowResized:
			{
				SizeType width = event.WindowResizedParameters.width;
				SizeType height = event.WindowResizedParameters.height;

				window.SetWidth(width);
				window.SetHeight(height);

				OnAppResize(width, height);
			}
				break;
			case EventType::WindowFocused:
				OnAppFocus(event.WindowFocusedParameters.focused);
				break;
			case EventType::WindowClosed:
				OnAppQuit();
				break;

			case EventType::KeyTyped:
			{
				auto key = static_cast<EnumUnderlyingType<Key>>(event.KeyTypedParameters.key);
				auto state = event.KeyTypedParameters.state;

				eventSystem.keys[key] |= state;
			}
				break;

			case EventType::MouseButtonTyped:
			{
				auto button = static_cast<EnumUnderlyingType<Key>>(event.MouseButtonTypedParameters.button);
				auto state = event.MouseButtonTypedParameters.state;

				eventSystem.buttons[button] |= state;
			}
				break;
			case EventType::MouseMoved: 
			{
				auto x = event.MouseMovedParameters.x;
				auto y = event.MouseMovedParameters.y;

				eventSystem.mousePosition = { x, y };
			}
				break;
			case EventType::MouseWheelScrolled:
			{
				auto delta = event.MouseWheelScrolledParameters.delta;

				eventSystem.mouseWheelValue += delta;
			}
				break;
			}
		}

		OnUpdate(timestep);
		gdi.Present(window.GetWidth(), window.GetHeight(), OnRender);

		eventSystem.Reset();
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