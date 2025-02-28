#include "Text.h"



namespace Engine::UI
{
	constexpr SizeType GlyphCount	= 95;
	constexpr SizeType GlyphOffset	= 32;

	const Byte GlyphMasks[GlyphCount][16] =
	{
		#include "AsciiLibrary.inline"
	};


	Void Text(IDrawable* interface, const Vector2Int& position, const U8String& text, const Color& color)
	{
		auto width	= FontSizeInPixel.x;
		auto height	= FontSizeInPixel.y;

		Vector2Int O = position;
		for (SizeType iteration = 0; iteration < text.GetCount(); iteration++)
		{
			Char8 character = text[iteration];
			if ( character < GlyphOffset + 1 ) // is ' '(space) if character == 32
				continue;

			SizeType index	= character - GlyphOffset;
			auto Mask		= GlyphMasks[index];

			for (Int32 x = 0; x < width; x++)
			{
				Int32 row = O.x + width * iteration + x;

				for (Int32 y = 0; y < height; y++)
					if ( ( Mask[y] >> x ) & 0x01 )
					{
						Int32 column = O.y + y;

						interface->SetPixel(row, column, color);
					}
			}
		}
	}
}