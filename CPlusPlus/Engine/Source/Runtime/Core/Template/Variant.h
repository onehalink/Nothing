#pragma once

#include "SelectNthFromParameterPack.h"



namespace Engine
{
	template<typename ...Ts>
	struct Variant;


	template<>
	struct Variant<>
	{

	};


	template<typename First, typename ...Ts>
	struct Variant<First, Ts ...>
	{
		union
		{
			First			head;
			Variant<Ts ...> tail;
		};


		First& Get();
	};


	template<SizeType Index, typename ...Ts>
	typename SelectNthFromParameterPack<Index, Ts ...>::Type Visit(Variant<Ts ...>& variant);


#pragma region Details

	template<typename First, typename ...Ts>
	First& Variant<First, Ts...>::Get()
	{
		return head;
	}

	template<SizeType Index, typename ...Ts>
	typename SelectNthFromParameterPack<Index, Ts...>::Type Visit(Variant<Ts...>& variant)
	{
		static_assert( Index < sizeof...(Ts) );
		static_assert( Index < 64 );


		if constexpr ( Index == 0 )
			return variant.Get();
		else if constexpr ( Index == 1 )
			return variant.tail.Get();
		else if constexpr ( Index == 2 )
			return variant.tail.tail.Get();
		else if constexpr ( Index == 3 )
			return variant.tail.tail.tail.Get();
		else if constexpr ( Index == 4 )
			return variant.tail.tail.tail.tail.Get();
		else if constexpr ( Index == 5 )
			return variant.tail.tail.tail.tail.tail.Get();
		else if constexpr ( Index == 6 )
			return variant.tail.tail.tail.tail.tail.tail.Get();
		else if constexpr ( Index == 7 )
			return variant.tail.tail.tail.tail.tail.tail.tail.Get();
		else if constexpr ( Index < 16 )
			return Visit<Index - 8>( variant.tail.tail.tail.tail.tail.tail.tail.tail );
		else if constexpr ( Index < 32 )
			return Visit<Index - 16>( variant.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail );
		else if constexpr ( Index < 64 )
			return Visit<Index - 32>( variant.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail.tail );
	}

#pragma endregion
}