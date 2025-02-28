#include "Text.h"



namespace Engine::UI
{
	static Color Lerp3(const Color& background, const Color& foreground, RealType alpha)
	{
		return Color
		{
			Lerp(background.r, foreground.r, alpha),
			Lerp(background.g, foreground.g, alpha),
			Lerp(background.b, foreground.b, alpha),
		};
	}


	Void Text(IDrawable* interface, const Vector2Int& position, const U32String& text, const Color& color)
	{
		auto& atlas = fontSDFAtlasStack.Top();

		Rectangle<Int16> safeArea = interface->SafeArea();

		Vector<2, Int16> penPosition = position;
		for (SizeType index = 0; index < text.GetCount(); index++)
		{
			UInt32 unicode = text[index];
			if ( !atlas.glyphExisted[unicode] )
			{
				if ( !atlas.glyphExisted[FallbackUnicodeChar] )
					continue;

				unicode = FallbackUnicodeChar;
			}

			UInt32 glyphIndex	= atlas.unicodeToGlyphMap[unicode];
			auto& metrics		= atlas.glyphMetrics[glyphIndex];
			auto& locator		= atlas.glyphSDFLocators[glyphIndex];
			auto shape			= atlas.precomputedAlphaBlendShapes.GetBuffer() + locator.offset;

			auto minimum		= penPosition + metrics.horizontalBearing;
			auto maximum		= minimum + metrics.size;
			auto limitMinimum	= Clamp( minimum, safeArea.minimum, safeArea.maximum );
			auto limitMaximum	= Clamp( maximum, safeArea.minimum, safeArea.maximum );

			for(SizeType y = limitMinimum.y; y < limitMaximum.y; y++)
				for (SizeType x = limitMinimum.x; x < limitMaximum.x; x++)
				{
					auto u = x - minimum.x;
					auto v = y - minimum.y;

					RealType alpha = shape[ metrics.size.x * v + u ];

					auto& background = interface->GetPixel(x, y);
					interface->SetPixel( x, y, Lerp3(background, color, alpha) );
				}

			penPosition.x += metrics.horizontalAdvance;
		}
	}
}


namespace Engine::UI::Private
{
	Vector2Int CalcualteTextRenderSize(const U32String& text)
	{
		auto& atlas = fontSDFAtlasStack.Top();

		Int32 width = 0;
		for (SizeType index = 0; index < text.GetCount(); index++)
		{
			auto unicode = text[index];
			if (!atlas.glyphExisted[unicode])
			{
				unicode = FallbackUnicodeChar;

				if (!atlas.glyphExisted[unicode])
					continue;
			}

			auto glyphIndex = atlas.unicodeToGlyphMap[unicode];

			width += atlas.glyphMetrics[glyphIndex].horizontalAdvance;
		}

		return { width, atlas.pixelsInEM };
	}

	Void RenderAlignedText(IDrawable* interface, Alignment alignment, const RectangleInt& relativeTo, const U32String& text, const Color& color)
	{
		Vector2Int size = CalcualteTextRenderSize(text);
		Text(interface, Private::CalculateRectangleAlignment(alignment, relativeTo, size), text, color);
	}
}