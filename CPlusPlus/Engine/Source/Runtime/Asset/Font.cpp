#include "Font.h"



namespace Engine
{
    Font::Font()
    {
        unitsPerEM = 0;
        lineSpace = 0;
        glyphPoints = {};
        glyphOutlineViews = {};
        glyphMetrics = {};

        glyphExisted = { MaximumCodePoint + 1 };
        unicodeToGlyphMap = { MaximumCodePoint + 1 };
    }

    Font::Font(const Font& other)
    {
        CopyFrom(other);
    }

    Font::Font(Font&& other)
    {
        SwapWith(other);
    }

    Font::~Font()
    {

    }

    RealType Font::FUnitsToPixel(Int32 pointSize, Int16 FUnits, Int32 unitsPerEM, Int32 dpi)
    {
        /**
        * Converting FUnits to pixels(reference from https://learn.microsoft.com/en-us/typography/opentype/spec/ttch01)
        * pointSize * resolution / ( 72 points per inch * units_per_em )
        */

        constexpr RealType DefaultDPI = 72;


        return static_cast<RealType>(pointSize * dpi * FUnits) / (DefaultDPI * unitsPerEM);
    }

    Vector2 Font::FUnitsToPixel(Int32 pointSize, const Vector<2, Int16>& FUnits, Int32 unitsPerEM, Int32 dpi)
    {
        Vector2 ret;
        for (SizeType index = 0; index < 2; index++)
            ret[index] = FUnitsToPixel(pointSize, FUnits[index], unitsPerEM, dpi);
       
        return ret;
    }

    Font& Font::operator=(const Font& other)
    {
        CopyFrom(other);

        return *this;
    }

    Font& Font::operator=(Font&& other)
    {
        SwapWith(other);

        return *this;
    }

    Void Font::CopyFrom(const Font& other)
    {
        unitsPerEM = other.unitsPerEM;
        lineSpace = other.lineSpace;

        glyphPoints = other.glyphPoints;
        glyphOutlineViews = other.glyphOutlineViews;
        glyphMetrics = other.glyphMetrics;
        glyphExisted = other.glyphExisted;
        unicodeToGlyphMap = other.unicodeToGlyphMap;
    }

    Void Font::SwapWith(Font& other)
    {
        glyphPoints = Move(other.glyphPoints);
        glyphOutlineViews = Move(other.glyphOutlineViews);
        glyphMetrics = Move(other.glyphMetrics);
        glyphExisted = Move(other.glyphExisted);
        unicodeToGlyphMap = Move(other.unicodeToGlyphMap);
        
        Swap(&unitsPerEM, &other.unitsPerEM);
        Swap(&lineSpace, &other.lineSpace);
    }
}
