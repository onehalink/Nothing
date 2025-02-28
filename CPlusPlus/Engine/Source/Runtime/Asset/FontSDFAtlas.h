#pragma once

#include "Font.h"



namespace Engine
{
	struct ENGINE_API FontSDFAtlas
	{
		struct ConvertedGlyphMetrics
		{
			Vector<2, Int16> size;
			Vector<2, Int16> horizontalBearing;
			Int16 horizontalAdvance;
		};


		struct GlyphSDFLocator
		{
			UInt32 offset;
		};


		static constexpr SizeType FontDefaultPointSize = 12;


		UInt32 pointSize;
		UInt32 pixelsInEM; // glyph width/height in pixels
		UInt32 lineSpace;

		Memory<Byte> glyphSDFs;
		Memory<Float32> precomputedAlphaBlendShapes;
		Memory<ConvertedGlyphMetrics> glyphMetrics;
		Memory<GlyphSDFLocator> glyphSDFLocators;

		BitSet<> glyphExisted;
		Memory<UInt32> unicodeToGlyphMap;


		FontSDFAtlas();
		FontSDFAtlas(const Font* font, Int32 pointSize = FontDefaultPointSize, Int32 dpi = 96);
		FontSDFAtlas(const FontSDFAtlas&) = delete;
		FontSDFAtlas(FontSDFAtlas&& other);
		~FontSDFAtlas();


		Void BuildPrecomputedAlphaBlendShapes(RealType sharpness = 25);


		Void SaveToFile(const U8String& path);
		static FontSDFAtlas LoadFromFile(const U8String& path);


		FontSDFAtlas& operator=(const FontSDFAtlas&) = delete;
		FontSDFAtlas& operator=(FontSDFAtlas&& other);
	private:
		Void SwapWith(FontSDFAtlas& other);
	};
}