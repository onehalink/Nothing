#pragma once

#include "../Function.h"

#include "StringView.h"



namespace Engine
{
	// Parse lines in the input string as terminated by any of CRLF, CR, LF
	template<typename T>
	Void ParseLines(StringView<T> view, Action<StringView<T>> Visitor)
	{
		SizeType startIndex = 0;
		for(SizeType index = 0; index < view.GetCount(); ++index)
			if (
				view[index] == '\n' ||
				view[index] == '\r'
				)
			{
				Visitor( view.Slice( startIndex, index - startIndex ) );

				startIndex = index + 1;

				if (
					index < view.GetCount() - 1 &&
					view[ index + 1 ] == '\n'
					)
				{
					startIndex++;

					index++;
				}
			}

		Visitor( view.Slice(startIndex) );
	}
}