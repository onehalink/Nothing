#pragma once

#include "../Base.h"

#include "Forward.h"



namespace Engine
{
	// &&, || and !

	template<typename T = Void>	struct LogicalAnd;
	template<>					struct LogicalAnd<Void>;

	template<typename T = Void>	struct LogicalOr;
	template<>					struct LogicalOr<Void>;

	template<typename T = Void>	struct LogicalNot;
	template<>					struct LogicalNot<Void>;


	// &, |, ~ and ^

	template<typename T = Void>	struct BitwiseAnd;
	template<>					struct BitwiseAnd<Void>;

	template<typename T = Void>	struct BitwiseOr;
	template<>					struct BitwiseOr<Void>;

	template<typename T = Void>	struct BitwiseNot;
	template<>					struct BitwiseNot<Void>;

	template<typename T = Void>	struct BitwiseXOr;
	template<>					struct BitwiseXOr<Void>;


	// +, -, *, / and %

	template<typename T = Void>	struct BinaryPlus;
	template<>					struct BinaryPlus<Void>;

	template<typename T = Void>	struct BinaryMinus;
	template<>					struct BinaryMinus<Void>;

	template<typename T = Void>	struct BinaryMultiply;
	template<>					struct BinaryMultiply<Void>;

	template<typename T = Void>	struct BinaryDivide;
	template<>					struct BinaryDivide<Void>;

	template<typename T = Void>	struct BinaryModulo;
	template<>					struct BinaryModulo<Void>;


	// <, <=, ==, > and >=

	template<typename T = Void>	struct LessThan;
	template<>					struct LessThan<Void>;

	template<typename T = Void>	struct LessOrEqual;
	template<>					struct LessOrEqual<Void>;

	template<typename T = Void>	struct EqualTo;
	template<>					struct EqualTo<Void>;

	template<typename T = Void>	struct GreaterThan;
	template<>					struct GreaterThan<Void>;

	template<typename T = Void>	struct GreaterOrEqual;
	template<>					struct GreaterOrEqual<Void>;


#pragma region Details

	template<typename T>
	struct LogicalAnd
	{
		constexpr Bool operator()(const T& first, const T& second) const
		{
			return first && second;
		}
	};

	template<>
	struct LogicalAnd<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) && Forward<Second>(second) )
		{
			return Forward<First>(first) && Forward<Second>(second);
		}
	};

	template<typename T>
	struct LogicalOr
	{
		constexpr Bool operator()(const T& first, const T& second) const
		{
			return first || second;
		}
	};

	template<>
	struct LogicalOr<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) || Forward<Second>(second) )
		{
			return Forward<First>(first) || Forward<Second>(second);
		}
	};

	template<typename T>
	struct LogicalNot
	{
		constexpr Bool operator()(const T& value) const
		{
			return !value;
		}
	};

	template<>
	struct LogicalNot<Void>
	{
		template<typename T, typename Second>
		constexpr auto operator()(T&& value, Second&& second) -> decltype( !Forward<T>(value) )
		{
			return !Forward<T>(value);
		}
	};

	template<typename T>
	struct BitwiseAnd
	{
		constexpr T operator()(const T& first, const T& second) const
		{
			return first & second;
		}
	};

	template<>
	struct BitwiseAnd<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) & Forward<Second>(second) )
		{
			return Forward<First>(first) & Forward<Second>(second);
		}
	};

	template<typename T>
	struct BitwiseOr
	{
		constexpr T operator()(const T& first, const T& second) const
		{
			return first | second;
		}
	};

	template<>
	struct BitwiseOr<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) | Forward<Second>(second) )
		{
			return Forward<First>(first) | Forward<Second>(second);
		}
	};

	template<typename T>
	struct BitwiseNot
	{
		template<typename T, typename Second>
		constexpr T operator()(const T& value) const
		{
			return ~value;
		}
	};

	template<>
	struct BitwiseNot<Void>
	{
		template<typename T>
		constexpr auto operator()(T&& value) -> decltype( ~Forward<T>(value) )
		{
			return ~Forward<T>(value);
		}
	};

	template<typename T>
	struct BitwiseXOr
	{
		constexpr T operator()(const T& first, const T& second) const
		{
			return first ^ second;
		}
	};

	template<>
	struct BitwiseXOr<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) ^ Forward<Second>(second) )
		{
			return Forward<First>(first) ^ Forward<Second>(second);
		}
	};

	template<typename T>
	struct BinaryPlus
	{
		constexpr T operator()(const T& first, const T& second) const
		{
			return first + second;
		}
	};

	template<>
	struct BinaryPlus<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) + Forward<Second>(second) )
		{
			return Forward<First>(first) + Forward<Second>(second);
		}
	};

	template<typename T>
	struct BinaryMinus
	{
		constexpr T operator()(const T& first, const T& second) const
		{
			return first - second;
		}
	};

	template<>
	struct BinaryMinus<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) - Forward<Second>(second) )
		{
			return Forward<First>(first) - Forward<Second>(second);
		}
	};

	template<typename T>
	struct BinaryMultiply
	{
		constexpr T operator()(const T& first, const T& second) const
		{
			return first * second;
		}
	};

	template<>
	struct BinaryMultiply<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) * Forward<Second>(second) )
		{
			return Forward<First>(first) * Forward<Second>(second);
		}
	};

	template<typename T>
	struct BinaryDivide
	{
		constexpr T operator()(const T& first, const T& second) const
		{
			return first / second;
		}
	};

	template<>
	struct BinaryDivide<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) / Forward<Second>(second) )
		{
			return Forward<First>(first) / Forward<Second>(second);
		}
	};

	template<typename T>
	struct BinaryModulo
	{
		constexpr T operator()(const T& first, const T& second) const
		{
			return first % second;
		}
	};

	template<>
	struct BinaryModulo<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) % Forward<Second>(second) )
		{
			return Forward<First>(first) % Forward<Second>(second);
		}
	};

	template<typename T>
	struct LessThan
	{
		constexpr Bool operator()(const T& first, const T& second) const
		{
			return first < second;
		}
	};

	template<>
	struct LessThan<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) < Forward<Second>(second) )
		{
			return Forward<First>(first) < Forward<Second>(second);
		}
	};

	template<typename T>
	struct LessOrEqual
	{
		constexpr Bool operator()(const T& first, const T& second) const
		{
			return first <= second;
		}
	};

	template<>
	struct LessOrEqual<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) <= Forward<Second>(second) )
		{
			return Forward<First>(first) <= Forward<Second>(second);
		}
	};

	template<typename T>
	struct EqualTo
	{
		constexpr Bool operator()(const T& first, const T& second) const
		{
			return first == second;
		}
	};

	template<>
	struct EqualTo<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) == Forward<Second>(second) )
		{
			return Forward<First>(first) == Forward<Second>(second);
		}
	};

	template<typename T>
	struct GreaterThan
	{
		constexpr Bool operator()(const T& first, const T& second) const
		{
			return first > second;
		}
	};

	template<>
	struct GreaterThan<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) > Forward<Second>(second) )
		{
			return Forward<First>(first) > Forward<Second>(second);
		}
	};

	template<typename T>
	struct GreaterOrEqual
	{
		constexpr Bool operator()(const T& first, const T& second) const
		{
			return first >= second;
		}
	};

	template<>
	struct GreaterOrEqual<Void>
	{
		template<typename First, typename Second>
		constexpr auto operator()(First&& first, Second&& second) -> decltype( Forward<First>(first) >= Forward<Second>(second) )
		{
			return Forward<First>(first) >= Forward<Second>(second);
		}
	};

#pragma endregion
}