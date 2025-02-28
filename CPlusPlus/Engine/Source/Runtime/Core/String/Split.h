#pragma once

#include "../Function.h"

#include "StringView.h"



namespace Engine
{
	template<typename T> Void Split(StringView<T> view, T delimiter, Action<StringView<T>> Visitor);
	template<typename T> Void Split(StringView<T> view, ReadOnlySpan<T> delimiters, Action<StringView<T>> Visitor);


#pragma region Details

	template<typename T>
	Void Split(StringView<T> view, T delimiter, Action<StringView<T>> Visitor)
	{
		Split( view, { &delimiter, 1 }, Visitor );
	}

	template<typename T>
	Void Split(StringView<T> view, ReadOnlySpan<T> delimiters, Action<StringView<T>> Visitor)
	{
		SizeType startIndex = 0;
		for (SizeType index = 0; index < view.GetCount(); ++index)
			for (auto delimiter : delimiters)
				if ( delimiter == view[index] )
				{
					Visitor( view.Slice( startIndex, index - startIndex ) );

					startIndex = index + 1;
				}

		Visitor( view.Slice(startIndex) );
	}

#pragma endregion
}