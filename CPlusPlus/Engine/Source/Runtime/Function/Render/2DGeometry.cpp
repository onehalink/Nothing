#include "2DGeometry.h"



namespace Engine
{
	static Void DrawLine(IDrawable* interface, Int32 x0, Int32 y0, Int32 x1, Int32 y1, const Color& color)
	{
		Int32 distanceX = Absolute( x0 - x1 );
		Int32 distanceY = Absolute( y0 - y1 );

		if ( distanceX == 0 && distanceY == 0 )
			interface->SetPixel(x0, y0, color);
		else if ( distanceX > distanceY )
		{
			if ( x0 > x1 ) // right to left
			{
				Swap( &x0, &x1 );
				Swap( &y0, &y1 );
			}

			for (Int32 x = x0; x <= x1; x++)
			{
				RealType amount	= static_cast<RealType>( x - x0 ) / distanceX;
				Int32 y			= Lerp(y0, y1, amount);

				interface->SetPixel(x, y, color);
			}
		}
		else // distanceY >= distanceX
		{
			if ( y0 > y1 ) // top to bottom
			{
				Swap( &y0, &y1 );
				Swap( &x0, &x1 );
			}

			for (Int32 y = y0; y <= y1; y++)
			{
				RealType amount	= static_cast<RealType>( y - y0 ) / distanceY;
				Int32 x			= Lerp(x0, x1, amount);

				interface->SetPixel(x, y, color);
			}
		}
	}

	/**
	* Reference from https://www.skytopia.com/project/articles/compsci/clipping.html
	*
	* @remark
	* return true if a line clipped, or it dont need to draw
	*/
	static Bool LiangBarskyLineClipping(Int32* outputX0, Int32* outputY0, Int32* outputX1, Int32* outputY1, Int32 x0, Int32 y0, Int32 x1, Int32 y1, Int32 left, Int32 right, Int32 bottom, Int32 top)
	{
		RealType t0 = 0;
		RealType t1 = 1;

		RealType xDelta = x1 - x0;
		RealType yDelta = y1 - y0;

		RealType p;
		RealType q;
		RealType r;

		for (SizeType iteration = 0; iteration < 4; iteration++)
		{
			if ( iteration == 0 )
			{
				p = -xDelta;
				q = -( left - x0 );
			}
			else if ( iteration == 1 )
			{
				p = xDelta;
				q = right - x0;
			}
			else if ( iteration == 2 )
			{
				p = -yDelta;
				q = -( bottom - y0 );
			}
			else if ( iteration == 3 )
			{
				p = yDelta;
				q = top - y0;
			}

			if ( Approximate(p, 0) && q < 0 )
				return false;

			r = q / p;

			if ( p < 0 )
			{
				if ( r > t1 )
					return false;
				else if ( r > t0 )
					t0 = r;
			}
			else if ( p > 0 )
			{
				if ( r < t0 )
					return false;
				else if ( r < t1 )
					t1 = r;
			}
		}

		*outputX0 = x0 + xDelta * t0;
		*outputY0 = y0 + yDelta * t0;
		*outputX1 = x0 + xDelta * t1;
		*outputY1 = y0 + yDelta * t1;

		return true;
	}


	Void DrawSegment(IDrawable* interface, const Vector2Int& a, const Vector2Int& b, const Color& color)
	{
		RectangleInt safeArea = interface->SafeArea();

		Int32 x0, y0, x1, y1;
		if ( LiangBarskyLineClipping( &x0, &y0, &x1, &y1, a.x, a.y, b.x, b.y, safeArea.left, safeArea.right - 1, safeArea.bottom, safeArea.top - 1 ) )
			DrawLine( interface, x0, y0, x1, y1, color );
	}

	Void DrawTriangle(IDrawable* interface, const Vector2Int& a, const Vector2Int& b, const Vector2Int& c, const Color& color)
	{
		DrawPolygon(interface, color, a, b, c);
	}

