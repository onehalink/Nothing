#include "Padding.h"



namespace Engine::UI
{
	Padding::Padding()
	{
		MemoryClear(this);
	}

	Padding::Padding(Int32 scalar)
	{
		left = bottom = right = top = scalar;
	}

	Padding::Padding(Int32 horizontal, Int32 vertical)
	{
		left = right = horizontal;
		bottom = top = vertical;
	}

	Padding::Padding(Int32 left, Int32 bottom, Int32 right, Int32 top)
		: left(left), bottom(bottom), right(right), top(top)
	{

	}

	Padding::Padding(const Vector2Int& leftBottom, const Vector2Int& rightTop)
		: leftBottom(leftBottom), rightTop(rightTop)
	{

	}

	Padding::Padding(const Padding& other)
	{
		MemoryCopy(this, &other);
	}

	Padding& Padding::operator=(const Padding& other)
	{
		MemoryCopy(this, &other);

		return *this;
	}
}