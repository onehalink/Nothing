#include "ScrollView.h"



namespace Engine::UI
{
	ScrollView::ScrollView()
	{
		InitInternal();
	}

	ScrollView::ScrollView(const Vector2Int& position, const Vector2Int& size, const Vector2Int& contentSize, Alignment contentAlignment)
	{
		InitInternal();

		rectangle = { position, position + size };

		content.serface = Serface(contentSize.x, contentSize.y);
		content.alignment = contentAlignment;
	}

	Void ScrollView::Update(const InputSystem& inputSystem)
	{
		if (!active)
			return;

		if (isDirty)
		{
			isDirty = false;

			UpdateInternal();
		}

		horizontalScrollBar.Update(inputSystem);
		verticalScrollBar.Update(inputSystem);

		content.position.x = Lerp(content.origin.x, contentTargetPosition.x, horizontalScrollBar.value);
		content.position.y = Lerp(content.origin.y, contentTargetPosition.y, verticalScrollBar.value);
	}

	Void ScrollView::Render(IDrawable* interface)
	{
		if (!visible)
			return;

		DrawRectangleFilled(interface, rectangle, background);
		DrawRectangle(interface, rectangle, border);

		horizontalScrollBar.Render(interface);
		verticalScrollBar.Render(interface);

		{
			auto safeArea = interface->SafeArea();

			Vector2Int contentMinimum = content.position;
			Vector2Int contentMaximum = contentMinimum + Vector2Int(content.serface.width, content.serface.height);

			auto limitMinimum = Clamp(viewport.minimum, safeArea.minimum, safeArea.maximum);
			auto limitMaximum = Clamp(viewport.maximum, safeArea.minimum, safeArea.maximum);
			auto offset = limitMinimum - content.position;
			for (SizeType index = 0; index < 2; index++)
			{
				limitMinimum[index] = Maximum(limitMinimum[index], contentMinimum[index]);
				limitMaximum[index] = Minimum(limitMaximum[index], contentMaximum[index]);
				offset[index] = Maximum(0, offset[index]);
			}

			auto limitSize = limitMaximum - limitMinimum;
			for(Int32 y = 0; y < limitSize.y; y++)
				for (Int32 x = 0; x < limitSize.x; x++)
				{
					auto& pixel = content.serface.GetPixel(x + offset.x, y + offset.y);

					interface->SetPixel(limitMinimum.x + x, limitMinimum.y + y, pixel);
				}
		}
	}

	Void ScrollView::InitInternal()
	{
		background = Color_ScrollViewBackground;
		border = Color_Border;

		{
			scrollBarSize = ScrollViewDefaultScrollBarSize;

			horizontalScrollBarLocation = VerticalLocation::Bottom;
			verticalScrollBarLocation = HorizontalLocation::Right;

			horizontalScrollBar.direction = Direction::LeftToRight;
			verticalScrollBar.direction = Direction::TopToBottom;
		}
		
		{
			active = true;
			visible = true;

			isDirty = true;
		}
	}

	Void ScrollView::AdjustViewport()
	{
		if (
			(horizontalScrollBarLocation == VerticalLocation::Bottom) &&
			(verticalScrollBarLocation == HorizontalLocation::Right)
			)
			viewport =
			{
				rectangle.minimum + Vector2Int::Top * scrollBarSize,
				rectangle.maximum + Vector2Int::Left * scrollBarSize,
			};

		if (
			(horizontalScrollBarLocation == VerticalLocation::Bottom) &&
			(verticalScrollBarLocation == HorizontalLocation::Left)
			)
			viewport =
			{
				rectangle.minimum + Vector2Int::One * scrollBarSize,
				rectangle.maximum,
			};

		if (
			(horizontalScrollBarLocation == VerticalLocation::Top) &&
			(verticalScrollBarLocation == HorizontalLocation::Right)
			)
			viewport =
			{
				rectangle.minimum,
				rectangle.maximum - Vector2Int::One * scrollBarSize,
			};

		if (
			(horizontalScrollBarLocation == VerticalLocation::Top) &&
			(verticalScrollBarLocation == HorizontalLocation::Left)
			)
			viewport =
			{
				rectangle.minimum + Vector2Int::Right * scrollBarSize,
				rectangle.maximum + Vector2Int::Bottom * scrollBarSize,
			};
	}

	Void ScrollView::AdjustScrollBar()
	{
		if (
			(horizontalScrollBarLocation == VerticalLocation::Bottom) &&
			(verticalScrollBarLocation == HorizontalLocation::Right)
			)
		{
			horizontalScrollBar.rectangle =
			{
				rectangle.minimum,
				rectangle.RightBottom() + Vector2Int(-scrollBarSize, scrollBarSize),
			};

			verticalScrollBar.rectangle =
			{
				horizontalScrollBar.rectangle.maximum,
				rectangle.maximum,
			};
		}

		if (
			(horizontalScrollBarLocation == VerticalLocation::Bottom) &&
			(verticalScrollBarLocation == HorizontalLocation::Left)
			)
		{
			horizontalScrollBar.rectangle =
			{
				rectangle.minimum + Vector2Int(scrollBarSize, 0),
				rectangle.RightBottom() + Vector2Int(0, scrollBarSize),
			};

			verticalScrollBar.rectangle =
			{
				rectangle.minimum + Vector2Int(0, scrollBarSize),
				rectangle.LeftTop() + Vector2Int(scrollBarSize, 0),
			};
		}

		if (
			(horizontalScrollBarLocation == VerticalLocation::Top) &&
			(verticalScrollBarLocation == HorizontalLocation::Right)
			)
		{
			horizontalScrollBar.rectangle =
			{
				rectangle.LeftTop() - Vector2Int(0, scrollBarSize),
				rectangle.maximum - Vector2Int(scrollBarSize, 0),
			};

			verticalScrollBar.rectangle =
			{
				rectangle.RightBottom() - Vector2Int(scrollBarSize, 0),
				rectangle.maximum - Vector2Int(0, scrollBarSize),
			};
		}

		if (
			(horizontalScrollBarLocation == VerticalLocation::Top) &&
			(verticalScrollBarLocation == HorizontalLocation::Left)
			)
		{
			horizontalScrollBar.rectangle =
			{
				rectangle.LeftTop() + Vector2Int(scrollBarSize, -scrollBarSize),
				rectangle.maximum,
			};

			verticalScrollBar.rectangle =
			{
				rectangle.minimum,
				horizontalScrollBar.rectangle.minimum,
			};
		}


		RealType ratioX = (RealType)viewport.Size().x / content.serface.width;
		RealType ratioY = (RealType)viewport.Size().y / content.serface.height;

		horizontalScrollBar.grab.renderSize = Minimum(1, ratioX);
		verticalScrollBar.grab.renderSize = Minimum(1, ratioY);

		horizontalScrollBar.isDirty = true;
		verticalScrollBar.isDirty = true;
	}

	Void ScrollView::AdjustContent()
	{
		Vector2Int contentSize = { content.serface.width, content.serface.height };

		Vector2Int sign = {
			content.alignment == Alignment::RightBottom || content.alignment == Alignment::RightTop ? -1 : 1,
			content.alignment == Alignment::LeftTop || content.alignment == Alignment::RightTop ? -1 : 1,
		};
		Vector2Int distance = (viewport.Size() - contentSize) * sign;

		content.origin = Private::CalculateRectangleAlignment(content.alignment, viewport, contentSize);
		contentTargetPosition = content.origin + distance;
	}

	Void ScrollView::UpdateInternal()
	{
		AdjustViewport();
		AdjustContent();

		AdjustScrollBar();
	}
}