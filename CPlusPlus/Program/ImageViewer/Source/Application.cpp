#include "Application.h"



static Runtime* runtime;


Void OnAppInit(Void* userParameter)
{
	//Debug::Trace("\n[Tips]\nMouseWheel: zoom in/out\nMoving mouse to drag image when left mouse button is pressed\nClick Key [O] to load other image");

	runtime = reinterpret_cast<Runtime*>(userParameter);

	runtime->eventSystem.AddKeyTypedEvent(Key::O, KeyState::Click);
}

Void OnAppResize(SizeType width, SizeType height)
{

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
	if (runtime->eventSystem.KeyClicked(Key::Escape))
		runtime->wantToQuit = true;

	runtime->window.SetTitle(Format(U8String("{Title}(Scale: {}%)"), runtime->windowTitle, static_cast<Int32>(runtime->imageCurrentScale * 100)));

	if (runtime->eventSystem.MouseButtonPressed(MouseButton::Left))
	{
		if (!runtime->isHold)
		{
			runtime->isHold = true;

			runtime->imageLastOffset = runtime->imageOffset;
			runtime->beginDragPoint = runtime->eventSystem.mousePosition;
		}

		runtime->imageOffset = runtime->imageLastOffset + (runtime->eventSystem.mousePosition - runtime->beginDragPoint);
	}
	else
	{
		runtime->isHold = false;
	}

	if (runtime->eventSystem.KeyClicked(Key::O))
		if (auto selected = FileDialog::Open({ InPlace(), "*.jpg", "*.png", "*.webp", "*.bmp" }, Path::GetFullQualifiedPathName("."), "Open image", runtime->window.GetHandle()))
		{
			runtime->imageLoaded = true;
			runtime->image = Image::LoadFromFile(selected.Value()).ConvertToSpecificPixelFormat(PixelFormat::B8G8R8A8);
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

	Int32 width = runtime->window.GetWidth();
	Int32 height = runtime->window.GetHeight();

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

			runtime->eventSystem.mouseWheelValue = Clamp<Int32>(runtime->eventSystem.mouseWheelValue, 0, NumericLimit<Int32>::Maximum);

			runtime->imageCurrentScale = runtime->imageRequiredScale + runtime->eventSystem.mouseWheelValue * Runtime::MouseWheelSense;
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
