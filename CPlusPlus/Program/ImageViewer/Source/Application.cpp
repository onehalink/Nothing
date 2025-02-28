#include "Application.h"



static Runtime* runtime;


Void OnAppInit(Void* userParameter)
{
	runtime = reinterpret_cast<Runtime*>(userParameter);

	runtime->inputSystem.keyboard.UpdateKeyState(Keyboard::Key::O, Keyboard::State::Click);
}

Void OnAppResize(SizeType width, SizeType height)
{
	runtime->window.width = width;
	runtime->window.height = height;
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

	runtime->window.SetTitle(Format(U8String("{Title}(Scale: {}%)"), runtime->title, static_cast<Int32>(runtime->imageCurrentScale * 100)));

	if (runtime->inputSystem.mouse.ButtonPressed(Mouse::Button::Left))
	{
		if (!runtime->isHold)
		{
			runtime->isHold = true;

			runtime->imageLastOffset = runtime->imageOffset;
			runtime->beginDragPoint = runtime->inputSystem.mouse.position;
		}

		runtime->imageOffset = runtime->imageLastOffset + (runtime->inputSystem.mouse.position - runtime->beginDragPoint);
	}
	else
	{
		runtime->isHold = false;
	}

	if (runtime->inputSystem.keyboard.KeyClicked(Keyboard::Key::O))
		if (auto selected = FileDialog::Open({ InPlace(), "*.jpg", "*.png", "*.webp", "*.bmp" }, Path::GetFullQualifiedPathName("."), "Open image", runtime->window.handle))
		{
			runtime->imageLoaded = true;
			runtime->image = Image::LoadFromFile(selected.Value()).ConvertPixelFormat(PixelFormat::B8G8R8A8);
		}
		else
		{
			runtime->imageLoaded = false;
		}
}

Void OnRender(Void* RenderTarget)
{
	if (!runtime->imageLoaded)
		return;

	Int32 width = runtime->window.width;
	Int32 height = runtime->window.height;

	// frame begin
	{
		UInt32 clearColor = ToB8G8R8A8(Color::Black);

		for (SizeType y = 0; y < height; y++)
			for (SizeType x = 0; x < width; x++)
				reinterpret_cast<UInt32*>(RenderTarget)[width * y + x] = clearColor;
	}

	// render
	{

		Int32 imageWidth = runtime->image.width;
		Int32 imageHeight = runtime->image.height;

		{
			RealType imageScaleX = static_cast<RealType>(width) / imageWidth;
			RealType imageScaleY = static_cast<RealType>(height) / imageHeight;

			runtime->imageRequiredScale = Minimum(imageScaleX, imageScaleY);

			runtime->inputSystem.mouse.wheelValue = Clamp<Int32>(runtime->inputSystem.mouse.wheelValue, 0, NumericLimit<Int32>::Maximum);

			runtime->imageCurrentScale = runtime->imageRequiredScale + runtime->inputSystem.mouse.wheelValue * Runtime::MouseWheelSense;
			runtime->imageCurrentScale = Clamp(runtime->imageCurrentScale, runtime->imageRequiredScale, Runtime::MaximumScale);
		}

		Int32 imageRealWidth = imageWidth * runtime->imageCurrentScale;
		Int32 imageRealHeight = imageHeight * runtime->imageCurrentScale;

		Int32 xBegin = (width - imageRealWidth) / 2;
		Int32 xEnd = xBegin + imageRealWidth;
		Int32 yBegin = (height - imageRealHeight) / 2;
		Int32 yEnd = yBegin + imageRealHeight;

		if (imageRealWidth > width)
		{
			runtime->imageOffset.x = Clamp<Int32>(runtime->imageOffset.x, xBegin, -xBegin);

			xBegin += runtime->imageOffset.x;
			xEnd += runtime->imageOffset.x;
		}
		else
			runtime->imageOffset.x = 0;

		if (imageRealHeight > height)
		{
			runtime->imageOffset.y = Clamp<Int32>(runtime->imageOffset.y, yBegin, -yBegin);

			yBegin += runtime->imageOffset.y;
			yEnd += runtime->imageOffset.y;
		}
		else
			runtime->imageOffset.y = 0;

		Int32 xMin = Maximum(xBegin, 0);
		Int32 xMax = Minimum(xEnd, width);
		Int32 yMin = Maximum(yBegin, 0);
		Int32 yMax = Minimum(yEnd, height);

		for(SizeType y = yMin; y < yMax; y++)
			for (SizeType x = xMin; x < xMax; x++)
			{
				RealType u = static_cast<RealType>(x - xBegin) / (imageRealWidth - 1);
				RealType v = static_cast<RealType>(y - yBegin) / (imageRealHeight - 1);

				reinterpret_cast<UInt32*>(RenderTarget)[width * y + x] = 
					runtime->image.GetPixel
					(
						(imageWidth - 1) * u,
						(imageHeight - 1) * v
					);
			}

	}
}
