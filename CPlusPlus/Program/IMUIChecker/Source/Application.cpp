#include "Application.h"

#include "ImageCodec.h"



using namespace Engine::Plugin;


static Runtime* runtime;

FrameBuffer fb;

RealType value = 0;

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
	fb = { width, height };
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
	value += deltaTime * 0.1;
}

Void OnRender(Void* RenderTarget)
{
	fb.Clear();

	// render
	{
		IMUI::Text(&fb, Vector2Int::One * 100, "Hello, Text");

		static IMUI::Button button(Vector2Int(200, 50), Vector2Int(150, 30),
			"Hello, Button",
			[]()
			{
				LogSystem::DefaultLogger.Trace("Clicked!\n");
			},
			[]()
			{
				//LogSystem::DefaultLogger.Trace("Pressed!\n");
			}
		);
		button.Update(runtime->eventSystem);
		button.Render(&fb);

		static IMUI::ScrollBar scrollbar(Vector2Int(400, 50), Vector2Int(150, 30),
			IMUI::Direction::LeftToRight,
			[](RealType value)
			{
				LogSystem::DefaultLogger.Trace("New value(ScrollBar): {}\n", value);
			}
		);
		scrollbar.Update(runtime->eventSystem);
		scrollbar.Render(&fb);

		static IMUI::ProcessBar pb(Vector2Int(100, 120), Vector2Int(150, 30), IMUI::Direction::LeftToRight);
		pb.value = value;
		pb.Update(runtime->eventSystem);
		pb.Render(&fb);


		static IMUI::CircleProcessBar cpb(Vector2Int(300, 300), 100, 80);
		cpb.value = value;
		cpb.Update(runtime->eventSystem);
		cpb.Render(&fb);

		{
			static IMUI::ScrollView ui(Vector2Int(600, 20), Vector2Int(800, 600), Vector2Int(800, 600));
			ui.Update(runtime->eventSystem);
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

	fb.CopyTo(RenderTarget);
}