	Void DrawRectangle(IDrawable* interface, const Vector2Int& minimum, const Vector2Int& maximum, const Color& color)
	{
		DrawPolygon(interface, color,
			minimum,														// a
			minimum + Vector2Int::Right	* ( maximum.x - minimum.x - 1 ),	// b
			maximum - Vector2Int::One,										// c
			minimum + Vector2Int::Top	* ( maximum.y - minimum.y - 1 )		// d
		);
	}

	Void DrawRectangle(IDrawable* interface, const RectangleInt& rectangle, const Color& color)
	{
		DrawRectangle(interface, rectangle.minimum, rectangle.maximum, color);
	}

	Void DrawCircleFast(IDrawable* interface, const Vector2Int& position, RealType radius, const Color& color, SizeType iteration)
	{
		auto Fn = [&](RealType radian)
			{
				return Vector2Int{
					position.x + radius * Cosine(radian),
					position.y + radius * Sine(radian),
				};
			};


		RealType unitRadian = Pi<RealType> * 2 / iteration;

		Vector2Int first;
		Vector2Int from = first = Fn( unitRadian * 0 );

		for (SizeType index = 1; index < iteration; index++)
		{
			Vector2Int to = Fn( unitRadian * index );

			DrawSegment(interface, from, to, color);

			from = to;
		}

		DrawSegment(interface, from, first, color);
	}

	Void DrawTriangleFilled(IDrawable* interface, const Vector2Int& a, const Vector2Int& b, const Vector2Int& c, const Color& color)
	{
		RectangleInt safeArea = interface->SafeArea();

		Triangle triangle = { a, b, c };

		RectangleInt aabb = triangle.CalculateAABB();
		aabb.minimum = Clamp( aabb.minimum, safeArea.minimum, safeArea.maximum );
		aabb.maximum = Clamp( aabb.maximum, safeArea.minimum, safeArea.maximum );

		for (SizeType y = aabb.bottom; y < aabb.top; y++)
			for (SizeType x = aabb.left; x < aabb.right; x++)
				if ( triangle.IsInside( Vector2(x, y) ) )
					interface->SetPixel(x, y, color);
	}

	Void DrawRectangleFilled(IDrawable* interface, const Vector2Int& minimum, const Vector2Int& maximum, const Color& color)
	{
		RectangleInt safeArea = interface->SafeArea();

		Vector2Int limitMinimum = Clamp( minimum, safeArea.minimum, safeArea.maximum );
		Vector2Int limitMaximum = Clamp( maximum, safeArea.minimum, safeArea.maximum );

		for (Int32 y = limitMinimum[1]; y < limitMaximum[1]; y++)
			for (Int32 x = limitMinimum[0]; x < limitMaximum[0]; x++)
				interface->SetPixel(x, y, color);
	}

	Void DrawRectangleFilled(IDrawable* interface, const RectangleInt& rectangle, const Color& color)
	{
		DrawRectangleFilled(interface, rectangle.minimum, rectangle.maximum, color);
	}
	
	Void DrawCircleFilled(IDrawable* interface, const Vector2Int& position, RealType radius, const Color& color)
	{
		RectangleInt safeArea = interface->SafeArea();

		RealType sin45		= Sine( Pi<RealType> / 2 );
		RealType cosine45	= sin45;

		Vector2Int minimum = position - Vector2Int( radius * cosine45, radius * sin45 );
		Vector2Int maximum = position + Vector2Int( radius * cosine45, radius * sin45 );

		minimum = Clamp(minimum, safeArea.minimum, safeArea.maximum);
		maximum = Clamp(maximum, safeArea.minimum, safeArea.maximum);

		Int32 r2 = Square(radius);
		for (SizeType y = minimum.y; y < maximum.y; y++)
			for (SizeType x = minimum.x; x < maximum.x; x++)
				if ( Square( x - position.x ) + Square( y - position.y ) <= r2 )
					interface->SetPixel(x, y, color);
	}
}