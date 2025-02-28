#include "ScrollView.h"



namespace Engine::UI
{
	ScrollView::ScrollView(const Vector2Int& position, const Vector2Int& size)
	{
		rectangle	= { position, position + size };
		background	= Color_ScrollViewBackground;
		border		= Color_Border;

		scrollBarSize = 20;

		isDirty	= true;
		state	= { true, true };

		Vector2Int contentSize	= Vector2(size) * RealType(1.5);
		content.texture = Texture{ (SizeType)contentSize.x, (SizeType)contentSize.y };

		content.alignment = Alignment::LeftTop;
	}

	Void ScrollView::Update(const EventSystem& eventSystem)
	{
		if ( !state.active )
			return;

		if (isDirty)
		{
			isDirty = false;

			UpdateInternal();
		}

		horizontal.Update(eventSystem);
		vertical.Update(eventSystem);

		{
			Vector2Int contentSize = Vector2Int{ content.texture.width, content.texture.height };
			Vector2Int distance = contentSize - viewport.Size();

			Vector2Int moveDirection = Vector2Int::Zero;
			switch (content.alignment)
			{
			case Alignment::LeftBottom:
				content.origin = viewport.minimum;
				moveDirection = Vector2Int::LeftBottom;
				break;
			case Alignment::LeftTop:
				content.origin = viewport.minimum + Vector2Int::Bottom * distance.y;
				moveDirection = Vector2Int::LeftTop;
				break;
			case Alignment::RightBottom:
				content.origin = viewport.minimum + Vector2Int::Left * distance.x;
				moveDirection = Vector2Int::RightBottom;
				break;
			case Alignment::RightTop:
				content.origin = viewport.minimum + Vector2Int::LeftBottom * distance;
				moveDirection = Vector2Int::RightTop;
				break;
			}

			distance *= moveDirection;
			content.position =
			{
				Lerp( content.origin.x, content.origin.x + distance.x, horizontal.value	),
				Lerp( content.origin.y, content.origin.y + distance.y, vertical.value	),
			};
		}
	}

	Void ScrollView::Render(IDrawable* interface)
	{
		if ( !state.visible )
			return;

		if ( NoEnoughDisplaySpace( interface->SafeArea(), rectangle ) )
			return;

		horizontal.Render(interface);
		vertical.Render(interface);

		{
			Vector2Int offset		= viewport.minimum - content.position;
			Vector2Int viewportSize	= viewport.Size();

			SizeType yEnd = Minimum( viewportSize.y, content.texture.height );
			SizeType xEnd = Minimum( viewportSize.x, content.texture.width );
			for (SizeType y = 0; y < yEnd; y++)
				for (SizeType x = 0; x < xEnd; x++)
				{
					auto pixel = content.texture.GetPixel( x + offset.x, y + offset.y );

					interface->SetPixel( viewport.minimum.x + x, viewport.minimum.y + y, FromR8G8B8(pixel) );
				}
		}
	}

	Void ScrollView::SetPosition(const Vector2Int& position)
	{
		isDirty = true;

		Vector2Int size	= rectangle.Size();
		rectangle		= { position, position + size };
	}

	Void ScrollView::SetSize(const Vector2Int& size)
	{
		isDirty = true;

		rectangle.maximum = rectangle.minimum + size;
	}

	Void ScrollView::SetContentSize(const Vector2Int& contentSize)
	{
		isDirty = true;

		content.texture = Texture{ (SizeType)contentSize.x, (SizeType)contentSize.y };
	}

	Void ScrollView::SetScrollBarSize(Int32 scrollBarSize)
	{
		isDirty = true;

		this->scrollBarSize = scrollBarSize;
	}

	Void ScrollView::UpdateInternal()
	{
		Vector2Int size	= rectangle.Size();
		scrollBarSize	= Minimum(size.x, size.y, scrollBarSize);

		viewport.minimum = rectangle.minimum + Vector2Int::Top * scrollBarSize;
		viewport.maximum = rectangle.maximum + Vector2Int::Left * scrollBarSize;

		content.position = content.origin = viewport.minimum;

		Vector2Int viewportSize = viewport.Size();

		horizontal =
		{
			rectangle.minimum,
			{ viewportSize.x, scrollBarSize },
			Direction::LeftToRight,
			horizontal.OnValueChange
		};
		horizontal.grab.renderSize = static_cast<RealType>(viewportSize.x) / content.texture.width;

		vertical =
		{
			rectangle.minimum + Vector2Int{ viewportSize.x, scrollBarSize },
			{ scrollBarSize, viewportSize.y },
			Direction::TopToBottom,
			vertical.OnValueChange
		};
		vertical.grab.renderSize = static_cast<RealType>(viewportSize.y) / content.texture.height;
	}
}