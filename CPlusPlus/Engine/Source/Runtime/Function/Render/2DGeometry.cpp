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
				Int32 y			= Lerp(y0, y1, amount);

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
				Int32 x			= Lerp(x0, x1, amount);

				interface->SetPixel(x, y, color);
			}
		}
	}


	Void DrawSegment(IDrawable* interface, const Vector2Int& a, const Vector2Int& b, const Color& color)
	{

		DrawSegment( interface, a.x, a.y, b.x, b.y, color );
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

	Void DrawRectangleFilled(IDrawable* interface, const Vector2Int& minimum, const Vector2Int& maximum, const Color& color)
	{
		for (Int32 y = minimum[1]; y < maximum[1]; y++)
			for (Int32 x = minimum[0]; x < maximum[0]; x++)
				interface->SetPixel(x, y, color);
	}
}