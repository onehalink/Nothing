#include "ScrollView.h"



namespace Engine::IMUI
{
	ScrollView::ScrollView(const Vector2Int& position, const Vector2Int& size, const Vector2Int& contentSize, Alignment contentAlignment)
	{
		rectangle = { position, position + size };
		background = Color_ScrollViewBackground;
		border = Color_Border;

		content.alignment = contentAlignment;
		content.serface = Serface(contentSize.x, contentSize.y);
		scrollBarSize = ScrollViewDefaultScrollBarSize;

		active = true;
		visible = true;

		{
			isDirty = true;
		}
	}

	Void ScrollView::Update(const EventSystem& eventSystem)
	{
		if (!active)
			return;

		if (isDirty)
		{
			isDirty = false;

			UpdateInternal();
		}

		horizontal.Update(eventSystem);
		vertical.Update(eventSystem);

		content.position =
		{
			Lerp<RealType>(content.origin.x, content.origin.x + contentAndViewportOffset.x, horizontal.value),
			Lerp<RealType>(content.origin.y, content.origin.y + contentAndViewportOffset.y, vertical.value),
		};
	}

	Void ScrollView::Render(IDrawable* interface)
	{
		if (!visible)
			return;

		//DrawRectangleFilled(
		//	interface,
		//	rectangle.minimum + Vector2Int::One,
		//	rectangle.maximum - Vector2Int::One,
		//	background
		//);
		//DrawRectangle(
		//	interface,
		//	rectangle.minimum,
		//	rectangle.maximum,
		//	background
		//);

		horizontal.Render(interface);
		vertical.Render(interface);

		{
			Vector2Int offset = viewport.minimum - content.position;
			Vector2Int viewportSize = viewport.Size();

			SizeType yEnd = Minimum(viewportSize.y, content.serface.height);
			SizeType xEnd = Minimum(viewportSize.x, content.serface.width);
			for(SizeType y = 0; y < yEnd; y++)
				for (SizeType x = 0; x < xEnd; x++)
				{
					const Color& pixel = content.serface.GetPixel(x + offset.x, y + offset.y);

					interface->SetPixel(viewport.minimum.x + x, viewport.minimum.y + y, pixel);
				}
		}
	}

	Void ScrollView::SetPosition(const Vector2Int& position)
	{
		isDirty = true;

		rectangle.SetPosition(position);
	}

	Void ScrollView::SetSize(const Vector2Int& size)
	{
		isDirty = true;

		rectangle.SetSize(size);
	}

	Void ScrollView::SetContentSize(const Vector2Int& contentSize)
	{
		isDirty = true;

		content.serface = { static_cast<SizeType>(contentSize.x), static_cast<SizeType>(contentSize.y) };
	}

	Void ScrollView::SetScrollBarSize(Int32 scrollBarSize)
	{
		isDirty = true;

		this->scrollBarSize = scrollBarSize;
	}

	Void ScrollView::UpdateInternal()
	{
		Vector2Int size = rectangle.Size();

		viewport.minimum = rectangle.minimum + Vector2Int::Top * scrollBarSize;
		viewport.maximum = rectangle.maximum + Vector2Int::Left * scrollBarSize;

		Vector2Int viewportSize = viewport.Size();

		horizontal =
		{
			rectangle.minimum,
			Vector2Int(viewportSize.x, scrollBarSize),
			Direction::LeftToRight,
			nullptr
		};
		horizontal.grab.renderSize = static_cast<RealType>(viewportSize.x) / content.serface.width;

		vertical =
		{
			rectangle.minimum + Vector2Int(viewportSize.x, scrollBarSize),
			Vector2Int(scrollBarSize, viewportSize.y),
			Direction::TopToBottom,
			nullptr
		};
		vertical.grab.renderSize = static_cast<RealType>(viewportSize.y) / content.serface.height;

		{
			Vector2Int offset = Vector2Int(content.serface.width, content.serface.height) - viewportSize;

			Vector2Int moveDirection = Vector2Int::Zero;
			switch (content.alignment)
			{
			case Alignment::LeftBottom:
				content.origin = viewport.minimum;
				moveDirection = Vector2Int::LeftBottom;
				break;
			case Alignment::LeftTop:
				content.origin = viewport.minimum + Vector2Int::Bottom * offset.y;
				moveDirection = Vector2Int::LeftTop;
				break;
			case Alignment::RightBottom:
				content.origin = viewport.minimum + Vector2Int::Left * offset.x;
				moveDirection = Vector2Int::RightBottom;
				break;
			case Alignment::RightTop:
				content.origin = viewport.minimum + Vector2Int::LeftBottom * offset;
				moveDirection = Vector2Int::LeftBottom;
				break;
			}

			contentAndViewportOffset = offset * moveDirection;
		}
	}
}
