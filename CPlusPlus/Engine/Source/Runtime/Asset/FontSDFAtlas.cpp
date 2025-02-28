#include "FontSDFAtlas.h"

#include "../Platform/Service/FileSystem/File.h"



namespace Engine
{
	static Vector2 Remap01(const Vector2& point, const Vector2& size)
	{
		return Vector2{
			point.x / (size.x - 1),
			point.y / (size.y - 1),
		};
	}


	FontSDFAtlas::FontSDFAtlas()
	{

	}

	FontSDFAtlas::FontSDFAtlas(const Font* font, Int32 pointSize, Int32 dpi)
	{
		{
			this->pointSize = pointSize;
			this->pixelsInEM = Font::FUnitsToPixel(pointSize, font->unitsPerEM, font->unitsPerEM, dpi);
			this->lineSpace = Font::FUnitsToPixel(pointSize, font->lineSpace, font->unitsPerEM, dpi);

			glyphExisted = font->glyphExisted;
			unicodeToGlyphMap = font->unicodeToGlyphMap;
		}

		SizeType glyphCount = font->glyphMetrics.GetCount();
		{
			glyphMetrics = { glyphCount };
			glyphSDFLocators = { glyphCount };
		}

		{
			SizeType requiredSize = 0;
			for (SizeType index = 0; index < glyphCount; index++)
			{
				auto& metrics = font->glyphMetrics[index];

				auto& convertedMetrics = glyphMetrics[index];
				//convertedMetrics.size = Font::FUnitsToPixel(pointSize, Vector<2, Int16>(metrics.width, metrics.height), font->unitsPerEM, dpi);
				convertedMetrics.size = Font::FUnitsToPixel(pointSize, Vector<2, Int16>(metrics.width, metrics.height), font->unitsPerEM, dpi) + Vector2::One * 0.5; // ceil
				convertedMetrics.horizontalBearing = Font::FUnitsToPixel(pointSize, Vector<2, Int16>(metrics.horizontalBearingX, metrics.horizontalBearingY - (metrics.height - 1)), font->unitsPerEM, dpi);
				convertedMetrics.horizontalAdvance = Font::FUnitsToPixel(pointSize, metrics.horizontalAdvance, font->unitsPerEM, dpi);

				requiredSize += convertedMetrics.size.x * convertedMetrics.size.y;
			}

			glyphSDFs = { requiredSize };

			UInt32 offset = 0;
			for (SizeType index = 0; index < glyphCount; index++)
			{
				auto& size = glyphMetrics[index].size;
				auto& locator = glyphSDFLocators[index];

				locator.offset = offset;
				offset += size.x * size.y;
			}
		}

		/**
		* reference from https://github.com/kocsis1david/font-demo/blob/master/howitworks.md
		* build glyph sdf
		*/
		DynamicArray<Vector2> temporaryPoints(64);
		for (SizeType index = 0; index < glyphCount; index++)
		{
			auto& originalMetrics = font->glyphMetrics[index];

			{
				temporaryPoints.Clear();

				auto& outlineView = font->glyphOutlineViews[index];
				for (SizeType iteration = 0; iteration < outlineView.count; iteration++)
				{
					auto& point = outlineView.start[iteration];
					auto converted = Font::FUnitsToPixel(pointSize, point, font->unitsPerEM, dpi);

					converted -= Font::FUnitsToPixel(
						pointSize,
						{
							originalMetrics.horizontalBearingX,
							originalMetrics.horizontalBearingY - (originalMetrics.height - 1),
						},
						font->unitsPerEM,
						dpi
					);

					temporaryPoints.Add(
						Remap01(
							converted,
							Font::FUnitsToPixel(
								pointSize,
								{
									originalMetrics.width,
									originalMetrics.height,
								},
								font->unitsPerEM,
								dpi
							)
						)
					);
				}
			}

			{
				auto& locator = glyphSDFLocators[index];

				auto& metrics = glyphMetrics[index];
				auto& size = metrics.size;

				for (SizeType y = 0; y < size.y; y++)
					for (SizeType x = 0; x < size.x; x++)
					{
						auto p = Remap01({ x, y }, metrics.size);

						RealType minUnsignedDistance = NumericLimit<RealType>::Maximum;
						RealType minDistance = NumericLimit<RealType>::Maximum;
						for (SizeType iteration = 0; iteration < temporaryPoints.GetCount(); iteration += 3)
						{
							auto& a = temporaryPoints[iteration + 0];
							auto& b = temporaryPoints[iteration + 1];
							auto& c = temporaryPoints[iteration + 2];

							auto t = CalculateTimeForBezierCurve(a, c, p);
							auto unsignedDistance = Magnitude(Lerp(a, c, t) - p);

							constexpr RealType UnsignedDistanceBias = 0.001;
							if (unsignedDistance < minUnsignedDistance + UnsignedDistanceBias)
							{
								auto distance = -DistanceToQuadraticBezierCurve(a, b, c, p, t);

								if (unsignedDistance > minUnsignedDistance - UnsignedDistanceBias)
								{
									auto previousPoint = temporaryPoints[iteration - 2];
									auto previousDistance = DistanceToLine(a, c, previousPoint);

									minDistance = previousDistance > 0 ? Maximum(minDistance, distance) : Minimum(minDistance, distance);
								}
								else
									minDistance = distance;

								minUnsignedDistance = unsignedDistance;
							}
						}

						// [-1, 1] -> [0, 1] -> [0, 255]
						glyphSDFs.GetBuffer()[locator.offset + size.x * y + x] = (minDistance + 1) / 2 * 255;
					}
			}
		}

		BuildPrecomputedAlphaBlendShapes();
	}

