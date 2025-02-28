#pragma once

#include "Forward.h"
#include "ParameterPack.h"



namespace Engine
{
	template<typename ...Types>
	struct Tuple;


	template<>
	struct Tuple<>
	{

	};


	template<typename First, typename ...Types>
	struct Tuple<First, Types ...> : Tuple<Types ...>
	{
		using Base		= Tuple<Types ...>;
		using ThisType	= Tuple<First, Types ...>;


		First value;


		Tuple() = default;
		template<typename OtherFirst, typename ...OtherTypes>
		Tuple(OtherFirst&& value, OtherTypes&&... parameters)
			: value( Forward<OtherFirst>(value) ), Base( Forward<OtherTypes>(parameters)... )
		{

		}


		template<SizeType Index> typename ParameterPack::Nth<Index, First, Types ...>::Type& Get()
		{
			if constexpr ( Index == 0 )
				return value;
			else
				return static_cast<Base*>(this)->Get<Index - 1>();
		}
		template<SizeType Index> const typename ParameterPack::Nth<Index, First, Types ...>::Type& Get() const
		{
			return const_cast<ThisType*>(this)->template Get<Index>();
		}
		template<SizeType ...Indices> Tuple<typename ParameterPack::Nth<Indices, First, Types ...>::Type ...> Swizzle() const
		{
			return { Get<Indices>()... };
		}
	};
}