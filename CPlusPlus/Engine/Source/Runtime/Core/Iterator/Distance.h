#pragma once

#include "../Enum.h"

#include "Category.h"



namespace Engine::Iterator
{
	template<typename IteratorType>
	typename IteratorType::DistanceType Distance(IteratorType first, IteratorType last)
	{
		if constexpr ( Enum::HasAll( IteratorType::Category, Category::Contiguous ) )
			return last - first;
		else
		{
			typename IteratorType::DistanceType result = 0;
			while ( first++ != last ) ++result;

			return result;
		}
	}
}