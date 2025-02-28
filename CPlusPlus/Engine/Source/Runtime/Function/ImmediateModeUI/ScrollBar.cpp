#include "ScrollBar.h"



namespace Engine::UI
{
	ScrollBar::ScrollBar()
	{
		
	}

	ScrollBar::ScrollBar(const Vector2& position, const Vector2& size, Direction direction, Action<RealType> OnValueChange)
	{
		this->OnValueChange = OnValueChange;

		rectangle	= { position, position + size };
		background	= Color_ScrollBarBackground;
		border		= Color_Border;

		state	= { true, true };
		isDirty	= true;
		value	= 0;

		this->direction = direction;

		grab.visual		= { Color_ScrollBarGrabNormal, Color_ScrollBarGrabHover, Color_ScrollBarGrabActive };
		grab.isHolded	= false;
		grab.renderSize	= 0.2;
	}

	Void ScrollBar::Update(const EventSystem& eventSystem)
	{
		if ( !state.active )
			return;

		if (isDirty)
		{
			isDirty = false;

			UpdateInternal();
		}

		auto& mouse	= eventSystem.mousePosition;
		Bool hover	= IsInside( { grab.position, grab.position + grab.size }, mouse );
		Bool press	= eventSystem.MouseButtonPressed(MouseButton::Left);

		if ( hover && press && !grab.isHolded )
		{
			grab.isHolded = true;

			grab.lastPosition	= grab.position;
			grab.beginDrag		= mouse;

			lastValue = value;
		}

		auto& visual = grab.visual;

		if (hover)
			visual.color = visual.hover;

		if ( press && grab.isHolded )
		{
			{
				Vector2Int offset = mouse - grab.beginDrag;

				grab.position			= grab.lastPosition;
				grab.position[index]	+= offset[index];

				grab.position = Clamp(grab.position, grab.minimum, grab.maximum);
			}

			{
				Int32 distance = grab.position[index] - rectangle.minimum[index];

				RealType temporary = distance / ( rectangle.Size()[index] * ( 1 - grab.renderSize ) );
				if ( !reverseValue )
					value = temporary;
				else
					value = 1 - temporary;
			}

			visual.color = visual.active;
		}
		else
		{
			if ( grab.isHolded )
			{
				grab.isHolded = false;

				if ( !Approximate(value, lastValue) )
					if (OnValueChange) OnValueChange(value);
			}

			if (hover)
				visual.color = visual.hover;
			else
				visual.color = visual.normal;
		}
	}

	Void ScrollBar::Render(IDrawable* interface)
	{
		if ( !state.visible )
			return;

		if ( NoEnoughDisplaySpace( interface->SafeArea(), rectangle ) )
			return;

		DrawRectangleFilled(
			interface,
			rectangle.minimum,
			rectangle.maximum,
			background
		);
		DrawRectangle(
			interface,
			rectangle.minimum,
			rectangle.maximum,
			border
		);

		Vector2Int minimum	= grab.position;
		Vector2Int maximum	= minimum + grab.size;
		DrawRectangleFilled(
			interface,
			minimum,
			maximum,
			grab.visual.color
		);
		DrawRectangle(
			interface,
			minimum,
			maximum,
			border
		);
	}

	Void ScrollBar::SetPosition(const Vector2Int& position)
	{
		isDirty = true;

		Vector2Int size		= rectangle.Size();
		rectangle.minimum	= position;
		rectangle.maximum	= position + size;
	}

	Void ScrollBar::SetSize(const Vector2Int& size)
	{
		isDirty = true;

		rectangle.maximum = rectangle.minimum + size;
	}

	Void ScrollBar::SetDirection(Direction direction)
	{
		isDirty = true;

		this->direction = direction;
	}

	Void ScrollBar::SetGrabRenderSize(RealType renderSize)
	{
		isDirty = true;

		grab.renderSize = renderSize;
	}

	Void ScrollBar::UpdateInternal()
	{
		axis	= AxisFromDirection(direction);
		index	= static_cast<SizeType>(axis);

		reverseValue = 
			direction == Direction::RightToLeft || direction == Direction::TopToBottom ?
			true : false;

		RealType total	= 1 - grab.renderSize;
		Vector2Int size	= rectangle.Size();
		{
			RealType movement = total * value;

			grab.position = rectangle.minimum;
			if (reverseValue)
				grab.position[index] += size[index] * (total - movement);
			else
				grab.position[index] += size[index] * movement;
		}

		{
			grab.size = size;
			grab.size[index] *= grab.renderSize;
		}

		{
			grab.minimum = rectangle.minimum;

			grab.maximum		= size;
			grab.maximum[index] *= total;
			grab.maximum		+= grab.minimum;
		}
	}
}