#pragma once

#include "../AsciiSet.h"
#include "../Char.h"
#include "../CoreMinimal.h"
#include "../Parse.h"
#include "../Result.h"

#include "../Container/DynamicArray.h"
#include "../Container/Stack.h"



namespace Engine::SimpleArithmeticExpression
{
	/**
	* Supported operators: +, -, *, /, ^(exponent)
	*
	* Example:
	* Evaluate("1 * (2 +3) * 4 + 5 / 10^(8 - 6)") -> 20.05
	*/
	template<typename ValueType, typename CharType> Result<ValueType> Evaluate(const CharType* text);


#pragma region Details

	struct Operator
	{
		Char8 opCode;
		UInt8 precedence;
	};


	template<typename T>
	struct Token
	{
		enum class Type
		{
			Oprand,
			Operator,
		};


		Type type;
		union
		{
			T			oprand;
			Operator	op;
		};


		Token() = default;
		Token(T oprand)			: type( Type::Oprand	), oprand(oprand)	{}
		Token(Operator op)		: type( Type::Operator	), op(op)			{}
	};


	const Operator PredefinedOperators[] =
	{
		{ '+', 1 },
		{ '-', 1 },
		{ '*', 2 },
		{ '/', 2 },
		{ '^', 3 },
		{ '(', 0 },
		{ ')', 0 },
	};


	template<typename T>
	T Calculate(Operator op, T leftHandSide, T rightHandSide)
	{
		switch ( op.opCode )
		{
		case '+':
			return leftHandSide + rightHandSide;
		case '-':
			return leftHandSide - rightHandSide;
		case '*':
			return leftHandSide * rightHandSide;
		case '/':
			return leftHandSide / rightHandSide;
		case '^':
			return Power(leftHandSide, rightHandSide);
		default:
			ASSERT(false);
			return T();
		}
	}

	template<typename ValueType, typename CharType>
	Result<ValueType> Evaluate(const CharType* text)
	{
		static_assert( IsChar<CharType>::Value );
		static_assert( IsArithmetic<ValueType>::Value );


		using Token = Token<ValueType>;


		DynamicArray<Token> tokens;
		{
			using namespace Char;


			while ( *text != '\0' )
			{
				text = PredefinedAsciiSet::Whitespaces.Skip(text);

				if ( IsDecimalDigit( *text ) )
				{
					if ( auto result = Parse::Value<ValueType>(text) )
						tokens.Add( result.GetValue() );

					// skip oprand
					++text;
					while ( IsDecimalDigit( *text ) ) ++text;

					continue;
				}

				for (auto op : PredefinedOperators)
					if ( *text == op.opCode )
					{
						tokens.Add(op);

						break;
					}

				// skip operator or advance
				++text;
			}
		}

		// test input
		{
			SizeType oprandCount = 0;
			SizeType operatorCount = 0;
			SizeType leftBracketCount = 0;
			SizeType rightBracketCount = 0;

			for(auto& token : tokens)
				switch ( token.type )
				{
				case Token::Type::Oprand:
					++oprandCount;
					break;
				case Token::Type::Operator:
					if ( token.op.opCode == '(' )
					{
						++leftBracketCount;
						break;
					}
					if ( token.op.opCode == ')' )
					{
						++rightBracketCount;
						break;
					}

					++operatorCount;
					break;
				}

			if (
				oprandCount != operatorCount + 1 ||
				leftBracketCount != rightBracketCount
				)
				return { InPlaceIndex<0>(), "Invalid input" };
		}

		DynamicArray<Token> output( tokens.GetCount() );
		Stack<Token> operatorStack;

		for (Token token : tokens)
		{
			if ( token.type == Token::Type::Oprand )
				output.Add(token);

			if ( token.type == Token::Type::Operator )
			{
				if ( token.op.opCode == '(' )
				{
					operatorStack.Push(token);

					continue;
				}

				if ( token.op.opCode == ')' )
				{
					while (
						!operatorStack.IsEmpty() &&
						operatorStack.Top().op.opCode != '('
						)
						output.Add( operatorStack.Pop() );

					// '(' not found
					if ( operatorStack.IsEmpty() )
						return { InPlaceIndex<0>(), "Left bracket not found" };

					// '(' drop
					operatorStack.Pop();

					continue;
				}

				while (
					!operatorStack.IsEmpty() &&
					operatorStack.Top().op.precedence >= token.op.precedence
					)
					output.Add( operatorStack.Pop() );

				operatorStack.Push(token);
			}
		}

		for (auto op : operatorStack)
			output.Add(op);

		Stack<ValueType> resultStack;
		for (Token token : output)
		{
			if ( token.type == Token::Type::Oprand )
				resultStack.Push( token.oprand );

			if ( token.type == Token::Type::Operator )
			{
				if ( resultStack.GetCount() < 2 )
					return { InPlaceIndex<0>(), "Oprands are less than 2" };

				ValueType b = resultStack.Pop();
				ValueType a = resultStack.Pop();

				resultStack.Push( Calculate( token.op, a, b ) );
			}
		}

		return { InPlaceIndex<1>(), resultStack.Top() };
	}

#pragma endregion
}