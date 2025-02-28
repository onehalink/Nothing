#pragma once

#include "../Enum.h"
#include "../Type.h"

#include "Category.h"



namespace Engine::Iterator
{
	template<typename IteratorType>
	Void Advance(IteratorType& iterator, typename IteratorType::DistanceType distance)
	{
		if constexpr ( Enum::HasAll( IteratorType::Category, Category::Contiguous ) )
			iterator += distance;
		else
		{
			if constexpr ( Enum::HasAll( IteratorType::Category, Category::Forward ) )
				while ( distance-- > 0 ) ++iterator;

			if constexpr ( Enum::HasAll( IteratorType::Category, Category::Backward ) )
				while ( distance++ < 0 ) --iterator;
		}
	}
}