#pragma once

#include "../Buffer.h"

#include "String.h"
#include "StringView.h"



namespace Engine
{
	// Returns a new string in which a specified number of characters from the current string are deleted
	template<typename T> String<T> Remove(StringView<T> view, SizeType startIndex);
	template<typename T> String<T> Remove(StringView<T> view, SizeType startIndex, SizeType count);


#pragma region Details

	template<typename T>
	String<T> Remove(StringView<T> view, SizeType startIndex)
	{
		return Remove( view, startIndex, view.GetCount() - startIndex );
	}

	template<typename T>
	String<T> Remove(StringView<T> view, SizeType startIndex, SizeType count)
	{
		String<T> result( view.GetCount() - count );

		MemoryCopy( result.GetBuffer(),					view.GetBuffer(),			startIndex					);
		SizeType advance = startIndex + count;
		MemoryCopy( result.GetBuffer() + startIndex,	view.GetBuffer() + advance,	view.GetCount() - advance	);

		return result;
	}

#pragma endregion
}