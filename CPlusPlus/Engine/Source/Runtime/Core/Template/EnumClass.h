#pragma once

#include "EnumUnderlyingType.h"



namespace Engine
{
	#define ENABLE_BITWISE_OPERATORS(EnumClass) template<> struct EnableBitwiseOperators<EnumClass> : TrueType {}


	/**
	* As a flag to disable/enable bitwise operators(&, |, ^ and ~) for enum class
	* 
	* @remark
	* Default is disable, and uses ENABLE_BITWISE_OPERATORS to enable
	*/
	template<typename EnumClass>
	struct EnableBitwiseOperators : FalseType
	{

	};


	template<typename EnumClass> constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, Bool>::Type EnumClassHasAnyFlags(EnumClass E, EnumClass flags);
	template<typename EnumClass> constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, Bool>::Type EnumClassHasAllFlags(EnumClass E, EnumClass flags);


	template<typename EnumClass> constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator&(EnumClass L, EnumClass R);
	template<typename EnumClass> constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator|(EnumClass L, EnumClass R);
	template<typename EnumClass> constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator^(EnumClass L, EnumClass R);
	template<typename EnumClass> constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator~(EnumClass E);

	template<typename EnumClass> typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type& operator&=(EnumClass& L, EnumClass R);
	template<typename EnumClass> typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type& operator|=(EnumClass& L, EnumClass R);
	template<typename EnumClass> typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type& operator^=(EnumClass& L, EnumClass R);


#pragma region Details

	template<typename EnumClass>
	constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, Bool>::Type EnumClassHasAnyFlags(EnumClass E, EnumClass flags)
	{
		return ( E & flags ) != EnumClass();
	}

	template<typename EnumClass>
	constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, Bool>::Type EnumClassHasAllFlags(EnumClass E, EnumClass flags)
	{
		return ( E & flags ) == flags;
	}

	template<typename EnumClass>
	constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator&(EnumClass L, EnumClass R)
	{
		using UnderlyingType = EnumUnderlyingType<EnumClass>;


		return EnumClass( static_cast<UnderlyingType>(L) & static_cast<UnderlyingType>(R) );
	}

	template<typename EnumClass>
	constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator|(EnumClass L, EnumClass R)
	{
		using UnderlyingType = EnumUnderlyingType<EnumClass>;


		return EnumClass( static_cast<UnderlyingType>(L) | static_cast<UnderlyingType>(R) );
	}

	template<typename EnumClass>
	constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator^(EnumClass L, EnumClass R)
	{
		using UnderlyingType = EnumUnderlyingType<EnumClass>;


		return EnumClass( static_cast<UnderlyingType>(L) ^ static_cast<UnderlyingType>(R) );
	}

	template<typename EnumClass>
	constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator~(EnumClass E)
	{
		using UnderlyingType = EnumUnderlyingType<EnumClass>;


		return EnumClass( ~static_cast<UnderlyingType>(E) );
	}

	template<typename EnumClass>
	typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type& operator&=(EnumClass& L, EnumClass R)
	{
		return L = L & R;
	}

	template<typename EnumClass>
	typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type& operator|=(EnumClass& L, EnumClass R)
	{
		return L = L | R;
	}

	template<typename EnumClass>
	typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type& operator^=(EnumClass& L, EnumClass R)
	{
		return L = L ^ R;
	}

#pragma endregion
}
