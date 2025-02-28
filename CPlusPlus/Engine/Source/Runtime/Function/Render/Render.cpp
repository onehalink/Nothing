#include "Render.h"



namespace Engine::Render
{
	static Void DrawLine(IRenderable* interface, Int32 x0, Int32 y0, Int32 x1, Int32 y1, const Color& color)
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


	Void Segment(IRenderable* interface, Vector2Int a, Vector2Int b, Color color)
	{
		RectangleInt limit = interface->GetScissorRectangle();

		Int32 x0, y0, x1, y1;
		if ( LiangBarskyLineClipping( &x0, &y0, &x1, &y1, a.x, a.y, b.x, b.y, limit.left, limit.right - 1, limit.bottom, limit.top - 1 ) )
			DrawLine( interface, x0, y0, x1, y1, color );
	}

	Void Triangle(IRenderable* interface, Vector2Int a, Vector2Int b, Vector2Int c, Color color)
	{
		Polygon(interface, color, a, b, c);
	}

	Void Rectangle(IRenderable* interface, Vector2Int minimum, Vector2Int maximum, Color color)
	{
		Polygon(interface, color,
			minimum,														// a
			minimum + Vector2Int::Right	* ( maximum.x - minimum.x - 1 ),	// b
			maximum - Vector2Int::One,										// c
			minimum + Vector2Int::Top	* ( maximum.y - minimum.y - 1 )		// d
		);
	}

	Void CircleFast(IRenderable* interface, Vector2Int center, Int32 radius, Color color, SizeType iteration)
	{
		auto Fn = [&](RealType radian)
			{
				return Vector2Int{
					center.x + radius * Cosine(radian),
					center.y + radius * Sine(radian),
				};
			};


		RealType unitRadian = Pi<RealType> * 2 / iteration;

		Vector2Int first;
		Vector2Int from = first = Fn( unitRadian * 0 );

		for (SizeType index = 1; index < iteration; index++)
		{
			Vector2Int to = Fn(unitRadian * index);

			Segment(interface, from, to, color);

			from = to;
		}

		Segment(interface, from, first, color);
	}

	Void SolidTriangle(IRenderable* interface, Vector2Int a, Vector2Int b, Vector2Int c, Color color)
	{
		auto BarycentricCoordinates = [](const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& point)
			{
				RealType areaA = Cross( c - b, point - b );
				RealType areaB = Cross( a - c, point - c );
				RealType areaC = Cross( b - a, point - a );

				RealType sum = areaA + areaB + areaC;

				RealType alpha	= areaA / sum;
				RealType beta	= areaB / sum;
				RealType gamma	= 1 - ( alpha + beta );

				return Vector3{ alpha, beta, gamma };
			};

		auto Contain = [](const Vector3& barycentricCoordinates)
			{
				return barycentricCoordinates.x >= 0 && barycentricCoordinates.y >= 0 && barycentricCoordinates.z >= 0;
			};


		RectangleInt aabb =
		{
			Minimum( a.x, b.x, c.x ),
			Minimum( a.y, b.y, c.y ),
			Maximum( a.x, b.x, c.x ) + 1, // right and top are excluded
			Maximum( a.y, b.y, c.y ) + 1
		};

		if ( auto limit = interface->GetScissorRectangle().Overlap(aabb) )
		{
			for (SizeType y = limit.minimum.y; y < limit.maximum.y; y++)
				for (SizeType x = limit.minimum.x; x < limit.maximum.x; x++)
					if ( Contain( BarycentricCoordinates( a, b, c, { x, y } ) ) )
						interface->SetPixel(x, y, color);
		}
	}

	Void SolidRectangle(IRenderable* interface, Vector2Int minimum, Vector2Int maximum, Color color)
	{
		if ( auto limit = interface->GetScissorRectangle().Overlap( { minimum, maximum } ) )
		{
			for (Int32 y = limit.minimum.y; y < limit.maximum.y; y++)
				for (Int32 x = limit.minimum.x; x < limit.maximum.x; x++)
					interface->SetPixel(x, y, color);
		}
	}

	Void SolidCircle(IRenderable* interface, Vector2Int center, Int32 radius, Color color)
	{
		Vector2Int offset	= { radius, radius };
		Vector2Int minimum	= center - offset;
		Vector2Int maximum	= center + offset;

		if ( auto limit = interface->GetScissorRectangle().Overlap( { minimum, maximum } ) )
		{
			Int32 r2 = Square(radius);
			for (SizeType y = limit.minimum.y; y < limit.maximum.y; y++)
				for (SizeType x = limit.minimum.x; x < limit.maximum.x; x++)
					if ( Square( x - center.x ) + Square( y - center.y ) <= r2 )
						interface->SetPixel(x, y, color);
		}
	}
}
