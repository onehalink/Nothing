#include "Base64.h"



namespace Engine
{
	constexpr Char8 EncodeLookupTable[64] =
	{
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', '0', '1', '2', '3',
		'4', '5', '6', '7', '8', '9', '+', '/',
	};
	constexpr Byte DecodeLookupTable[128] =
	{
		/* nul, soh, stx, etx, eot, enq, ack, bel, */
		255, 255, 255, 255, 255, 255, 255, 255,
		/*  bs,  ht,  nl,  vt,  np,  cr,  so,  si, */
		255, 255, 255, 255, 255, 255, 255, 255,
		/* dle, dc1, dc2, dc3, dc4, nak, syn, etb, */
		255, 255, 255, 255, 255, 255, 255, 255,
		/* can,  em, sub, esc,  fs,  gs,  rs,  us, */
		255, 255, 255, 255, 255, 255, 255, 255,
		/*  sp, '!', '"', '#', '$', '%', '&', ''', */
		255, 255, 255, 255, 255, 255, 255, 255,
		/* '(', ')', '*', '+', ',', '-', '.', '/', */
		255, 255, 255,  62, 255, 255, 255,  63,
		/* '0', '1', '2', '3', '4', '5', '6', '7', */
		52,  53,  54,  55,  56,  57,  58,  59,
		/* '8', '9', ':', ';', '<', '=', '>', '?', */
		60,  61, 255, 255, 255, 255, 255, 255,
		/* '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', */
		255,   0,   1,  2,   3,   4,   5,    6,
		/* 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', */
		7,   8,   9,  10,  11,  12,  13,  14,
		/* 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', */
		15,  16,  17,  18,  19,  20,  21,  22,
		/* 'X', 'Y', 'Z', '[', '\', ']', '^', '_', */
		23,  24,  25, 255, 255, 255, 255, 255,
		/* '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', */
		255,  26,  27,  28,  29,  30,  31,  32,
		/* 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', */
		33,  34,  35,  36,  37,  38,  39,  40,
		/* 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', */
		41,  42,  43,  44,  45,  46,  47,  48,
		/* 'x', 'y', 'z', '{', '|', '}', '~', del, */
		49,  50,  51, 255, 255, 255, 255, 255
	};

	constexpr Char8 Padding = '=';
	

	Memory<Char8> Base64::Encode(const Void* buffer, SizeType byteCount)
	{
		/**
		* Note:
		* Read from high to low bits!!
		* Use zero padding when no enough bits
		*/

		SizeType count	= byteCount / 3;
		SizeType modulo	= byteCount % 3;
		SizeType size	= ( count + ( modulo == 0 ? 0 : 1 ) ) * 4;

		auto from	= reinterpret_cast<const Byte*>(buffer);
		auto to		= Memory<Char8>(size);

		SizeType readCursor		= 0;
		SizeType writeCursor	= 0;
		SizeType end			= byteCount - modulo;
		for (; readCursor < end; readCursor += 3)
		{
			Byte first	= from[ readCursor + 0 ];
			Byte second	= from[ readCursor + 1 ];
			Byte third	= from[ readCursor + 2 ];

			UInt32 packedBits =
				first	<< 16 |
				second	<<  8 |
				third	<<  0;

			SizeType index0 = ( packedBits >> 18 ) & 0x3F;
			SizeType index1 = ( packedBits >> 12 ) & 0x3F;
			SizeType index2 = ( packedBits >>  6 ) & 0x3F;
			SizeType index3 = ( packedBits >>  0 ) & 0x3F;

			to[ writeCursor++ ] = EncodeLookupTable[index0];
			to[ writeCursor++ ] = EncodeLookupTable[index1];
			to[ writeCursor++ ] = EncodeLookupTable[index2];
			to[ writeCursor++ ] = EncodeLookupTable[index3];
		}

		switch (modulo)
		{
		case 1:
		{
			// 8 bits(6 + 2 + '=' + '=')

			Byte last = from[ byteCount - 1 ];

			to[ writeCursor++ ] = EncodeLookupTable[ last >> 2 ];
			to[ writeCursor++ ] = EncodeLookupTable[ last & 0x03 ];
			to[ writeCursor++ ] = Padding;
			to[ writeCursor++ ] = Padding;
		}
			break;
		case 2:
		{
			// 16 bits(6 + 6 + 4 + '=')

			UInt16 packedBits = from[ byteCount - 2 ] << 8 | from[ byteCount - 1 ] << 0;

			to[ writeCursor++ ] = EncodeLookupTable[ ( packedBits >> 10 ) & 0x3F ];
			to[ writeCursor++ ] = EncodeLookupTable[ ( packedBits >>  4 ) & 0x3F ];
			to[ writeCursor++ ] = EncodeLookupTable[ ( packedBits <<  2 ) & 0x3C ];
			to[ writeCursor++ ] = Padding;
		}
			break;
		}

		return to;
	}

	Memory<Byte> Base64::Decode(const Void* buffer, SizeType byteCount)
	{
		auto pointer = reinterpret_cast<const Char8*>(buffer);

		SizeType size		= byteCount / 4 * 3;
		SizeType realSize	=
			pointer[ byteCount - 2 ] == Padding ? size - 2 :
			pointer[ byteCount - 1 ] == Padding ? size - 1 : size;

		Memory<Byte> result(realSize);

		auto from	= pointer;
		auto to		= result.GetBuffer();

		SizeType readCursor		= 0;
		SizeType writeCursor	= 0;
		SizeType end			= realSize == size ? byteCount : byteCount - 4;
		for (; readCursor < end; readCursor += 4)
		{
			Char8 first		= from[ readCursor + 0 ];
			Char8 second	= from[ readCursor + 1 ];
			Char8 third		= from[ readCursor + 2 ];
			Char8 fourth	= from[ readCursor + 3 ];

			Byte value0 = DecodeLookupTable[first];
			Byte value1 = DecodeLookupTable[second];
			Byte value2 = DecodeLookupTable[third];
			Byte value3 = DecodeLookupTable[fourth];

			UInt32 packedBits =
				value0 << 18 |
				value1 << 12 |
				value2 <<  6 |
				value3 <<  0;

			to[ writeCursor++ ] = ( packedBits >> 16 ) & 0xFF;
			to[ writeCursor++ ] = ( packedBits >>  8 ) & 0xFF;
			to[ writeCursor++ ] = ( packedBits >>  0 ) & 0xFF;
		}

		if( realSize != size )
			switch ( realSize - size )
			{
			case 1:
			{
				Char8 first		= from[ byteCount - 4 ];
				Char8 second	= from[ byteCount - 3 ];
				Char8 third		= from[ byteCount - 2 ];

				Byte value0 = DecodeLookupTable[first];
				Byte value1 = DecodeLookupTable[second];
				Byte value2 = DecodeLookupTable[third];

				UInt16 packedBits =
					value0 << 10 |
					value1 <<  4 |
					value2 >>  2; // 0b????00

				to[ writeCursor++ ] = ( packedBits >> 8 ) & 0xFF;
				to[ writeCursor++ ] = ( packedBits >> 0 ) & 0xFF;
			}
				break;
			case 2:
				to[writeCursor] =
					DecodeLookupTable[ from[ byteCount - 4 ] ] << 2 |
					DecodeLookupTable[ from[ byteCount - 3 ] ] << 0;
				break;
			}

		return result;
	}
}
