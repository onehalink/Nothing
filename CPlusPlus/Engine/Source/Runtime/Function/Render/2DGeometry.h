#pragma once

#include "IDrawable.h"



namespace Engine
{
	ENGINE_API Void DrawSegment(IDrawable* interface, const Vector2Int& a, const Vector2Int& b, const Color& color);
	template<typename ...Parameters> Void DrawPath(IDrawable* interface, const Color& color, const Vector2Int& a, const Vector2Int& b, Parameters&&... parameters);

	ENGINE_API Void DrawTriangle(IDrawable* interface, const Vector2Int& a, const Vector2Int& b, const Vector2Int& c, const Color& color);
	ENGINE_API Void DrawRectangle(IDrawable* interface, const Vector2Int& minimum, const Vector2Int& maximum, const Color& color);
	ENGINE_API Void DrawRectangle(IDrawable* interface, const RectangleInt& rectangle, const Color& color);
	ENGINE_API Void DrawCircleFast(IDrawable* interface, const Vector2Int& position, RealType radius, const Color& color, SizeType iteration = 16);
	template<typename ...Parameters> Void DrawPolygon(IDrawable* interface, const Color& color, const Vector2Int& a, const Vector2Int& b, Parameters&&... parameters);

	ENGINE_API Void DrawTriangleFilled(IDrawable* interface, const Vector2Int& a, const Vector2Int& b, const Vector2Int& c, const Color& color);
	ENGINE_API Void DrawRectangleFilled(IDrawable* interface, const Vector2Int& minimum, const Vector2Int& maximum, const Color& color);
	ENGINE_API Void DrawRectangleFilled(IDrawable* interface, const RectangleInt& rectangle, const Color& color);
	ENGINE_API Void DrawCircleFilled(IDrawable* interface, const Vector2Int& position, RealType radius, const Color& color);


#pragma region Details

	template<typename ...Parameters>
	Void DrawPath(IDrawable* interface, const Color& color, const Vector2Int& a, const Vector2Int& b, Parameters&&... parameters)
	{
		static_assert( And<IsConvertible<Parameters, Vector2Int> ...>::Value );


		DrawSegment(interface, a, b, color);

		if constexpr ( sizeof...(parameters) > 0 )
			DrawPath( interface, color, b, Forward<Parameters>(parameters)... );
	}

	template<typename ...Parameters>
	Void DrawPolygon(IDrawable* interface, const Color& color, const Vector2Int& a, const Vector2Int& b, Parameters&&... parameters)
	{
		static_assert( And<IsConvertible<Parameters, Vector2Int> ...>::Value );
		static_assert( sizeof...(parameters) > 0 );

	
		Tuple<Parameters ...>	tuple	= { Forward<Parameters>(parameters)... };
		auto&					end		= Visit<sizeof...(parameters) - 1>(tuple);

		DrawSegment(interface, a, end, color);

		DrawPath( interface, color, a, b, Forward<Parameters>(parameters)... );
	}

#pragma endregion
}