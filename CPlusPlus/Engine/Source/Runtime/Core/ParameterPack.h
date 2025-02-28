#pragma once

#include "Forward.h"
#include "Type.h"

#include "Template/IntegralConstant.h"
#include "Template/TypesAreSame.h"



namespace Engine::ParameterPack
{
	/**
	* Selects the nth type from parameter pack
	*
	* @remark
	* Index must be less than sizeof...(Types)
	*/
	template<SizeType Index, typename ...Types>
	struct Nth;


	// Find the first index of LookupType from parameter pack
	template<typename LookupType, typename ...Types>
	struct TypeIndex;


	// The count of LookupType from parameter pack
	template<typename LookupType, typename ...Types>
	struct TypeCount : IntegralConstant<SizeType, ( ( TypesAreSame<LookupType, Types>::Value ? 1 : 0 ) + ... )> { };


	// Copy values to a pointer point to heap/stack memory from parameter pack
	template<typename T, typename First, typename ...Parameters> Void CopyTo(T* pointer, First&& value, Parameters&&... parameters);
	template<SizeType Index, typename First, typename ...Parameters> constexpr typename Nth<Index, First, Parameters...>::Type&& NthElement(First&& value, Parameters&&... parameters);


#pragma region Details

#pragma region Nth

	template<typename First, typename ...Types>
	struct Nth<0, First, Types ...>
	{
		using Type = First;
	};


	template<SizeType Index, typename First, typename ...Types>
	struct Nth<Index, First, Types ...>
	{
		using Type = typename Nth<Index - 1, Types ...>::Type;
	};

#pragma endregion


#pragma region TypeIndex

	template<SizeType InValue> using IndexConstant = IntegralConstant<SizeType, InValue>;


	template<SizeType Index, typename LookupType, typename ...Types>
	struct TypeIndexHelper : IndexConstant<-1>
	{

	};


	template<SizeType Index, typename T, typename ...Types>
	struct TypeIndexHelper<Index, T, T, Types ...> : IndexConstant<Index>
	{

	};


	template<Int32 Index, typename LookupType, typename First, typename ...Types>
	struct TypeIndexHelper<Index, LookupType, First, Types ...> : IndexConstant<TypeIndexHelper<Index + 1, LookupType, Types ...>::Value>
	{

	};


	template<typename LookupType, typename ...Types>
	struct TypeIndex : IndexConstant<TypeIndexHelper<0, LookupType, Types ...>::Value>
	{

	};

#pragma endregion


	template<typename T, typename First, typename ...Parameters>
	Void CopyTo(T* pointer, First&& value, Parameters&&... parameters)
	{
		*pointer = Forward<First>(value);

		if constexpr ( sizeof...(parameters) > 0 )
			CopyTo( pointer + 1, Forward<Parameters>(parameters)... );
	}

	template<SizeType Index, typename First, typename ...Parameters>
	constexpr typename Nth<Index, First, Parameters...>::Type&& NthElement(First&& value, Parameters&&... parameters)
	{
		if constexpr ( Index == 0 )
			return Forward<First>(value);
		else
			return NthElement<Index - 1>( Forward<Parameters>(parameters)... );
	}

#pragma endregion
}