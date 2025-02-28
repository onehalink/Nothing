#include "2DGeometry.h"



namespace Engine
{
	static Void DrawSegment(IDrawable* interface, Int32 x0, Int32 y0, Int32 x1, Int32 y1, const Color& color)
	{
		Int32 distanceX = Absolute( x0 - x1 );
		Int32 distanceY = Absolute( y0 - y1 );

		if ( distanceX == 0 && distanceY == 0 )
			interface->SetPixel(x0, y0, color);
		else if ( distanceX > distanceY )
		{
			if ( x0 > x1 )
			{
				Swap( &x0, &x1 );
				Swap( &y0, &y1 );
			}

			for (Int32 x = x0; x <= x1; x++)
			{
				RealType amount	= static_cast<RealType>( x - x0 ) / distanceX;
				Int32 y			= Lerp<RealType>(y0, y1, amount);

				interface->SetPixel(x, y, color);
			}
		}
		else
		{
			if ( y0 > y1 )
			{
				Swap( &y0, &y1 );
				Swap( &x0, &x1 );
			}

			for (Int32 y = y0; y <= y1; y++)
			{
				RealType amount	= static_cast<RealType>( y - y0 ) / distanceY;
				Int32 x			= Lerp<RealType>(x0, x1, amount);

				interface->SetPixel(x, y, color);
			}
		}
	}


	Void DrawSegment(IDrawable* interface, const Vector2Int& a, const Vector2Int& b, const Color& color)
	{
		DrawSegment( interface, a.x, a.y, b.x, b.y, color );
	}

	Void DrawPath(IDrawable* interface, const Vector2Int* points, SizeType pointCount, const Color& color)
	{
		for (SizeType index = 1; index < pointCount; index++)
		{
			const Vector2Int& from	= points[ index - 1 ];
			const Vector2Int& to	= points[index];

			DrawSegment(interface, from, to, color);
		}
	}

	Void DrawTriangle(IDrawable* interface, const Vector2Int& a, const Vector2Int& b, const Vector2Int& c, const Color& color)
	{
		DrawSegment(interface, a, b, color);
		DrawSegment(interface, b, c, color);
		DrawSegment(interface, a, c, color);
	}

	Void DrawRectangle(IDrawable* interface, const Vector2Int& minimum, const Vector2Int& maximum, const Color& color)
	{
		Vector2Int offset = maximum - minimum - Vector2Int::One;

		Vector2Int a = minimum;
		Vector2Int b = a + Vector2Int::Right	* offset.x;
		Vector2Int c = b + Vector2Int::Top		* offset.y;
		Vector2Int d = a + Vector2Int::Top		* offset.y;

		DrawSegment(interface, a, b, color);
		DrawSegment(interface, b, c, color);
		DrawSegment(interface, c, d, color);
		DrawSegment(interface, a, d, color);
	}

	Void DrawCircleFast(IDrawable* interface, const Vector2Int& position, RealType radius, const Color& color, SizeType iteration)
	{
		RealType unitRadian = TwoPi<RealType> / iteration;

		Memory<Vector2Int> span( iteration + 1 );
		for (SizeType index = 0; index < iteration; index++)
		{
			RealType radian = unitRadian * index;

			RealType x = position.x + radius * Cosine(radian);
			RealType y = position.y + radius * Sine(radian);

			span[index] = { x, y };
		}

		span[iteration] = span[0];
		DrawPath( interface, span.GetBuffer(), span.GetCount(), color );
	}

	Void DrawTriangleFilled(IDrawable* interface, const Vector2Int& a, const Vector2Int& b, const Vector2Int& c, const Color& color)
	{
		RectangleInt aabb = CalculateAABB(a, b, c);
		for (SizeType y = aabb.bottom; y < aabb.top; y++)
			for (SizeType x = aabb.left; x < aabb.right; x++)
				if ( IsInside( BarycentricCoordinates( a, b, c, Vector2Int(x, y) ) ) )
					interface->SetPixel(x, y, color);
	}

	Void DrawRectangleFilled(IDrawable* interface, const Vector2Int& minimum, const Vector2Int& maximum, const Color& color)
	{
		for (Int32 y = minimum[1]; y < maximum[1]; y++)
			for (Int32 x = minimum[0]; x < maximum[0]; x++)
				interface->SetPixel(x, y, color);
	}
	
	Void DrawCircleFilled(IDrawable* interface, const Vector2Int& position, RealType radius, const Color& color)
	{
		RealType sin45		= Sine( HalfPi<RealType> );
		RealType cosine45	= sin45;

		Vector2Int minimum = position - Vector2Int( radius * cosine45, radius * sin45 );
		Vector2Int maximum = position + Vector2Int( radius * cosine45, radius * sin45 );

		Int32 r2 = Square(radius);
		for (SizeType y = minimum.y; y < maximum.y; y++)
			for (SizeType x = minimum.x; x < maximum.x; x++)
				if ( Square( x - position.x ) + Square( y - position.y ) <= r2 )
					interface->SetPixel(x, y, color);
	}
}