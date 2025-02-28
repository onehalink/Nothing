#include "Application.h"



static Runtime* runtime;

static Serface serface;

static RealType processBarValue = 0;

static Texture texture;
static Bool requireUpload;


Void OnAppInit(Void* userParameter)
{
	runtime = reinterpret_cast<Runtime*>(userParameter);

	{
		requireUpload = true;
		texture = Image::LoadFromFile("swimsuits.jpg");

		//texture = texture.ConvertPixelFormat(PixelFormat::R8G8B8);
	}
}

Void OnAppResize(SizeType width, SizeType height)
{
	runtime->window.width = width;
	runtime->window.height = height;

	serface = { width, height };
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
	if (runtime->inputSystem.keyboard.KeyClicked(Keyboard::Key::Escape))
		runtime->wantToQuit = true;

	processBarValue += deltaTime * 0.1;
	if (processBarValue > 1)
		processBarValue = 0;
}

Void OnRender(Void* RenderTarget)
{
	serface.Clear();

	// render
	{
		auto& fb = serface;

		Text(&fb, Vector2Int::One * 100, "Hello, Text");

		static Button button(Vector2Int(200, 50), Vector2Int(150, 30),
			"Hello, Button",
			[]()
			{
				Debug::Trace("Clicked!\n");
			},
			[]()
			{
				//Debug::Trace("Pressed!\n");
			}
		);
		button.Update(runtime->inputSystem);
		button.Render(&fb);

		static ScrollBar scrollbar(Vector2Int(400, 50), Vector2Int(150, 30),
			Direction::LeftToRight,
			[](RealType value)
			{
				Debug::Trace("value(ScrollBar): {}\n", value);
			}
		);
		scrollbar.Update(runtime->inputSystem);
		scrollbar.Render(&fb);

		static ProcessBar pb(Vector2Int(100, 120), Vector2Int(150, 30), Direction::LeftToRight);
		pb.value = processBarValue;
		pb.Update(runtime->inputSystem);
		pb.Render(&fb);


		static CircleProcessBar cpb(Vector2Int(300, 300), 100, 80);
		cpb.value = processBarValue;
		cpb.Update(runtime->inputSystem);
		cpb.Render(&fb);

		{
			static ScrollView ui(Vector2Int(600, 20), Vector2Int(800, 600), Vector2Int(800, 600));
			ui.Update(runtime->inputSystem);
			ui.Render(&fb);

			if (requireUpload)
			{
				requireUpload = false;

				ui.SetContentSize({ texture.width, texture.height });

				auto& serface = ui.content.serface;
				for (SizeType y = 0; y < serface.height; y++)
					for (SizeType x = 0; x < serface.width; x++)
					{
						serface.SetPixel(x, y,
							FromR8G8B8(
								texture.GetPixel(x, y)
							)
						);
					}
			}
		}

	}

	serface.CopyTo(RenderTarget);
}
