#pragma once

#include "../Buffer.h"

#include "StringView.h"



namespace Engine
{
	template<typename T>
	Bool Contain(StringView<T> view, StringView<T> search, SizeType* outputMatchIndex = nullptr)
	{
		if ( view.GetCount() < search.GetCount() )
			return false;

		SizeType end = view.GetCount() - search.GetCount() + 1;
		for (SizeType index = 0; index < end; ++index)
			if ( MemoryEqual( view.GetBuffer() + index, search.GetBuffer(), search.GetCount() ) )
			{
				if (outputMatchIndex)
					*outputMatchIndex = index;

				return true;
			}

		return false;
	}
}
