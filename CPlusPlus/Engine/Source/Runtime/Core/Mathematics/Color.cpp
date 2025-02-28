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

	Color ToSrgb(const Color& color)
	{
		constexpr RealType Exponent = 1 / 2.2;

		return
		{
			Power( color.r, Exponent ),
			Power( color.g, Exponent ),
			Power( color.b, Exponent ),
			color.a,
		};
	}

	Color ToLinear(const Color& color)
	{
		constexpr RealType Exponent = 2.2;

		return
		{
			Power( color.r, Exponent ),
			Power( color.g, Exponent ),
			Power( color.b, Exponent ),
			color.a,
		};
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
