#pragma once

#include "../Template.h"



namespace Engine
{
	using CodePoint = Char32; // Used to represent unicode(0 - 0x10FFFF)


	enum class TextEncoding
	{
		UTF8,
		UTF16,
		//UTF32,
	};


	template<TextEncoding TE>
	using UTFDeduceDataType = typename Conditional<TE == TextEncoding::UTF8, Char8, Char16>::Type;


	template<TextEncoding TE, typename T = UTFDeduceDataType<TE>> SizeType GetCodePointCountFromUTFElements(const T* UTFElements, SizeType count);
	template<TextEncoding TE> SizeType GetUTFElementCountFromCodePoints(const CodePoint* codepoints, SizeType count);

	/**
	* Convert UTF encoding sequence to a codepoint
	* 
	* @return Indicate how many UTF elements had been used
	*/
	template<TextEncoding TE, typename T = UTFDeduceDataType<TE>> SizeType FromUTF(CodePoint* outputResult, const T* inUTFSequence);
	/**
	* Convert a codepoint to UTF encoding sequence
	* 
	* @return Indicate a codepoint could be converted to how many UTF elements
	*/
	template<TextEncoding TE, typename T = UTFDeduceDataType<TE>> SizeType ToUTF(T* outputResult, CodePoint codepoint);


#pragma region Details

	template<TextEncoding TE, typename T>
	SizeType GetCodePointCountFromUTFElements(const T* UTFElements, SizeType count)
	{
		SizeType ret = 0;
		for (SizeType offset = 0; offset < count;)
		{
			T value = UTFElements[offset];

			if constexpr ( TE == TextEncoding::UTF8 )
			{
				if ( ( value & 0x80 ) == 0x00 )
					offset += 1;
				else if ( ( value & 0xE0 ) == 0xC0 )
					offset += 2;
				else if ( ( value & 0xF0 ) == 0xE0 )
					offset += 3;
				else if ( ( value & 0xF8 ) == 0xF0 )
					offset += 4;
			}

			if constexpr ( TE == TextEncoding::UTF16 )
			{
				if ( ( value & 0xFC00 ) == 0xD800 )
					offset += 2;
				else
					offset += 1;
			}

			ret++;
		}

		return ret;
	}

	template<TextEncoding TE>
	SizeType GetUTFElementCountFromCodePoints(const CodePoint* codepoints, SizeType count)
	{
		SizeType ret = 0;
		for (SizeType index = 0; index < count; index++)
		{
			CodePoint codepoint = codepoints[index];

			if constexpr ( TE == TextEncoding::UTF8 )
			{
				if ( codepoint <= 0x7F )
					ret += 1;
				else if ( codepoint <= 0x7FF ) // 5 + 6(uses 11 bits to store)
					ret += 2;
				else if ( codepoint <= 0xFFFF ) // 4 + 6 + 6
					ret += 3;
				else // 3 + 6 + 6 + 6
					ret += 4;
			}

			if constexpr ( TE == TextEncoding::UTF16 )
			{
				if ( codepoint <= 0xFFFF )
					ret += 1;
				else
					ret += 2;
			}
		}

		return ret;
	}

	template<TextEncoding TE, typename T>
	SizeType FromUTF(CodePoint* outputResult, const T* inUTFSequence)
	{
		SizeType ret = 0;

		CodePoint codepoint = 0;

		const T* c0 = inUTFSequence + 0;
		const T* c1 = inUTFSequence + 1;
		const T* c2 = inUTFSequence + 2;
		const T* c3 = inUTFSequence + 3;

		if constexpr ( TE == TextEncoding::UTF8 )
		{
			if ( ( *c0 & 0x80 ) == 0x00 )
			{
				codepoint = *c0;

				ret = 1;
			}
			else if ( ( *c0 & 0xE0 ) == 0xC0 )
			{
				codepoint |= ( *c0 & 0x1F ) << 6;
				codepoint |= ( *c1 & 0x3F ) << 0;

				ret = 2;
			}
			else if ( ( *c0 & 0xF0 ) == 0xE0 )
			{
				codepoint |= ( *c0 & 0x0F ) << 12;
				codepoint |= ( *c1 & 0x3F ) <<  6;
				codepoint |= ( *c2 & 0x3F ) <<  0;

				ret = 3;
			}
			else if ( ( *c0 & 0xF8 ) == 0xF0 )
			{
				codepoint |= ( *c0 & 0x07 ) << 18;
				codepoint |= ( *c1 & 0x3F ) << 12;
				codepoint |= ( *c2 & 0x3F ) <<  6;
				codepoint |= ( *c3 & 0x3F ) <<  0;

				ret = 4;
			}
		}

		if constexpr ( TE == TextEncoding::UTF16 )
		{
			if ( ( *c0 & 0xFC00 ) == 0xD800 )
			{
				codepoint |= ( *c0 & 0x3FF ) << 10;
				codepoint |= ( *c1 & 0x3FF ) <<  0;

				codepoint += 0x10000;

				ret = 2;
			}
			else
			{
				codepoint = *c0;

				ret = 1;
			}
		}

		if (outputResult)
			*outputResult = codepoint;

		return ret;
	}

	template<TextEncoding TE, typename T>
	SizeType ToUTF(T* outputResult, CodePoint codepoint)
	{
		T* c0 = outputResult + 0;
		T* c1 = outputResult + 1;
		T* c2 = outputResult + 2;
		T* c3 = outputResult + 3;

		if constexpr ( TE == TextEncoding::UTF8 )
		{
			if ( codepoint <= 0x7F )
			{
				*c0 = codepoint;

				return 1;
			}
			else if ( codepoint <= 0x7FF )
			{
				*c0 = ( ( codepoint >> 6 ) & 0x1F ) | 0xC0;
				*c1 = ( ( codepoint >> 0 ) & 0x3F ) | 0x80;

				return 2;
			}
			else if ( codepoint <= 0xFFFF )
			{
				*c0 = ( ( codepoint >> 12 ) & 0x0F ) | 0xE0;
				*c1 = ( ( codepoint >>  6 ) & 0x3F ) | 0x80;
				*c2 = ( ( codepoint >>  0 ) & 0x3F ) | 0x80;

				return 3;
			}
			else if ( codepoint <= 0x10FFFF )
			{
				*c0 = ( ( codepoint >> 18 ) & 0x07 ) | 0xF0;
				*c1 = ( ( codepoint >> 12 ) & 0x3F ) | 0x80;
				*c2 = ( ( codepoint >>  6 ) & 0x3F ) | 0x80;
				*c3 = ( ( codepoint >>  0 ) & 0x3F ) | 0x80;

				return 4;
			}
		}

		if constexpr ( TE == TextEncoding::UTF16 )
		{
			if ( codepoint <= 0xFFFF )
			{
				*c0 = codepoint;

				return 1;
			}
			else if ( codepoint <= 0x10FFFF )
			{
				codepoint -= 0x10000;

				*c0 = ( ( codepoint >> 10 ) & 0x3FF ) | 0xD800;
				*c1 = ( ( codepoint >>  0 ) & 0x3FF ) | 0xDC00;

				return 2;
			}
		}

		return 0;
	}

#pragma endregion
}