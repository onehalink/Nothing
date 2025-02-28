#include "Application.h"



static Runtime* runtime;
EventSystem* eventSystem;

static FrameBuffer frameBuffer;

static Texture texture;
static Bool requireUpload;

Void OnAppInit(Void* userParameter)
{
	runtime = reinterpret_cast<Runtime*>(userParameter);
	eventSystem = &runtime->eventSystem;

	{
		texture = Image::LoadFromFile("swimsuits.jpg");
		requireUpload = true;
	}
}

Void OnAppResize(SizeType width, SizeType height)
{
	frameBuffer = { width, height };
}

Void OnAppFocus(Bool focused)
{

}

Void OnAppQuit()
{
	runtime->wantToQuit = true;
}

Void OnUpdate(RealType deltaTime)
{

}

Void OnRender(Void* RenderTarget)
{
	// frame begin
	frameBuffer.Clear();

	// render
	{
		// Text
		{
			UI::Text(&frameBuffer, Vector2Int::One * 50, "Hello, Text!");
		}

		// Button
		{
			static UI::Button ui(
				{ 100, 100 },
				{ 250, 40 },
				"This is a button(Clicked)",
				[]()
				{
					Debug::Trace("Button clicked!!");
				}
			);
			ui.Update(*eventSystem);
			ui.Render(&frameBuffer);
		}

		// ScrollBar
		{
			static UI::ScrollBar ui(
				{ 100, 200 },
				{200, 50}
			);

			ui.OnValueChange = [](RealType value)
				{
					Debug::Trace("ScrollBar value(0 - 1): {}", value);
				};

			ui.Update(*eventSystem);
			ui.Render(&frameBuffer);
		}

		// ScrollView
		{
			static UI::ScrollView ui(
				Vector2{ 700, 100 }
			);
			ui.Update(*eventSystem);
			ui.Render(&frameBuffer);

			if (requireUpload)
			{
				requireUpload = false;

				ui.SetPosition(Vector2(frameBuffer.width * 0.25, frameBuffer.height * 0.1));
				ui.SetSize(Vector2(frameBuffer.width * 0.7, frameBuffer.height * 0.7));

				ui.SetContentSize({ texture.width, texture.height });

				auto& serface = ui.content.texture;
				for (SizeType y = 0; y < serface.height; y++)
					for (SizeType x = 0; x < serface.width; x++)
					{
						serface.SetPixel(x, y,
							texture.GetPixel(x, y)
						);
					}
			}
		}

	}

	// frame end
	frameBuffer.CopyTo(RenderTarget);
}
