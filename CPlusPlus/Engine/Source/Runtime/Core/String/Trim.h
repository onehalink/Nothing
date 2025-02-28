#pragma once

#include "../AsciiSet.h"

#include "StringView.h"



namespace Engine
{
	// Trim the whitespace from both ends of the string
	template<typename T>
	StringView<T> Trim(StringView<T> view, Bool trimStart = true, Bool trimEnd = true)
	{
		using namespace PredefinedAsciiSet;


		SizeType startIndex = 0;
		if(trimStart)
			for(SizeType index = 0; index < view.GetCount(); ++index)
				if ( !Whitespaces.Contain( view[index] ) )
				{
					startIndex = index;

					break;
				}

		SizeType count;
		if (trimEnd)
		{
			for(Int32 index = view.GetCount() - 1; index > startIndex; --index)
				if ( !Whitespaces.Contain( view[index] ) )
				{
					count = ( index + 1 ) - startIndex;

					break;
				}
		}
		else
			count = view.GetCount() - startIndex; 

		return view.Slice(startIndex, count);
	}
}