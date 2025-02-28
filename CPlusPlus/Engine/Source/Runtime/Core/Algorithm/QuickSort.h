#pragma once

#include "../CoreMinimal.h"

#include "../Iterator/Category.h"



namespace Engine::Algorithm
{
	template<typename IteratorType, typename BinaryPredicateType>
	Void QuickSort(IteratorType first, IteratorType last, BinaryPredicateType Predicate);


#pragma region Details

	namespace Private
	{
		template<typename IteratorType, typename BinaryPredicateType>
		IteratorType Partition(IteratorType first, IteratorType last, BinaryPredicateType Predicate)
		{
			IteratorType						temporary		= last;
			typename IteratorType::ElementType&	pivotElement	= *--temporary;

			IteratorType pivot = first;

			for (IteratorType iterator = first; iterator != last; ++iterator)
				if ( Predicate( *iterator, pivotElement ) )
				{
					Swap( &*iterator, &*pivot );

					++pivot;
				}

			Swap( &*pivot, &pivotElement );

			return pivot;
		}
	}


	template<typename IteratorType, typename BinaryPredicateType>
	Void QuickSort(IteratorType first, IteratorType last, BinaryPredicateType Predicate)
	{
		static_assert( Enum::HasAll( IteratorType::Category, Iterator::Category::Bidirectional ) );


		if ( first == last )
			return;

		IteratorType pivot = Private::Partition(first, last, Predicate);

		QuickSort( first,	pivot,	Predicate );
		QuickSort( ++pivot, last,	Predicate );
	}

#pragma endregion
}