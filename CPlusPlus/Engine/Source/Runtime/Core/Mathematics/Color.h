#pragma once

#include "../CoreMinimal.h"



namespace Engine
{
	/**
	* Note:
	*
	*
	* sRGB to Linear
	*
	* Condition			| Value
	* 0 <= S <= 0.04045	| L = S / 12.92
	* 0.04045 < S <= 1	| L = ((S + 0.055) / 1.055) ^ 2.4
	*
	* Linear to sRGB
	*
	* Condition				| Value
	* 0 <= L <= 0.0031308	| S = L * 12.92
	* 0.0031308 < L <= 1	| S = 1.055 * (L ^ (1 / 2.4)) - 0.055
	*/


	// The different kinds of gamma spaces we expect to need to convert from/to
	enum class GammaSpace
	{
		Linear,		// No gamma correction is applied to this space

		Power22,	// A simplified sRGB gamma correction is applied, Power(1/2.2)
		sRGB,		// Use the standard sRGB conversion
	};


	struct ENGINE_API Color
	{
		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Cyan;
		static const Color Magenta;


		union
		{

			UInt32		packedBits;
			Byte		components[4];
			struct
			{
				Byte	r,
						g,
						b,
						a;
			};
		};


		Color();
		Color(UInt32 packedBits);
		Color(Byte r, Byte g, Byte b, Byte a = 255);
		Color(const Color& other);
		Color& operator=(const Color& other);


		Byte& operator[](SizeType index);
		const Byte& operator[](SizeType index) const;

		Bool operator==(Color color) const;
		Bool operator!=(Color color) const;
	};


	struct ENGINE_API LinearColor
	{
		union
		{
			RealType		components[4];
			struct
			{
				RealType	r,
							g,
							b,
							a;
			};
		};


		LinearColor();
		LinearColor(Color color, GammaSpace gammaSpace = GammaSpace::sRGB);
		LinearColor(RealType r, RealType g, RealType b, RealType a = 1);
		LinearColor(const LinearColor& other);
		LinearColor& operator=(const LinearColor& other);


		Void Clamp01();
		RealType Luminance() const;


		Color ToColor(GammaSpace gammaSpace = GammaSpace::sRGB) const;


		RealType& operator[](SizeType index);
		const RealType& operator[](SizeType index) const;

		LinearColor operator+(const LinearColor& other) const;
		LinearColor operator-(const LinearColor& other) const;
		LinearColor operator*(const LinearColor& other) const;
		LinearColor operator*(RealType scalar) const;
		friend LinearColor operator*(RealType scalar, const LinearColor& linearColor)
		{
			return linearColor * scalar;
		}
		LinearColor operator/(RealType scalar) const;

		LinearColor& operator+=(const LinearColor& other);
		LinearColor& operator-=(const LinearColor& other);
		LinearColor& operator*=(const LinearColor& other);
		LinearColor& operator*=(RealType scalar);
		LinearColor& operator/=(RealType scalar);
	};
}