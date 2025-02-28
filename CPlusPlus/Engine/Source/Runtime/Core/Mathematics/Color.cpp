#include "Color.h"



namespace Engine
{
	RealType Luminance(const Color& color)
	{
		return
			color.r * 0.2126 +
			color.g * 0.7152 +
			color.b * 0.0722;
	}

	Color Inverted(const Color& color)
	{
		return
		{
			1 - color.r,
			1 - color.g,
			1 - color.b,
			color.a,
		};
	}

	Color Lightened(const Color& color, RealType amount)
	{
		return
		{
			color.r + ( 1 - color.r ) * amount,
			color.g + ( 1 - color.g ) * amount,
			color.b + ( 1 - color.b ) * amount,
			color.a,
		};
	}

	Color Darkened(const Color& color, RealType amount)
	{
		amount = 1 - amount;

		return
		{
			color.r * amount,
			color.g * amount,
			color.b * amount,
			color.a,
		};
	}

	Color ToSRGB(const Color& color)
	{
		/**
		* Linear to sRGB
		*
		* Condition				| Value
		* 0 <= L <= 0.0031308	| S = L * 12.92
		* 0.0031308 < L <= 1	| S = 1.055 * (L ^ (1 / 2.4)) - 0.055
		*/

		Color result;
		result.a = color.a;
		for (SizeType index = 0; index < 3; index++)
		{
			RealType value = color[index];

			result[index] = value > 0.0031308 ?
				Power( value, 1 / 2.4 ) * 1.055 - 0.055 :
				value * 12.92;
		}

		return result;
	}

	Color ToLinear(const Color& color)
	{
		/**
		* sRGB to Linear
		* 
		* Condition			| Value
		* 0 <= S <= 0.04045	| L = S / 12.92
		* 0.04045 < S <= 1	| L = ((S + 0.055) / 1.055) ^ 2.4
		*/

		Color result;
		result.a = color.a;
		for (SizeType index = 0; index < 3; index++)
		{
			RealType value = color[index];

			result[index] = value > 0.04045 ?
				Power( ( value + 0.055 ) / 1.055, 2.4 ) :
				value / 12.92;
		}

		return result;
	}

	Color FromR8G8B8(UInt32 pixel)
	{
		return
		{
			static_cast<RealType>( ( pixel >>  0 ) & 0xFF ) / 255,
			static_cast<RealType>( ( pixel >>  8 ) & 0xFF ) / 255,
			static_cast<RealType>( ( pixel >> 16 ) & 0xFF ) / 255,
			1,
		};
	}

	Color FromR8G8B8A8(UInt32 pixel)
	{
		return
		{
			static_cast<RealType>( ( pixel >>  0 ) & 0xFF ) / 255,
			static_cast<RealType>( ( pixel >>  8 ) & 0xFF ) / 255,
			static_cast<RealType>( ( pixel >> 16 ) & 0xFF ) / 255,
			static_cast<RealType>( ( pixel >> 24 ) & 0xFF ) / 255,
		};
	}

	Color FromB8G8R8(UInt32 pixel)
	{
		return
		{
			static_cast<RealType>( ( pixel >> 16 ) & 0xFF ) / 255,
			static_cast<RealType>( ( pixel >>  8 ) & 0xFF ) / 255,
			static_cast<RealType>( ( pixel >>  0 ) & 0xFF ) / 255,
			1,
		};
	}

	Color FromB8G8R8A8(UInt32 pixel)
	{
		return
		{
			static_cast<RealType>( ( pixel >> 16 ) & 0xFF ) / 255,
			static_cast<RealType>( ( pixel >>  8 ) & 0xFF ) / 255,
			static_cast<RealType>( ( pixel >>  0 ) & 0xFF ) / 255,
			static_cast<RealType>( ( pixel >> 24 ) & 0xFF ) / 255,
		};
	}

	UInt32 ToR8G8B8(const Color& color)
	{
		return
			( static_cast<Byte>( color.r * 255 ) <<  0 ) |
			( static_cast<Byte>( color.g * 255 ) <<  8 ) |
			( static_cast<Byte>( color.b * 255 ) << 16 );
	}

	UInt32 ToR8G8B8A8(const Color& color)
	{
		return
			( static_cast<Byte>( color.r * 255 ) <<  0 ) |
			( static_cast<Byte>( color.g * 255 ) <<  8 ) |
			( static_cast<Byte>( color.b * 255 ) << 16 ) |
			( static_cast<Byte>( color.a * 255 ) << 24 );
	}

	UInt32 ToB8G8R8(const Color& color)
	{
		return
			( static_cast<Byte>( color.r * 255 ) << 16 ) |
			( static_cast<Byte>( color.g * 255 ) <<  8 ) |
			( static_cast<Byte>( color.b * 255 ) <<  0 );
	}

	UInt32 ToB8G8R8A8(const Color& color)
	{
		return
			( static_cast<Byte>( color.r * 255 ) << 16 ) |
			( static_cast<Byte>( color.g * 255 ) <<  8 ) |
			( static_cast<Byte>( color.b * 255 ) <<  0 ) |
			( static_cast<Byte>( color.a * 255 ) << 24 );
	}
}