	FontSDFAtlas::FontSDFAtlas(FontSDFAtlas&& other)
	{
		SwapWith(other);
	}

	FontSDFAtlas::~FontSDFAtlas()
	{

	}

	Void FontSDFAtlas::BuildPrecomputedAlphaBlendShapes(RealType sharpness)
	{
		if (precomputedAlphaBlendShapes.GetCount() != glyphSDFs.GetCount())
			precomputedAlphaBlendShapes = { glyphSDFs.GetCount() };

		SizeType glyphCount = glyphMetrics.GetCount();
		for (SizeType index = 0; index < glyphCount; index++)
		{
			UInt32 offset = glyphSDFLocators[index].offset;
			Vector<2, Int16> size = glyphMetrics[index].size;

			auto begin0 = glyphSDFs.GetBuffer() + offset;
			auto begin1 = precomputedAlphaBlendShapes.GetBuffer() + offset;
			for (SizeType iteration = 0, end = size.x * size.y; iteration < end; iteration++)
			{
				RealType distance = begin0[iteration] / 255.0 * 2 - 1;
				RealType alpha = Clamp01(distance * sharpness + 0.5);

				begin1[iteration] = alpha;
			}
		}
	}

	Void FontSDFAtlas::SaveToFile(const U8String& path)
	{
		ASSERT(!File::Exist(path));

		UInt32 glyphSDFStorageSize = glyphSDFs.GetCount();
		UInt32 glyphCount = glyphMetrics.GetCount();
		UInt32 unicodeCount = Font::MaximumCodePoint + 1;

		File output(path, File::Mode::Write);
		output.Write(&pointSize, sizeof(UInt32));
		output.Write(&pixelsInEM, sizeof(UInt32));
		output.Write(&lineSpace, sizeof(UInt32));
		output.Write(&glyphSDFStorageSize, sizeof(UInt32));
		output.Write(&glyphCount, sizeof(UInt32));
		output.Write(&unicodeCount, sizeof(UInt32));

		output.Write(glyphSDFs.GetBuffer(), sizeof(Byte) * glyphSDFStorageSize);
		output.Write(glyphMetrics.GetBuffer(), sizeof(ConvertedGlyphMetrics) * glyphCount);
		output.Write(glyphSDFLocators.GetBuffer(), sizeof(GlyphSDFLocator) * glyphCount);

		output.Write(glyphExisted.GetBuffer(), glyphExisted.GetCapacity() / 8);
		output.Write(unicodeToGlyphMap.GetBuffer(), sizeof(UInt32) * unicodeCount);
	}

	FontSDFAtlas FontSDFAtlas::LoadFromFile(const U8String& path)
	{
		ASSERT(File::Exist(path));

		FontSDFAtlas result;

		File input(path, File::Mode::Read);

		input.Read(&result.pointSize, sizeof(UInt32));
		input.Read(&result.pixelsInEM, sizeof(UInt32));
		input.Read(&result.lineSpace, sizeof(UInt32));

		UInt32 glyphSDFStorageSize = 0;
		input.Read(&glyphSDFStorageSize, sizeof(UInt32));

		UInt32 glyphCount = 0;
		input.Read(&glyphCount, sizeof(UInt32));

		UInt32 unicodeCount = 0;
		input.Read(&unicodeCount, sizeof(UInt32));

		result.glyphSDFs = { glyphSDFStorageSize };
		input.Read(result.glyphSDFs.GetBuffer(), sizeof(Byte) * glyphSDFStorageSize);

		result.glyphMetrics = { glyphCount };
		input.Read(result.glyphMetrics.GetBuffer(), sizeof(ConvertedGlyphMetrics) * glyphCount);

		result.glyphSDFLocators = { glyphCount };
		input.Read(result.glyphSDFLocators.GetBuffer(), sizeof(GlyphSDFLocator) * glyphCount);

		result.glyphExisted = { Font::MaximumCodePoint };
		input.Read(result.glyphExisted.GetBuffer(), result.glyphExisted.GetCapacity() / 8);

		result.unicodeToGlyphMap = { unicodeCount };
		input.Read(result.unicodeToGlyphMap.GetBuffer(), sizeof(UInt32) * unicodeCount);

		result.BuildPrecomputedAlphaBlendShapes();

		return result;
	}

	FontSDFAtlas& FontSDFAtlas::operator=(FontSDFAtlas&& other)
	{
		SwapWith(other);

		return *this;
	}

	Void FontSDFAtlas::SwapWith(FontSDFAtlas& other)
	{
		glyphSDFs = Move(other.glyphSDFs);
		precomputedAlphaBlendShapes = Move(other.precomputedAlphaBlendShapes);
		glyphMetrics = Move(other.glyphMetrics);
		glyphSDFLocators = Move(other.glyphSDFLocators);
		glyphExisted = Move(other.glyphExisted);
		unicodeToGlyphMap = Move(other.unicodeToGlyphMap);

		Swap(&pointSize, &other.pointSize);
		Swap(&pixelsInEM, &other.pixelsInEM);
		Swap(&lineSpace, &other.lineSpace);
	}
}
