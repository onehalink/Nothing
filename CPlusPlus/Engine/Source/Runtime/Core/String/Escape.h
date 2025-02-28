#pragma once

#include "StringLiteral.h"
#include "StringBuilder.h"



namespace Engine
{
	/**
	* Example:
	* EscapeTo(outputResult, "Tab is \t and quote is \"") -> "Tab is \\t and quote is \\\""
	*/
	template<typename T> Void EscapeTo(StringBuilder<T>* outputResult, const T* string, Int32 length = -1);
	template<typename T> Void EscapeTo(StringBuilder<T>* outputResult, const String<T>& string);

	/**
	* Example:
	* QuoteEscapeTo(outputResult, "Tab is \t and quote is \"") -> "\"Tab is \\t and quote is \\\"\""
	*/
	template<typename T> Void QuoteEscapeTo(StringBuilder<T>* outputResult, const T* string, Int32 length = -1);
	template<typename T> Void QuoteEscapeTo(StringBuilder<T>* outputResult, const String<T>& string);


#pragma region Details

	template<typename T>
	Void EscapeTo(StringBuilder<T>* outputResult, const T* string, Int32 length)
	{
		if ( length == -1 )
			length = StringLength(string);

		for (SizeType index = 0; index < length; index++)
		{
			T value = string[index];

			switch (value)
			{
			case '\f': outputResult->Append( STRING_LITERAL(T, "\\f") ); break;
			case '\n': outputResult->Append( STRING_LITERAL(T, "\\n") ); break;
			case '\r': outputResult->Append( STRING_LITERAL(T, "\\r") ); break;
			case '\t': outputResult->Append( STRING_LITERAL(T, "\\t") ); break;
			case '\v': outputResult->Append( STRING_LITERAL(T, "\\v") ); break;

			case '\"': outputResult->Append( STRING_LITERAL(T, "\\\"") ); break;
			case '\'': outputResult->Append( STRING_LITERAL(T, "\\\'") ); break;
			case '\\': outputResult->Append( STRING_LITERAL(T, "\\\\") ); break;

			default: outputResult->Append(&value, 1); break;
			}
		}
	}

	template<typename T>
	Void EscapeTo(StringBuilder<T>* outputResult, const String<T>& string)
	{
		EscapeTo( outputResult, string.GetBuffer(), string.GetCount() );
	}

	template<typename T>
	Void QuoteEscapeTo(StringBuilder<T>* outputResult, const T* string, Int32 length)
	{
		outputResult->Append( STRING_LITERAL(T, '\"') );
		EscapeTo(outputResult, string, length);
		outputResult->Append( STRING_LITERAL(T, '\"') );
	}

	template<typename T>
	Void QuoteEscapeTo(StringBuilder<T>* outputResult, const String<T>& string)
	{
		QuoteEscapeTo( outputResult, string.GetBuffer(), string.GetCount() );
	}

#pragma endregion
}
