#pragma once

#include "../InPlace.h"
#include "../Template.h"

#include "../Mathematics/NumericCalculation.h"



namespace Engine
{
	template<typename T>
	class Nullable
	{
	public:
		Nullable();
		template<typename ...Parameters> Nullable(InPlace, Parameters&&... parameters);
		Nullable(const T& value);
		Nullable(T&& value);


		Void SetValue(const T& value);
		Void SetValue(T&& value);


		T& GetValue();
		Bool HasValue() const;
		const T& GetValue() const;


		Nullable<T>& operator=(const Nullable<T>& other);
		Nullable<T>& operator=(Nullable<T>&& other);

		operator Bool() const;
	private:
		Bool	existed;
		T		value;
	};


#pragma region Details

	template<typename T>
	Nullable<T>::Nullable()
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
		: existed(true), value( Forward<T>(value) )
	{

	}

	template<typename T>
	Void Nullable<T>::SetValue(const T& value)
	{
		existed = true;

		this->value = value;
	}

	template<typename T>
	Void Nullable<T>::SetValue(T&& value)
	{
		existed = true;

		this->value = Forward<T>(value);
	}

	template<typename T>
	T& Nullable<T>::GetValue()
	{
		return value;
	}

	template<typename T>
	Bool Nullable<T>::HasValue() const
	{
		return existed;
	}

	template<typename T>
	const T& Nullable<T>::GetValue() const
	{
		return value;
	}

	template<typename T>
	Nullable<T>& Nullable<T>::operator=(const Nullable<T>& other)
	{
		existed	= other.existed;
		value	= other.value;

		return *this;
	}

	template<typename T>
	Nullable<T>& Nullable<T>::operator=(Nullable<T>&& other)
	{
		Swap( &existed, &other.existed );

		value = Move( other.value );

		return *this;
	}

	template<typename T>
	Nullable<T>::operator Bool() const
	{
		return HasValue();
	}

#pragma endregion
}