#pragma once

#include "Type.h"

#include "Template/IsChar.h"



namespace Engine
{
	/**
	* ASCII character bitset useful for fast and readable parsing
	* Entirely constexpr. Works with all strings
	*/
	class AsciiSet
	{
	public:
		template<SizeType Size, typename T> constexpr AsciiSet(const T(&charArray)[Size]);


		// Returns true if a character is part of the set
		template<typename T> constexpr Bool Contain(T value) const;
		// Find first character of string outside of set. Never returns null
		template<typename T> constexpr const T* Skip(const T* string) const;

		// Test if string contains any character in set
		template<typename T> constexpr Bool HasAny(const T* string) const;
		// Test if string contains any character outside of set
		template<typename T> constexpr Bool HasOnly(const T* string) const;


		// Create new set with specified character in it
		constexpr AsciiSet operator+(Char8 value) const;

		// Create new set containing only the characters that exist in both this and another specified set
		constexpr AsciiSet operator&(AsciiSet set) const;
		// Create new set containing the combination of this set and another
		constexpr AsciiSet operator|(AsciiSet set) const;
		// Create new set containing inverse set of characters - likely including null-terminator
		constexpr AsciiSet operator~() const;
	private:
		struct Bits
		{
			UInt64	low,
					high;
		};


		constexpr AsciiSet(UInt64 lowMask, UInt64 highMask);
		constexpr AsciiSet(Bits bits);


		static constexpr Void SetBit(Bits& bits, Char32 value);
		template<SizeType Size, typename T> static constexpr Bits StringToBits(const T(&charArray)[Size]);

		constexpr UInt64 TestBit(Char32 value) const;
	private:
		UInt64	lowMask,
				highMask;
	};


#pragma region Details

	template<SizeType Size, typename T>
	constexpr AsciiSet::AsciiSet(const T(&charArray)[Size])
		: AsciiSet( StringToBits(charArray) )
	{
		static_assert( IsChar<T>::Value );
	}

	template<typename T>
	constexpr Bool AsciiSet::Contain(T value) const
	{
		static_assert( IsChar<T>::Value );


		return TestBit(value);
	}

	template<typename T>
	constexpr const T* AsciiSet::Skip(const T* string) const
	{
		static_assert( IsChar<T>::Value );


		while ( Contain( *string ) )
			++string;

		return string;
	}

	template<typename T>
	constexpr Bool AsciiSet::HasAny(const T* string) const
	{
		static_assert( IsChar<T>::Value );


		while ( *string != '\0' )
		{
			if ( Contain( *string ) )
				return true;

			++string;
		}

		return false;
	}

	template<typename T>
	constexpr Bool AsciiSet::HasOnly(const T* string) const
	{
		static_assert( IsChar<T>::Value );


		return *Skip(string) == '\0';
	}

	constexpr AsciiSet AsciiSet::operator+(Char8 value) const
	{
		Bits bits = { lowMask, highMask };
		SetBit(bits, value);

		return bits;
	}

	constexpr AsciiSet AsciiSet::operator&(AsciiSet set) const
	{
		return AsciiSet( lowMask & set.lowMask, highMask & set.highMask );
	}

	constexpr AsciiSet AsciiSet::operator|(AsciiSet set) const
	{
		return AsciiSet( lowMask | set.lowMask, highMask | set.highMask );
	}

	constexpr AsciiSet AsciiSet::operator~() const
	{
		return AsciiSet( ~lowMask, ~highMask );
	}

	constexpr AsciiSet::AsciiSet(UInt64 lowMask, UInt64 highMask)
		: lowMask(lowMask), highMask(highMask)
	{

	}

	constexpr AsciiSet::AsciiSet(Bits bits)
		: lowMask( bits.low ), highMask( bits.high )
	{

	}

	constexpr Void AsciiSet::SetBit(Bits& bits, Char32 value)
	{
		UInt64 isLow	= static_cast<UInt64>(0) - ( value >> 6 == 0 );
		UInt64 isHigh	= static_cast<UInt64>(0) - ( value >> 6 == 1 );
		UInt64 bit		= static_cast<UInt64>(1) << ( value & 0x3F );

		bits.low	|= isLow	& bit;
		bits.high	|= isHigh	& bit;
	}

	template<SizeType Size, typename T>
	static constexpr AsciiSet::Bits AsciiSet::StringToBits(const T(&charArray)[Size])
	{
		Bits bits = { 0, 0 };
		for (SizeType index = 0; index < Size - 1; ++index)
			SetBit( bits, charArray[index] );

		return bits;
	}

	constexpr UInt64 AsciiSet::TestBit(Char32 value) const
	{
		UInt64 isLow	= static_cast<UInt64>(0) - ( value >> 6 == 0 );
		UInt64 isHight	= static_cast<UInt64>(0) - ( value >> 6 == 1 );
		UInt64 bit		= static_cast<UInt64>(1) << ( value & 0x3F );

		return ( isLow & bit & lowMask ) | ( isHight & bit & highMask );
	}

#pragma endregion
}


namespace Engine::PredefinedAsciiSet
{
	constexpr AsciiSet Slashes("/\\");
	constexpr AsciiSet Whitespaces(" \v\f\t\r\n");
}