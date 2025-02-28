#pragma once

#include "../Buffer.h"

#include "StringView.h"



namespace Engine
{
	template<typename T> Bool StartWith(StringView<T> view, T search);
	template<typename T> Bool StartWith(StringView<T> view, StringView<T> search);

	template<typename T> Bool EndWith(StringView<T> view, T search);
	template<typename T> Bool EndWith(StringView<T> view, StringView<T> search);


#pragma region Details

	template<typename T>
	Bool StartWith(StringView<T> view, T search)
	{
		return StartWith( view, { &search, 1 } );
	}

	template<typename T>
	Bool StartWith(StringView<T> view, StringView<T> search)
	{
		if ( view.GetCount() < search.GetCount() )
			return false;

		return MemoryEqual( view.GetBuffer(), search.GetBuffer(), search.GetCount() );
	}

	template<typename T>
	Bool EndWith(StringView<T> view, T search)
	{
		return EndWith( view, { &search, 1 } );
	}

	template<typename T>
	Bool EndWith(StringView<T> view, StringView<T> search)
	{
		if ( view.GetCount() < search.GetCount() )
			return false;

		return MemoryEqual( view.GetBuffer() + view.GetCount() - search.GetCount(), search.GetBuffer(), search.GetCount() );
	}

#pragma endregion
}