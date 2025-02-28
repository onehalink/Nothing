#pragma once

#include "../Buffer.h"

#include "String.h"
#include "StringView.h"



namespace Engine
{
	template<typename T> String<T> Insert(StringView<T> view, SizeType index, T value);
	template<typename T> String<T> Insert(StringView<T> view, SizeType index, StringView<T> value);


#pragma region Details

	template<typename T>
	String<T> Insert(StringView<T> view, SizeType index, T value)
	{
		return Insert( view, index, { &value, 1 } );
	}

	template<typename T>
	String<T> Insert(StringView<T> view, SizeType index, StringView<T> value)
	{
		String<T> result( view.GetCount() + value.GetCount() );

		MemoryCopy( result.GetBuffer(),								view.GetBuffer(),			index					);
		MemoryCopy( result.GetBuffer() + index,						value.GetBuffer(),			value.GetCount()		);
		MemoryCopy( result.GetBuffer() + index + value.GetCount(),	view.GetBuffer() + index,	view.GetCount() - index	);

		return result;
	}

#pragma endregion
}