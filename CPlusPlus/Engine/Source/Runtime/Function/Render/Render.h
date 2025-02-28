#pragma once

#include "../Interface/IRenderable.h"



namespace Engine::Render
{
	ENGINE_API Void Segment(IRenderable* interface, Vector2Int startPoint, Vector2Int endPoint, Color color);
	ENGINE_API Void Triangle(IRenderable* interface, Vector2Int a, Vector2Int b, Vector2Int c, Color color);
	ENGINE_API Void Rectangle(IRenderable* interface, Vector2Int minimum, Vector2Int maximum, Color color);
	ENGINE_API Void CircleFast(IRenderable* interface, Vector2Int center, Int32 radius, Color color, SizeType iteration = 16);
	template<typename ...Points> Void Path(IRenderable* interface, Color color, Vector2Int a, Vector2Int b, Points... points);
	template<typename ...Points> Void Polygon(IRenderable* interface, Color color, Vector2Int a, Vector2Int b, Points... points);

	ENGINE_API Void SolidTriangle(IRenderable* interface, Vector2Int pointA, Vector2Int pointB, Vector2Int pointC, Color color);
	ENGINE_API Void SolidRectangle(IRenderable* interface, Vector2Int minimum, Vector2Int maximum, Color color);
	ENGINE_API Void SolidCircle(IRenderable* interface, Vector2Int center, Int32 radius, Color color);


	Void Rectangle(IRenderable* interface, const RectangleInt& rectangle, Color color);
	Void SolidRectangle(IRenderable* interface, const RectangleInt& rectangle, Color color);


#pragma region Details

	template<typename ...Points>
	Void Path(IRenderable* interface, Color color, Vector2Int a, Vector2Int b, Points... points)
	{
		static_assert( And<IsConvertible<Points, Vector2Int> ...>::Value );


		Segment(interface, a, b, color);

		if constexpr ( sizeof...(points) > 0 )
			Path( interface, color, b, points... );
	}

	template<typename ...Points>
	Void Polygon(IRenderable* interface, Color color, Vector2Int a, Vector2Int b, Points... points)
	{
		static_assert( And<IsConvertible<Points, Vector2Int> ...>::Value );
		static_assert( sizeof...(points) > 0 );

	
		const auto& last = ParameterPack::NthElement<sizeof...(points) - 1>( Forward<Points>(points)... );
		Segment(interface, a, last, color);

		Path( interface, color, a, b, points... );
	}

	inline Void Rectangle(IRenderable* interface, const RectangleInt& rectangle, Color color)
	{
		return Rectangle( interface, rectangle.minimum, rectangle.maximum, color );
	}

	inline Void SolidRectangle(IRenderable* interface, const RectangleInt& rectangle, Color color)
	{
		return SolidRectangle( interface, rectangle.minimum, rectangle.maximum, color );
	}

#pragma endregion
}