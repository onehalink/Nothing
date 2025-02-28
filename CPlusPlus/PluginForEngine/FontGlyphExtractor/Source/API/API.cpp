#include "API.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#pragma comment(lib, "freetype")

#include <fstream>
#include <filesystem>



namespace Engine::Plugin
{
	struct OutlineUserParameters
	{
		FT_Vector end;
		Font* font;
	};


	static Vector<2, Int16> FromFTVector(const FT_Vector& ftv)
	{
		return { ftv.x, ftv.y };
	}

	static Vector<2, Int16> FromFTVector(const FT_Vector* ftv)
	{
		return FromFTVector(*ftv);
	}


#pragma region Callbacks

	int MoveTo(const FT_Vector* to, void* userParameter)
	{
		auto p = (OutlineUserParameters*)userParameter;
		p->end = *to;

		return 0;
	}

	int LineTo(const FT_Vector* to, void* userParameter)
	{
		auto p = (OutlineUserParameters*)userParameter;

		auto start = FromFTVector(p->end);
		auto end = FromFTVector(to);
		auto middle = (start + end) / (Int16)2;

		auto& container = p->font->glyphPoints;
		container.Add(start);
		container.Add(middle);
		container.Add(end);

		p->end = *to;

		return 0;
	}

	int QaudraticBezierCurveTo(const FT_Vector* control, const FT_Vector* to, void* userParameter)
	{
		auto p = (OutlineUserParameters*)userParameter;

		auto start = FromFTVector(p->end);
		auto end = FromFTVector(to);
		auto middle = FromFTVector(control);

		auto& container = p->font->glyphPoints;
		container.Add(start);
		container.Add(middle);
		container.Add(end);

		p->end = *to;

		return 0;
	}

	int CubicBezierCurveTo(const FT_Vector* control0, const FT_Vector* control1, const FT_Vector* to, void* userParameter)
	{
		// do nothing here

		return 0;
	}

#pragma endregion


	Font LoadFontFromMemory(const Void* buffer, SizeType byteCount)
	{
		Font ret;

		FT_Library library;
		FT_Init_FreeType(&library);
		ASSERT(library);

		FT_Face face;
		FT_New_Memory_Face(library, reinterpret_cast<const FT_Byte*>(buffer), byteCount, 0, &face);
		ASSERT(face);

		ret.unitsPerEM = face->units_per_EM;
		ret.lineSpace = face->height;

		FT_Select_Charmap(face, FT_ENCODING_UNICODE);

		{
			FT_UInt glyphIndex;
			UInt32 unicode = FT_Get_First_Char(face, &glyphIndex);

			SizeType glyphCount = 0;
			SizeType glyphPointsCount = 0;

			while (glyphIndex != 0)
			{
				glyphCount++;

				{
					FT_Load_Glyph(face, glyphIndex, FT_LOAD_NO_SCALE);

					FT_Outline_Funcs Callbacks;
					Callbacks.move_to = [](const FT_Vector*, void*) -> int { return 0; };
					Callbacks.line_to = [](const FT_Vector*, void* userParameter) -> int
						{
							*reinterpret_cast<SizeType*>(userParameter) += 3;
							return 0;
						};
					Callbacks.conic_to = [](const FT_Vector*, const FT_Vector*, void* userParameter) -> int
						{
							*reinterpret_cast<SizeType*>(userParameter) += 3;
							return 0;
						};
					Callbacks.cubic_to = [](const FT_Vector*, const FT_Vector*, const FT_Vector*, void*) -> int { return 0; };
					Callbacks.delta = 0;
					Callbacks.shift = 0;

					FT_Outline_Decompose(&face->glyph->outline, &Callbacks, &glyphPointsCount);
				}

				unicode = FT_Get_Next_Char(face, unicode, &glyphIndex);
			}

			ret.glyphPoints = { glyphPointsCount };
			ret.glyphOutlineViews = { glyphCount };
			ret.glyphMetrics = { glyphCount };
		}

		{
			FT_UInt glyphIndex;
			UInt32 unicode = FT_Get_First_Char(face, &glyphIndex);

			SizeType glyphOutlineViewStart = 0;
			SizeType curerntGlyphIndexForStore = 0;
			while (glyphIndex != 0)
			{
				FT_Load_Glyph(face, glyphIndex, FT_LOAD_NO_SCALE);

				{
					auto& metrics = face->glyph->metrics;

					Font::GlyphMetrics value;
					value.width = metrics.width;
					value.height = metrics.height;
					value.horizontalBearingX = metrics.horiBearingX;
					value.horizontalBearingY = metrics.horiBearingY;
					value.horizontalAdvance = metrics.horiAdvance;

					ret.glyphMetrics.Add(value);
				}

				{
					FT_Outline_Funcs Callbacks;
					Callbacks.move_to = MoveTo;
					Callbacks.line_to = LineTo;
					Callbacks.conic_to = QaudraticBezierCurveTo;
					Callbacks.cubic_to = CubicBezierCurveTo;
					Callbacks.delta = 0;
					Callbacks.shift = 0;

					OutlineUserParameters userParameters;
					userParameters.font = &ret;

					FT_Outline_Decompose(&face->glyph->outline, &Callbacks, &userParameters);
				}

				{
					Font::GlyphOutlineView value;
					value.start = ret.glyphPoints.GetBuffer() + glyphOutlineViewStart;
					value.count = ret.glyphPoints.GetCount() - glyphOutlineViewStart;

					ret.glyphOutlineViews.Add(value);

					glyphOutlineViewStart += value.count;
				}

				{
					SizeType begin = ret.glyphExisted.GetCount();
					SizeType end = unicode;
					for (SizeType index = begin; index < end; index++)
						ret.glyphExisted.Add(false);

					ret.glyphExisted.Add(true);

					//ret.glyphExisted[unicode] = true;
					ret.unicodeToGlyphMap[unicode] = curerntGlyphIndexForStore++;
				}

				unicode = FT_Get_Next_Char(face, unicode, &glyphIndex);
			}
		}

		FT_Done_Face(face);
		FT_Done_FreeType(library);

		return ret;
	}

	Font LoadFontFromFile(const U8String& path)
	{
		auto size = std::filesystem::file_size(path.GetBuffer());
		Memory<Byte> temporary(size);

		std::fstream input(path, std::ios::binary | std::ios::in);
		input.read((char*)temporary.GetBuffer(), size);

		return LoadFontFromMemory(temporary.GetBuffer(), temporary.GetCount());
	}
}