#pragma once

#include "../CoreMinimal.h"

#include "../Iterator/Advance.h"
#include "../Iterator/Category.h"
#include "../Iterator/Distance.h"



namespace Engine::Algorithm
{
	template<typename IteratorType, typename BinaryPredicateType>
	IteratorType BinarySearch(IteratorType first, IteratorType last, typename IteratorType::ElementType target, BinaryPredicateType Predicate)
	{
		static_assert( Enum::HasAll( IteratorType::Category, Iterator::Category::Forward ) );


		while ( first != last )
		{
			IteratorType middle = first;
			Iterator::Advance( middle, Iterator::Distance(first, last) / 2 );

			typename IteratorType::ElementType& element = *middle;
			if ( element == target )
			{
				return middle;
			}
			else if ( Predicate(element, target) )
			{
				first = middle;

				++first;
			}
			else
			{
				last = middle;
			}
		}

		return { InPlace() };
	}
}