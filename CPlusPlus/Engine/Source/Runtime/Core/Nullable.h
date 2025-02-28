#pragma once

#include "InPlace.h"
#include "Type.h"

#include "Template/Forward.h"



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
		template<typename ...Parameters>
		Nullable(InPlace, Parameters&&... parameters);
		Nullable(T&& value);
		Nullable(const T& value);


		T& Value();


		operator Bool() const;
	private:
		Bool	isValid;
		T		value;
	};


#pragma region Details

	template<typename T>
	Nullable<T>::Nullable(Null)
		: isValid(false)
	{

	}

	template<typename T>
	template<typename ...Parameters>
	Nullable<T>::Nullable(InPlace, Parameters&&... parameters)
		: isValid(true), value( Forward<Parameters>(parameters)... )
	{

	}

	template<typename T>
	Nullable<T>::Nullable(T&& value)
		: isValid(true), value( Forward<T>(value) )
	{

	}

	template<typename T>
	Nullable<T>::Nullable(const T& value)
		: isValid(true), value(value)
	{

	}

	template<typename T>
	T& Nullable<T>::Value()
	{
		return value;
	}

	template<typename T>
	Nullable<T>::operator Bool() const
	{
		return isValid;
	}

#pragma endregion
}