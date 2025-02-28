#pragma once

#include "Type.h"

#include "Template/TypesAreSame.h"



namespace Engine::Unicode
{
	enum class Encoding
	{
		UTF8,
		UTF16,
	};


	struct CodePointLimit
	{
		static constexpr Char32 Minimum = 0;
		static constexpr Char32 Maximum = 0x10FFFF;
	};


	template<Encoding E, typename T> SizeType GetEncodedLength(const T* inUTF8OrUTF16, SizeType count);
	template<Encoding E> SizeType GetDecodedLength(const Char32* inUTF32, SizeType count);

	/**
	* Convert UTF encoding sequence to a codepoint
	* 
	* @return Indicate how many UTF elements had been used
	*/
	template<Encoding E, typename T> SizeType FromUTF(Char32* output, const T* inUTF8OrUTF16Sequence);
	/**
	* Convert a codepoint to UTF encoding sequence
	* 
	* @return Indicate a codepoint could be converted to how many UTF elements
	*/
	template<Encoding E, typename T> SizeType ToUTF(T* output, Char32 codepoint);


#pragma region Details

	template<Encoding E, typename T>
	SizeType GetEncodedLength(const T* inUTF8OrUTF16, SizeType count)
	{
		static_assert(
			( E == Encoding::UTF8	&& TypesAreSame<T,  Char8>::Value ) ||
			( E == Encoding::UTF16	&& TypesAreSame<T, Char16>::Value )
			);


		SizeType result = 0;

		for (SizeType index = 0; index < count; )
		{
			T value = inUTF8OrUTF16[index];

			if constexpr ( E == Encoding::UTF8 )
			{
				if ( ( value & 0x80 ) == 0x00 )
					index += 1;
				else if ( ( value & 0xE0 ) == 0xC0 )
					index += 2;
				else if ( ( value & 0xF0 ) == 0xE0 )
					index += 3;
				else if ( ( value & 0xF8 ) == 0xF0 )
					index += 4;
			}

			if constexpr ( E == Encoding::UTF16 )
			{
				if ( ( value & 0xFC00 ) == 0xD800 )
					index += 2;
				else
					index += 1;
			}

			result++;
		}

		return result;
	}

	template<Encoding E>
	SizeType GetDecodedLength(const Char32* inUTF32, SizeType count)
	{
		SizeType result = 0;

		for (SizeType index = 0; index < count; index++)
		{
			Char32 codepoint = inUTF32[index];

			if constexpr ( E == Encoding::UTF8 )
			{
				if ( codepoint <= 0x7F )
					result += 1;
				else if ( codepoint <= 0x7FF )
					result += 2;
				else if ( codepoint <= 0xFFFF )
					result += 3;
				else
					result += 4;
			}

			if constexpr ( E == Encoding::UTF16 )
			{
				if ( codepoint <= 0xFFFF )
					result += 1;
				else
					result += 2;
			}
		}

		return result;
	}

	template<Encoding E, typename T>
	SizeType FromUTF(Char32* output, const T* inUTF8OrUTF16Sequence)
	{
		static_assert(
			( E == Encoding::UTF8	&& TypesAreSame<T,  Char8>::Value ) ||
			( E == Encoding::UTF16	&& TypesAreSame<T, Char16>::Value )
			);


		SizeType result = 0;

		Char32 codepoint = 0;

		const T* c0 = inUTF8OrUTF16Sequence + 0;
		const T* c1 = inUTF8OrUTF16Sequence + 1;
		const T* c2 = inUTF8OrUTF16Sequence + 2;
		const T* c3 = inUTF8OrUTF16Sequence + 3;

		if constexpr ( E == Encoding::UTF8 )
		{
			if ( ( *c0 & 0x80 ) == 0x00 )
			{
				codepoint = *c0;

				result = 1;
			}
			else if ( ( *c0 & 0xE0 ) == 0xC0 )
			{
				codepoint |= ( *c0 & 0x1F ) << 6;
				codepoint |= ( *c1 & 0x3F ) << 0;

				result = 2;
			}
			else if ( ( *c0 & 0xF0 ) == 0xE0 )
			{
				codepoint |= ( *c0 & 0x0F ) << 12;
				codepoint |= ( *c1 & 0x3F ) <<  6;
				codepoint |= ( *c2 & 0x3F ) <<  0;

				result = 3;
			}
			else if ( ( *c0 & 0xF8 ) == 0xF0 )
			{
				codepoint |= ( *c0 & 0x07 ) << 18;
				codepoint |= ( *c1 & 0x3F ) << 12;
				codepoint |= ( *c2 & 0x3F ) <<  6;
				codepoint |= ( *c3 & 0x3F ) <<  0;

				result = 4;
			}
		}

		if constexpr ( E == Encoding::UTF16 )
		{
			if ( ( *c0 & 0xFC00 ) == 0xD800 )
			{
				codepoint |= ( *c0 & 0x3FF ) << 10;
				codepoint |= ( *c1 & 0x3FF ) <<  0;

				codepoint += 0x10000;

				result = 2;
			}
			else
			{
				codepoint = *c0;

				result = 1;
			}
		}

		if (output)
			*output = codepoint;

		return result;
	}

	template<Encoding E, typename T>
	SizeType ToUTF(T* output, Char32 codepoint)
	{
		static_assert(
			( E == Encoding::UTF8	&& TypesAreSame<T,  Char8>::Value ) ||
			( E == Encoding::UTF16	&& TypesAreSame<T, Char16>::Value )
			);


		T* c0 = output + 0;
		T* c1 = output + 1;
		T* c2 = output + 2;
		T* c3 = output + 3;

		if constexpr ( E == Encoding::UTF8 )
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

		if constexpr ( E == Encoding::UTF16 )
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