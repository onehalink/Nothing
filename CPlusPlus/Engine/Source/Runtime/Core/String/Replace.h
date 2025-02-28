#pragma once

#include "Contain.h"
#include "String.h"
#include "StringBuilder.h"
#include "StringView.h"



namespace Engine
{
	// Replaces all instances of oldValue with newValue

	template<typename T> String<T> Replace(StringView<T> view, T oldValue, T newValue);
	template<typename T> String<T> Replace(StringView<T> view, StringView<T> oldValue, StringView<T> newValue);


#pragma region Details

	template<typename T>
	String<T> Replace(StringView<T> view, T oldValue, T newValue)
	{
		return Replace( view, { &oldValue, 1 }, { &newValue, 1 } );
	}

	template<typename T>
	String<T> Replace(StringView<T> view, StringView<T> oldValue, StringView<T> newValue)
	{
		StringBuilder<T> builder;
		do
		{
			SizeType matchIndex;
			if ( !Contain( view, oldValue, &matchIndex ) )
			{
				if ( builder.IsEmpty() )
					return view;

				return builder.Append(view).ToString();
			}

			builder.Append( view.Slice(0, matchIndex) ).Append(newValue);

			view = view.Slice( matchIndex + oldValue.GetCount() );

		} while (true);
	}

#pragma endregion
}