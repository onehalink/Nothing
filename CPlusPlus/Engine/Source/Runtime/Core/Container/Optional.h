#pragma once

#include "../InPlace.h"
#include "../Template.h"



namespace Engine
{
	struct NullOptional
	{

	};


	/**
	* @remark
	* Usage only for return value
	*/
	template<typename T>
	class Optional
	{
	public:
		Optional(NullOptional);
		template<typename ...Parameters> Optional(InPlace, Parameters&&... parameters);
		Optional(const T& value);
		Optional(T&& value);


		T& Value();


		Bool HasValue() const;


		operator Bool() const;
	private:
		Bool	existed;
		T		value;
	};


#pragma region Details

	template<typename T>
	Optional<T>::Optional(NullOptional)
		: existed(false)
	{

	}

	template<typename T>
	template<typename ...Parameters>
	Optional<T>::Optional(InPlace, Parameters&&... parameters)
		: existed(true), value( Forward<Parameters>(parameters)... )
	{

	}

	template<typename T>
	Optional<T>::Optional(const T& value)
		: existed(true), value(value)
	{

	}

	template<typename T>
	Optional<T>::Optional(T&& value)
		: existed(true), value( Forward<T>(value) )
	{

	}

	template<typename T>
	T& Optional<T>::Value()
	{
		return value;
	}

	template<typename T>
	Bool Optional<T>::HasValue() const
	{
		return existed;
	}

	template<typename T>
	Optional<T>::operator Bool() const
	{
		return HasValue();
	}

#pragma endregion
}