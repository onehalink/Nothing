#include "Application.h"



static Runtime* runtime;

static Serface serface;

static RealType processValue = 0;

static Texture texture;
static Bool requireUpload;


Void OnAppInit(Void* userParameter)
{
	runtime = reinterpret_cast<Runtime*>(userParameter);

	{
		U8String path = "../../../Asset/Font/DefaultFont.ttf";
		U8String fontSDFAtlasPath = Path::ChangeFileExtension(path, ".glyphsdf");
		if (false)
		{
			auto font = LoadFontFromFile(path);

			Debug::Trace("Start(Build)!");
			UI::fontSDFAtlasStack.Push(FontSDFAtlas(&font));
			Debug::Trace("End(Build)!");

			if (File::Exist(fontSDFAtlasPath))
				File::Delete(fontSDFAtlasPath);

			Debug::Trace("Start(Save)!");
			UI::fontSDFAtlasStack.Top().SaveToFile(fontSDFAtlasPath);
			Debug::Trace("End(Save)!");
		}
		else
			UI::fontSDFAtlasStack.Push(FontSDFAtlas::LoadFromFile(fontSDFAtlasPath));
	}

	{
		requireUpload = true;
		texture = Image::LoadFromFile("../../../Asset/Image/raiza_visual_0014.jpg");
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
	processValue += deltaTime * 0.1;
	if (processValue > 1)
		processValue = 0;

	runtime->window.SetTitle(Format("{} (FPS: {})", runtime->title, static_cast<UInt32>(1 / deltaTime)));
}

Void OnRender(Void* RenderTarget)
{
	serface.Clear();

	// render
	{
		Int32 lineSpace = fontSDFAtlasStack.Top().lineSpace;
		Vector2Int contentOffset = Vector2Int(16, 0);

		Vector2Int penPostion = {
			0,
			serface.height - lineSpace
		};

		// Text
		{
			Text(&serface, penPostion, "[Text]", Color::Green);

			penPostion.y -= lineSpace;
			Text(&serface, penPostion + contentOffset, STRING_LITERAL(Char32, "The Quick Brown Fox Jumps The Lazy Dog"));

			penPostion.y -= lineSpace;
			Text(&serface, penPostion + contentOffset, STRING_LITERAL(Char32, "一只迅捷的棕色的狐狸从懒狗身上跳过"));
		}

		// Button
		{
			penPostion.y -= lineSpace;
			Text(&serface, penPostion, "[Button]", Color::Green);

			penPostion.y -= lineSpace * 2.2;
			static Button button(Vector2::Zero, Vector2Int(150, 30),
				"Click Me",
				[]()
				{
					Debug::Trace("button clicked");
				}
			);
			button.rectangle.SetPosition(penPostion + contentOffset);
			button.Update(runtime->inputSystem);
			button.Render(&serface);
		}

		// CheckBox
		{
			penPostion.y -= lineSpace;
			Text(&serface, penPostion, "[CheckBox]", Color::Green);

			Int32 size = 30;
			penPostion.y -= size + lineSpace * 0.5;

			static CheckBox checkBox(Vector2::Zero, size,
				[](Bool value)
				{
					Debug::Trace("value(CheckBox) = {}", value);
				}
			);

			checkBox.rectangle.SetPosition(penPostion + contentOffset);

			checkBox.Update(runtime->inputSystem);
			checkBox.Render(&serface);
		}

		// TextInput
		{
			penPostion.y -= lineSpace;
			Text(&serface, penPostion, "[TextInput]", Color::Green);

			Vector2Int size = Vector2(150, 30);
			penPostion.y -= size.y + lineSpace * 0.5;

			static UI::TextInput textInput(Vector2::Zero, size);

			textInput.rectangle.SetPosition(penPostion + contentOffset);

			textInput.Update(runtime->inputSystem);
			textInput.Render(&serface);
		}

		// ProcessBar
		{
			penPostion.y -= lineSpace;
			Text(&serface, penPostion, "[ProcessBar]", Color::Green);

			penPostion.y -= lineSpace * 2.2;

			ProcessBar(&serface, penPostion + contentOffset, Vector2Int(150, 30), processValue);
		}

		// ScrollBar
		{
			penPostion.y -= lineSpace;
			Text(&serface, penPostion, "[ScrollBar]", Color::Green);

			penPostion.y -= lineSpace * 2.2;
			static ScrollBar scrollbar(Vector2::Zero, Vector2Int(150, 30),
				Direction::LeftToRight,
				[](RealType value)
				{
					Debug::Trace("value(ScrollBar): {}", value);
				}
			);

			scrollbar.rectangle.SetPosition(penPostion + contentOffset);
			scrollbar.isDirty = true;

			scrollbar.Update(runtime->inputSystem);
			scrollbar.Render(&serface);

		}

		// ScrollView
		{
			penPostion.y -= lineSpace;
			Text(&serface, penPostion, "[ScrollView]", Color::Green);

			Vector2Int scrollViewSize = Vector2Int(600, 400);
			penPostion.y -= scrollViewSize.y + lineSpace * 0.5;

			static ScrollView scrollView(Vector2::Zero, scrollViewSize, Vector2::Zero);

			scrollView.rectangle.SetPosition(penPostion + contentOffset);
			scrollView.isDirty = true;

			scrollView.Update(runtime->inputSystem);
			scrollView.Render(&serface);

			if (requireUpload)
			{
				requireUpload = false;

				auto& serface = scrollView.content.serface;

				serface = { texture.width, texture.height };
				scrollView.isDirty = true;


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

		// CombineBox
		{
			penPostion.y -= lineSpace;
			Text(&serface, penPostion, "[CombineBox]", Color::Green);

			penPostion.y -= lineSpace * 2.2;

			static CombineBox combineBox(Vector2::Zero, Vector2(200, 30),
				[](Int32 value)
				{
					Debug::Trace("index(CombineBox) = {}", value);
				}
			);

			combineBox.rectangle.SetPosition(penPostion + contentOffset);

			combineBox.Update(runtime->inputSystem);
			combineBox.Render(&serface);
		}
	}

	serface.CopyTo(RenderTarget);
}
