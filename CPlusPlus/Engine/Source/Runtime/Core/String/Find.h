#pragma once

#include "../Buffer.h"

#include "StringView.h"



namespace Engine
{
	template<typename T> Int32 FindFirst(StringView<T> view, StringView<T> search);
	template<typename T> Int32 FindLast(StringView<T> view, StringView<T> search);

	template<typename T> Int32 FindFirstOfAny(StringView<T> view, ReadOnlySpan<StringView<T>> search);
	template<typename T> Int32 FindLastOfAny(StringView<T> view, ReadOnlySpan<StringView<T>> search);


	template<typename T> Int32 FindFirstChar(StringView<T> view, T search);
	template<typename T> Int32 FindLastChar(StringView<T> view, T search);

	template<typename T> Int32 FindFirstOfAnyChar(StringView<T> view, ReadOnlySpan<T> search);
	template<typename T> Int32 FindLastOfAnyChar(StringView<T> view, ReadOnlySpan<T> search);


#pragma region Details

	template<typename T>
	Int32 FindFirst(StringView<T> view, StringView<T> search)
	{
		return FindFirstOfAny( view, { &search, 1 } );
	}

	template<typename T>
	Int32 FindLast(StringView<T> view, StringView<T> search)
	{
		return FindLastOfAny( view, { &search, 1 } );
	}

	template<typename T>
	Int32 FindFirstOfAny(StringView<T> view, ReadOnlySpan<StringView<T>> search)
	{
		for(SizeType index = 0; index < view.GetCount(); ++index)
			for (auto selected : search)
			{
				if ( view.GetCount() - index < selected.GetCount() )
					continue;

				if ( MemoryEqual( view.GetBuffer() + index, selected.GetBuffer(), selected.GetCount() ) )
					return index;
			}

		return -1;
	}

	template<typename T>
	Int32 FindLastOfAny(StringView<T> view, ReadOnlySpan<StringView<T>> search)
	{
		for(Int32 count = view.GetCount(); count >= 0; --count)
			for (auto selected : search)
			{
				if ( count < selected.GetCount() )
					continue;

				SizeType index = count - search.GetCount();
				if ( MemoryEqual( view.GetBuffer() + index, selected.GetBuffer(), selected.GetCount() ) )
					return index;
			}

		return -1;
	}

	template<typename T>
	Int32 FindFirstChar(StringView<T> view, T search)
	{
		return FindFirstOfAnyChar( view, { &search, 1 } );
	}

	template<typename T>
	Int32 FindLastChar(StringView<T> view, T search)
	{
		return FindLastOfAnyChar( view, { &search, 1 } );
	}

	template<typename T>
	Int32 FindFirstOfAnyChar(StringView<T> view, ReadOnlySpan<T> search)
	{
		for (SizeType index = 0; index < view.GetCount(); index++)
			for (auto selected : search)
				if ( selected == view[index] )
					return index;

		return -1;
	}

	template<typename T>
	Int32 FindLastOfAnyChar(StringView<T> view, ReadOnlySpan<T> search)
	{
		for (Int32 index = view.GetCount() - 1; index >= 0; --index)
			for (auto selected : search)
				if ( selected == view[index] )
					return index;

		return -1;
	}

#pragma endregion
}