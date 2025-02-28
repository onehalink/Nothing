#pragma once

#include "../Base.h"

#include "Forward.h"



namespace Engine
{
	// >, >=, ==, <, <=

	template<typename T = Void>	struct Greater;
	template<>					struct Greater<Void>;

	template<typename T = Void>	struct GreaterEqual;
	template<>					struct GreaterEqual<Void>;

	template<typename T = Void> struct Equal;
	template<>					struct Equal<Void>;

	template<typename T = Void> struct Less;
	template<>					struct Less<Void>;

	template<typename T = Void> struct LessEqual;
	template<>					struct LessEqual<Void>;


#pragma region Details

	template<typename T>
	struct Greater
	{
		constexpr Bool operator()(const T& a, const T& b)
		{
			return a > b;
		}
	};

	template<>
	struct Greater<Void>
	{
		template<typename T, typename U>
		constexpr auto operator()(T&& a, U&& b) -> decltype( Forward<T>(a) > Forward<U>(b) )
		{
			return Forward<T>(a) > Forward<U>(b);
		}
	};

	template<typename T>
	struct GreaterEqual
	{
		constexpr Bool operator()(const T& a, const T& b)
		{
			return a >= b;
		}
	};

	template<>
	struct GreaterEqual<Void>
	{
		template<typename T, typename U>
		constexpr auto operator()(T&& a, U&& b) -> decltype( Forward<T>(a) >= Forward<U>(b) )
		{
			return Forward<T>(a) >= Forward<U>(b);
		}
	};

	template<typename T>
	struct Equal
	{
		constexpr Bool operator()(const T& a, const T& b)
		{
			return a == b;
		}
	};

	template<>
	struct Equal<Void>
	{
		template<typename T, typename U>
		constexpr auto operator()(T&& a, U&& b) -> decltype( Forward<T>(a) == Forward<U>(b) )
		{
			return Forward<T>(a) == Forward<U>(b);
		}
	};

	template<typename T>
	struct Less
	{
		constexpr Bool operator()(const T& a, const T& b)
		{
			return a < b;
		}
	};

	template<>
	struct Less<Void>
	{
		template<typename T, typename U>
		constexpr auto operator()(T&& a, U&& b) -> decltype( Forward<T>(a) < Forward<U>(b) )
		{
			return Forward<T>(a) < Forward<U>(b);
		}
	};

	template<typename T>
	struct LessEqual
	{
		constexpr Bool operator()(const T& a, const T& b)
		{
			return a <= b;
		}
	};

	template<>
	struct LessEqual<Void>
	{
		template<typename T, typename U>
		constexpr auto operator()(T&& a, U&& b) -> decltype( Forward<T>(a) <= Forward<U>(b) )
		{
			return Forward<T>(a) <= Forward<U>(b);
		}
	};

#pragma endregion
}