#pragma once

#include "ParameterPack.h"
#include "Type.h"

#include "Template/AndOrNot.h"
#include "Template/IsEnum.h"
#include "Template/TypesAreSame.h"



namespace Engine::Enum
{
	template<typename T>
	using UnderlyingType = __underlying_type(T);


	template<typename T> constexpr T From(UnderlyingType<T> value);
	template<typename T> constexpr UnderlyingType<T> To(T enumValue);


	template<typename ...Enums> constexpr auto And(Enums... enums);
	template<typename ...Enums> constexpr auto Or(Enums... enums);
	template<typename ...Enums> constexpr auto XOr(Enums... enums);
	template<typename Enum> constexpr Enum Complement(Enum flags);

	template<typename Enum, typename ...Enums> constexpr Enum& Add(Enum& flags, Enums... flagsToAdd);
	template<typename Enum, typename ...Enums> constexpr Enum& Remove(Enum& flags, Enums... flagsToRemove);


	template<typename Enum, typename ...Enums> constexpr Bool HasAny(Enum flags, Enums... flagsToTest);
	template<typename Enum, typename ...Enums> constexpr Bool HasAll(Enum flags, Enums... flagsToTest);


#pragma region Details

	template<typename T>
	constexpr T From(UnderlyingType<T> value)
	{
		static_assert( IsEnum<T>::Value );


		return T(value);
	}

	template<typename T>
	constexpr UnderlyingType<T> To(T enumValue)
	{
		static_assert( IsEnum<T>::Value );


		return static_cast<UnderlyingType<T>>(enumValue);
	}

	template<typename ...Enums>
	constexpr auto And(Enums... enums)
	{
		static_assert( sizeof...(enums) >= 2 );
		static_assert( Engine::And<IsEnum<Enums> ...>::Value );
		static_assert( TypesAreSame<Enums ...>::Value );


		using EnumType = typename ParameterPack::Nth<0, Enums ...>::Type;


		return EnumType( ( To(enums) & ... ) );
	}

	template<typename ...Enums>
	constexpr auto Or(Enums... enums)
	{
		static_assert( sizeof...(enums) >= 2 );
		static_assert( Engine::And<IsEnum<Enums> ...>::Value );
		static_assert( TypesAreSame<Enums ...>::Value );


		using EnumType = typename ParameterPack::Nth<0, Enums ...>::Type;


		return EnumType( ( To(enums) | ... ) );
	}

	template<typename ...Enums>
	constexpr auto XOr(Enums... enums)
	{
		static_assert( sizeof...(enums) >= 2 );
		static_assert( Engine::And<IsEnum<Enums> ...>::Value );
		static_assert( TypesAreSame<Enums ...>::Value );


		using EnumType = typename ParameterPack::Nth<0, Enums ...>::Type;


		return EnumType( ( To(enums) ^ ... ) );
	}

	template<typename Enum>
	constexpr Enum Complement(Enum flags)
	{
		static_assert( IsEnum<Enum>::Value );


		return Enum( ~To(flags) );
	}

	template<typename Enum, typename ...Enums>
	constexpr Enum& Add(Enum& flags, Enums... flagsToAdd)
	{
		return flags = Or( flags, flagsToAdd... );
	}

	template<typename Enum, typename ...Enums>
	constexpr Enum& Remove(Enum& flags, Enums... flagsToRemove)
	{
		return flags = And( flags, Complement(flagsToRemove)... );
	}

	template<typename Enum, typename ...Enums>
	constexpr Bool HasAny(Enum flags, Enums... flagsToTest)
	{
		static_assert( sizeof...(flagsToTest) > 0 );
		static_assert( Engine::And<IsEnum<Enum>, IsEnum<Enums> ...>::Value );
		static_assert( TypesAreSame<Enum, Enums ...>::Value );


		return ( ( And(flags, flagsToTest) != Enum() ) || ... );
	}

	template<typename Enum, typename ...Enums>
	constexpr Bool HasAll(Enum flags, Enums... flagsToTest)
	{
		static_assert( sizeof...(flagsToTest) > 0 );
		static_assert( Engine::And<IsEnum<Enum>, IsEnum<Enums> ...>::Value );
		static_assert( TypesAreSame<Enum, Enums ...>::Value );


		return ( ( And(flags, flagsToTest) == flagsToTest ) && ... );
	}

#pragma endregion
}