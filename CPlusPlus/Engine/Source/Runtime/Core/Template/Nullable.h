#pragma once

#include "../Base.h"



namespace Engine
{
	struct Null
	{

	};


	/**
	* @remark
	* Usage only for return value
	*/
	template<typename T>
	class Nullable
	{
	public:
		Nullable(Null);
		template<typename ...Parameters> Nullable(InPlace, Parameters&&... parameters);
		Nullable(const T& value);
		Nullable(T&& value);


		T& Value();


		Bool HasValue() const;


		operator Bool() const;
	private:
		Bool	existed;
		T		value;
	};


#pragma region Details

	template<typename T>
	Nullable<T>::Nullable(Null)
		: existed(false)
	{

	}

	template<typename T>
	template<typename ...Parameters>
	Nullable<T>::Nullable(InPlace, Parameters&&... parameters)
		: existed(true), value( Forward<Parameters>(parameters)... )
	{

	}

	template<typename T>
	Nullable<T>::Nullable(const T& value)
		: existed(true), value(value)
	{

	}

	template<typename T>
	Nullable<T>::Nullable(T&& value)
		: existed(true), value( Move(value) )
	{

	}

	template<typename T>
	T& Nullable<T>::Value()
	{
		return value;
	}

	template<typename T>
	Bool Nullable<T>::HasValue() const
	{
		return existed;
	}

	template<typename T>
	Nullable<T>::operator Bool() const
	{
		return HasValue();
	}

#pragma endregion
}