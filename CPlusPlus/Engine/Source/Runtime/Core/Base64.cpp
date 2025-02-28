#include "Base64.h"



namespace Engine::Base64
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
	

	Void Encode(Span<Char8> output, ReadOnlySpan<Byte> input)
	{
		/**
		* Note:
		* Read from high to low bits!!
		* Use zero padding when no enough bits
		*/

		SizeType byteCount	= input.GetCount();
		SizeType modulo		= byteCount % 3;

		SizeType writeCursor = 0;
		for (SizeType readCursor = 0, end = byteCount - modulo; readCursor < end; readCursor += 3)
		{
			Byte first	= input[ readCursor + 0 ];
			Byte second	= input[ readCursor + 1 ];
			Byte third	= input[ readCursor + 2 ];

			UInt32 packedBits =
				first	<< 16 |
				second	<<  8 |
				third	<<  0;

			SizeType index0 = ( packedBits >> 18 ) & 0x3F;
			SizeType index1 = ( packedBits >> 12 ) & 0x3F;
			SizeType index2 = ( packedBits >>  6 ) & 0x3F;
			SizeType index3 = ( packedBits >>  0 ) & 0x3F;

			output[ writeCursor++ ] = EncodeLookupTable[index0];
			output[ writeCursor++ ] = EncodeLookupTable[index1];
			output[ writeCursor++ ] = EncodeLookupTable[index2];
			output[ writeCursor++ ] = EncodeLookupTable[index3];
		}

		switch (modulo)
		{
		case 1:
		{
			// 8 bits(6 + 2 + '=' + '=')

			Byte last = input[ byteCount - 1 ];

			output[ writeCursor++ ] = EncodeLookupTable[ last >> 2 ];
			output[ writeCursor++ ] = EncodeLookupTable[ last & 0x03 ];
			output[ writeCursor++ ] = Padding;
			output[ writeCursor++ ] = Padding;
		}
			break;
		case 2:
		{
			// 16 bits(6 + 6 + 4 + '=')

			UInt16 packedBits = input[ byteCount - 2 ] << 8 | input[ byteCount - 1 ] << 0;

			output[ writeCursor++ ] = EncodeLookupTable[ ( packedBits >> 10 ) & 0x3F ];
			output[ writeCursor++ ] = EncodeLookupTable[ ( packedBits >>  4 ) & 0x3F ];
			output[ writeCursor++ ] = EncodeLookupTable[ ( packedBits <<  2 ) & 0x3C ];
			output[ writeCursor++ ] = Padding;
		}
			break;
		}
	}

	Void Decode(Span<Byte> output, ReadOnlySpan<Char8> input)
	{
		SizeType byteCount = input.GetCount();

		SizeType size		= GetDecodedLength(byteCount);
		SizeType realSize	=
			input[ byteCount - 2 ] == Padding ? size - 2 :
			input[ byteCount - 1 ] == Padding ? size - 1 : size;

		SizeType readCursor		= 0;
		SizeType writeCursor	= 0;
		SizeType end			= realSize == size ? byteCount : byteCount - 4;
		for ( ; readCursor < end; readCursor += 4)
		{
			Char8 first		= input[ readCursor + 0 ];
			Char8 second	= input[ readCursor + 1 ];
			Char8 third		= input[ readCursor + 2 ];
			Char8 fourth	= input[ readCursor + 3 ];

			Byte value0 = DecodeLookupTable[first];
			Byte value1 = DecodeLookupTable[second];
			Byte value2 = DecodeLookupTable[third];
			Byte value3 = DecodeLookupTable[fourth];

			UInt32 packedBits =
				value0 << 18 |
				value1 << 12 |
				value2 <<  6 |
				value3 <<  0;

			output[ writeCursor++ ] = ( packedBits >> 16 ) & 0xFF;
			output[ writeCursor++ ] = ( packedBits >>  8 ) & 0xFF;
			output[ writeCursor++ ] = ( packedBits >>  0 ) & 0xFF;
		}

		if( realSize != size )
			switch ( realSize - size )
			{
			case 1:
			{
				Char8 first		= input[ byteCount - 4 ];
				Char8 second	= input[ byteCount - 3 ];
				Char8 third		= input[ byteCount - 2 ];

				Byte value0 = DecodeLookupTable[first];
				Byte value1 = DecodeLookupTable[second];
				Byte value2 = DecodeLookupTable[third];

				UInt16 packedBits =
					value0 << 10 |
					value1 <<  4 |
					value2 >>  2; // 0b????00

				output[ writeCursor++ ] = ( packedBits >> 8 ) & 0xFF;
				output[ writeCursor++ ] = ( packedBits >> 0 ) & 0xFF;
			}
				break;
			case 2:
				output[writeCursor] =
					DecodeLookupTable[ input[ byteCount - 4 ] ] << 2 |
					DecodeLookupTable[ input[ byteCount - 3 ] ] << 0;
				break;
			}
	}
}
