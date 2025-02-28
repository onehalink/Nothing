#pragma once

#include "StringBuilder.h"



namespace Engine
{
	/**
	* Example:
	* EscapeTo(outputResult, "Tab is \t and quote is \"") -> "Tab is \\t and quote is \\\""
	*/
	template<typename T> Void EscapeTo(StringBuilder<T>* outputResult, const T* rawString, Int32 length = -1);
	template<typename T> Void EscapeTo(StringBuilder<T>* outputResult, const String<T>& string);

	/**
	* Example:
	* QuoteEscapeTo(outputResult, "Tab is \t and quote is \"") -> "\"Tab is \\t and quote is \\\"\""
	*/
	template<typename T> Void QuoteEscapeTo(StringBuilder<T>* outputResult, const T* rawString, Int32 length = -1);
	template<typename T> Void QuoteEscapeTo(StringBuilder<T>* outputResult, const String<T>& string);


#pragma region Details

#define SELECT_STRING_LITERAL(outputResult, ValueType, Literal)		\
do{																	\
	if constexpr( TypesAreSame<ValueType, Char8>::Value )			\
		outputResult = Literal;										\
																	\
	if constexpr( TypesAreSame<ValueType, Char16>::Value )			\
		outputResult = L ## Literal;								\
																	\
	if constexpr( TypesAreSame<ValueType, Char32>::Value )			\
		outputResult = U ## Literal;								\
}while(false)


	template<typename T>
	Void EscapeTo(StringBuilder<T>* outputResult, const T* rawString, Int32 length)
	{
		if ( length == -1 )
			length = StringLength(rawString);

		for (SizeType index = 0; index < length; index++)
		{
			T value = rawString[index];

			switch (value)
			{
			case '\f':
			{
				const T* value;
				SELECT_STRING_LITERAL(value, T, "\\f");

				outputResult->Append(value);
			}
				break;
			case '\n':
			{
				const T* value;
				SELECT_STRING_LITERAL(value, T, "\\n");

				outputResult->Append(value);
			}
				break;
			case '\r':
			{
				const T* value;
				SELECT_STRING_LITERAL(value, T, "\\r");

				outputResult->Append(value);
			}
				break;
			case '\t':
			{
				const T* value;
				SELECT_STRING_LITERAL(value, T, "\\t");

				outputResult->Append(value);
			}
				break;
			case '\v':
			{
				const T* value;
				SELECT_STRING_LITERAL(value, T, "\\v");

				outputResult->Append(value);
			}
				break;

			case '\"':
			{
				const T* value;
				SELECT_STRING_LITERAL(value, T, "\\\"");

				outputResult->Append(value);
			}
				break;
			case '\'':
			{
				const T* value;
				SELECT_STRING_LITERAL(value, T, "\\\'");

				outputResult->Append(value);
			}
				break;
			case '\\':
			{
				const T* value;
				SELECT_STRING_LITERAL(value, T, "\\\\");

				outputResult->Append(value);
			}
				break;

			default:
				outputResult->Append( &value, 1 );
				break;
			}
		}
	}

	template<typename T>
	Void EscapeTo(StringBuilder<T>* outputResult, const String<T>& string)
	{
		EscapeTo( outputResult, string.GetBuffer(), string.GetCount() );
	}

	template<typename T>
	Void QuoteEscapeTo(StringBuilder<T>* outputResult, const T* rawString, Int32 length)
	{
		{
			const T* value;
			SELECT_STRING_LITERAL(value, T, "\"");

			outputResult->Append(value);
		}

		EscapeTo(outputResult, rawString, length);
		
		{
			const T* value;
			SELECT_STRING_LITERAL(value, T, "\"");

			outputResult->Append(value);
		}
	}

	template<typename T>
	Void QuoteEscapeTo(StringBuilder<T>* outputResult, const String<T>& string)
	{
		QuoteEscapeTo( outputResult, string.GetBuffer(), string.GetCount() );
	}


#undef SELECT_STRING_LITERAL

#pragma endregion
}