#pragma once

#include "Type.h"

#include "Mathematics/Numeric.h"

#include "Template/IsChar.h"



namespace Engine::Char
{
	template<typename T> constexpr Bool IsBinaryDigit(T value);
	template<typename T> constexpr Bool IsOctalDigit(T value);
	template<typename T> constexpr Bool IsDecimalDigit(T value);
	template<typename T> constexpr Bool IsHexDigit(T value);

	template<typename T> constexpr Bool IsLower(T value);
	template<typename T> constexpr Bool IsUpper(T value);
	template<typename T> constexpr Bool IsLetter(T value);

	template<Bool CheckValue = true, typename T> constexpr T ToLower(T value);
	template<Bool CheckValue = true, typename T> constexpr T ToUpper(T value);


#pragma region Details

	template<typename T>
	constexpr Bool IsBinaryDigit(T value)
	{
		static_assert( IsChar<T>::Value );


		return value == '0' || value == '1';
	}

	template<typename T>
	constexpr Bool IsOctalDigit(T value)
	{
		static_assert( IsChar<T>::Value );


		return IsBetween(value, '0', '7');
	}

	template<typename T>
	constexpr Bool IsDecimalDigit(T value)
	{
		static_assert( IsChar<T>::Value );


		return IsBetween(value, '0', '9');
	}

	template<typename T>
	constexpr Bool IsHexDigit(T value)
	{
		static_assert( IsChar<T>::Value );


		return IsDecimalDigit(value) || IsBetween(value, 'A', 'F') || IsBetween(value, 'a', 'f');
	}

	template<typename T>
	constexpr Bool IsLower(T value)
	{
		static_assert( IsChar<T>::Value );


		return IsBetween(value, 'a', 'z');
	}

	template<typename T>
	constexpr Bool IsUpper(T value)
	{
		static_assert( IsChar<T>::Value );


		return IsBetween(value, 'A', 'Z');
	}

	template<typename T>
	constexpr Bool IsLetter(T value)
	{
		static_assert( IsChar<T>::Value );


		return IsLower(value) || IsUpper(value);
	}

	template<Bool CheckValue, typename T>
	constexpr T ToLower(T value)
	{
		static_assert( IsChar<T>::Value );


		if constexpr (CheckValue)
		{
			if ( IsUpper(value) )
				return value + 0x20;

			return value;
		}
		else
			return value + 0x20;
	}

	template<Bool CheckValue, typename T>
	constexpr T ToUpper(T value)
	{
		static_assert( IsChar<T>::Value );


		if constexpr (CheckValue)
		{
			if ( IsLower(value) )
				return value - 0x20;

			return value;
		}
		else
			return value - 0x20;
	}

#pragma endregion
}