#pragma once

#include "../Core.h"



namespace Engine
{
	struct ENGINE_API Font
	{
		struct GlyphMetrics
		{
			Int16 width;
			Int16 height;
			Int16 horizontalBearingX;
			Int16 horizontalBearingY;
			Int16 horizontalAdvance;
		};


		struct GlyphOutlineView
		{
			Vector<2, Int16>* start;
			UInt32 count;
		};


		static constexpr UInt32 MaximumCodePoint = 0x10FFFF;


		Int32 unitsPerEM;
		Int32 lineSpace;
		
		DynamicArray<Vector<2, Int16>> glyphPoints; // points of the quadratic bezier curve
		DynamicArray<GlyphOutlineView> glyphOutlineViews;
		DynamicArray<GlyphMetrics> glyphMetrics;

		BitSet<> glyphExisted;
		Memory<UInt32> unicodeToGlyphMap;


		Font();
		Font(const Font& other);
		Font(Font&& other);
		~Font();


		static RealType FUnitsToPixel(Int32 pointSize, Int16 FUnits, Int32 unitsPerEM, Int32 dpi);
		static Vector2 FUnitsToPixel(Int32 pointSize, const Vector<2, Int16>& FUnits, Int32 unitsPerEM, Int32 dpi);


		Font& operator=(const Font& other);
		Font& operator=(Font&& other);
	private:
		Void CopyFrom(const Font& other);
		Void SwapWith(Font& other);
	};
}