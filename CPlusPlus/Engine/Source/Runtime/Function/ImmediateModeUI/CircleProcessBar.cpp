#include "CircleProcessBar.h"



namespace Engine::IMUI
{
	CircleProcessBar::CircleProcessBar(const Vector2Int& position, Int32 outerRadius, Int32 innerRadius)
	{
		this->position = position;
		this->outerRadius = outerRadius;
		this->innerRadius = innerRadius;

		background = Color_ProcessBarBackground;
		foreground = Color_ProcessBarForeground;

		active = true;
		visible = true;

		value = 0;

		displayText = true;
		textColor = Color_Text;
	}

	Void CircleProcessBar::Update(const EventSystem& eventSystem)
	{
		if (!active)
			return;
	}

	Void CircleProcessBar::Render(IDrawable* interface)
	{
		if (!visible)
			return;

		value = Clamp01(value);

		Vector2Int minimum = position - Vector2Int::One * outerRadius;
		Vector2Int maximum = position + Vector2Int::One * outerRadius;

		Int32 or2 = Square(outerRadius);
		Int32 ir2 = Square(innerRadius);

		for(SizeType y = minimum.y; y < maximum.y; y++)
			for (SizeType x = minimum.x; x < maximum.x; x++)
			{
				Int32 temp = Square(x - position.x) + Square(y - position.y);
				if (
					(temp < or2) &&
					(temp > ir2)
					)
					interface->SetPixel(x, y, background);
			}

		constexpr RealType Unit = 1 / 0.25 * Pi / 2;
		// 0 - 0.25
		{
			RealType radian = Minimum(value, 0.25) * Unit;
			RealType k = Cosine(radian) / Sine(radian);

			RectangleInt aabb = { position, position + Vector2Int::One * outerRadius };
			for (Int32 y = aabb.minimum.y; y < aabb.maximum.y; y++)
				for (Int32 x = aabb.minimum.x; x < aabb.maximum.x; x++)
				{
					if (
						(Square(x - position.x) + Square(y - position.y) < or2) &&
						(Square(x - position.x) + Square(y - position.y) > ir2) &&
						(y - position.y > k * (x - position.x))
						)
						interface->SetPixel(x, y, foreground);
				}
		}

		// 0.25 - 0.5
		if(value > 0.25)
		{
			RealType radian = (Minimum(value, 0.50 - Epsilon) - 0.25) * Unit;
			RealType k = -Sine(radian) / Cosine(radian);

			RectangleInt aabb = { Vector2Int(position.x, position.y - outerRadius), Vector2Int(position.x + outerRadius, position.y) };
			for (Int32 y = aabb.minimum.y; y < aabb.maximum.y; y++)
				for (Int32 x = aabb.minimum.x; x < aabb.maximum.x; x++)
				{
					if (
						(Square(x - position.x) + Square(y - position.y) < or2) &&
						(Square(x - position.x) + Square(y - position.y) > ir2) &&
						(y - position.y > k * (x - position.x))
						)
						interface->SetPixel(x, y, foreground);
				}
		}

		// 0.5 - 0.75
		if (value > 0.5)
		{
			RealType radian = (Minimum(value, 0.75) - 0.50) * Unit;
			RealType k = Cosine(radian) / Sine(radian);

			RectangleInt aabb = { position - Vector2Int::One * outerRadius, position };
			for (Int32 y = aabb.minimum.y; y < aabb.maximum.y; y++)
				for (Int32 x = aabb.minimum.x; x < aabb.maximum.x; x++)
				{
					if (
						(Square(x - position.x) + Square(y - position.y) < or2) &&
						(Square(x - position.x) + Square(y - position.y) > ir2) &&
						(y - position.y < k * (x - position.x))
						)
						interface->SetPixel(x, y, foreground);
				}
		}

		// 0.75 - 1
		if(value > 0.75)
		{
			RealType radian = (Minimum(value, 1 - Epsilon) - 0.75) * Unit;
			RealType k = Sine(radian) / -Cosine(radian);

			RectangleInt aabb = { position + Vector2Int::Left * outerRadius, position + Vector2Int::Top * outerRadius };
			for (Int32 y = aabb.minimum.y; y < aabb.maximum.y; y++)
				for (Int32 x = aabb.minimum.x; x < aabb.maximum.x; x++)
				{
					if (
						(Square(x - position.x) + Square(y - position.y) < or2) &&
						(Square(x - position.x) + Square(y - position.y) > ir2) &&
						(y - position.y < k * (x - position.x))
						)
						interface->SetPixel(x, y, foreground);
				}
		}

		// artifact fix
		if (value >= 0.5)
			DrawSegment(interface, position + Vector2Int::Bottom * innerRadius, position + Vector2Int::Bottom * outerRadius, foreground);

		if(displayText)
		{
			U8String text = Format("{}%", static_cast<Int32>(value * 100));
			Vector2Int size = DefaultFontSizeInPixel * Vector2Int(text.GetCount(), 1);

			Text(interface, Private::CalculateRectangleAlignment(Alignment::Center, { position - Vector2Int::One * outerRadius, position + Vector2Int::One * outerRadius }, size), text, textColor);
		}
	}
}