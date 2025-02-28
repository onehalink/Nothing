#include "Application.h"



static Runtime* runtime;

Void OnAppInit(Void* userParameter)
{
	TRACE("{} execute\n", __FUNCTION__);

	runtime = reinterpret_cast<Runtime*>(userParameter);
}

Void OnAppResize(SizeType width, SizeType height)
{
	TRACE("New Resolution: {}x{}\n", width, height);
}

Void OnAppFocus(Bool focused)
{
	TRACE("{} focus\n", focused ? "Gain" : "Lost");
}

Void OnAppQuit()
{
	TRACE("{} execute\n", __FUNCTION__);

	runtime->wantToQuit = true;
}

Void OnUpdate(RealType deltaTime)
{
	if (runtime->eventSystem.KeyClicked(Key::Escape))
		runtime->wantToQuit = true;

	//runtime->window.SetTitle(Format(U8String("Hello Window(FPS: {})"), static_cast<Int32>(1 / deltaTime)));

	/*
	if (runtime->eventSystem.KeyClicked(Key::R))
	{
		U16String text;
		if (Clipboard::ReadText(&text))
		{
			TRACE("Read \"{}\" from clipboard\n", text);
		}
	}

	if (runtime->eventSystem.KeyClicked(Key::W))
	{
		U16String text = "Hello, Clipboard";
		if (Clipboard::WriteText(text))
		{
			TRACE("Write \"{}\" to clipboard\n", text);
		}
	}
	*/
}

Void OnRender(Void* RenderTarget)
{
	SizeType width = runtime->window.GetWidth();
	SizeType height = runtime->window.GetHeight();
	
	//UInt32 clearColor = ToB8G8R8A8(Color::Red);
	UInt32 clearColor = ToB8G8R8A8(Color::Black);

	for (SizeType y = 0; y < height; y++)
		for (SizeType x = 0; x < width; x++)
			reinterpret_cast<UInt32*>(RenderTarget)[width * y + x] = clearColor;
}
