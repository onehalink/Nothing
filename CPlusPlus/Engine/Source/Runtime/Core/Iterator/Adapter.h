#pragma once

#include "../Forward.h"
#include "../InPlace.h"
#include "../Type.h"

#include "Category.h"



namespace Engine::Iterator
{
	// The adapter uses a CRTP(Curiously Recurring Template Pattern) pattern requring its base class to implement some methods


	/**
	* Require:
	* -	ElementType&		Dereference() const
	* -	Void				Increment()
	* -	Bool				Equal(const IteratorType&) const
	*/
	template<typename Base>
	class ForwardIteratorAdapter : public Base
	{
	public:
		using BaseType		= Base;
		using ThisType		= ForwardIteratorAdapter<Base>;

		using ElementType	= typename BaseType::ElementType;
		using DistanceType	= typename BaseType::DistanceType;


		static constexpr enum class Category Category = Category::Forward;


		template<typename ...Parameters>
		ForwardIteratorAdapter(InPlace, Parameters&&... parameters);


		ElementType& operator*() const;
		ElementType* operator->() const;

		ThisType& operator++();
		ThisType operator++(Int32);

		Bool operator==(const ThisType& iterator) const;
		Bool operator!=(const ThisType& iterator) const;
	private:
		using BaseType::Dereference;
		using BaseType::Increment;
		using BaseType::Equal;
	};


	/**
	* Require:
	* -	ElementType&		Dereference() const
	* -	Void				Decrement()
	* -	Bool				Equal(const IteratorType&) const
	*/
	template<typename Base>
	class BackwardIteratorAdapter : public Base
	{
	public:
		using BaseType		= Base;
		using ThisType		= BackwardIteratorAdapter<Base>;

		using ElementType	= typename BaseType::ElementType;
		using DistanceType	= typename BaseType::DistanceType;


		static constexpr enum class Category Category = Category::Backward;


		template<typename ...Parameters>
		BackwardIteratorAdapter(InPlace, Parameters&&... parameters);


		ElementType& operator*() const;
		ElementType* operator->() const;

		ThisType& operator--();
		ThisType operator--(Int32);

		Bool operator==(const ThisType& iterator) const;
		Bool operator!=(const ThisType& iterator) const;
	private:
		using BaseType::Dereference;
		using BaseType::Decrement;
		using BaseType::Equal;
	};


	/**
	* Require:
	* -	ElementType&		Dereference() const
	* - Void				Increment()
	* -	Void				Decrement()
	* -	Bool				Equal(const IteratorType&) const
	*/
	template<typename Base>
	class BidirectionalIteratorAdapter : public Base
	{
	public:
		using BaseType		= Base;
		using ThisType		= BidirectionalIteratorAdapter<Base>;

		using ElementType	= typename BaseType::ElementType;
		using DistanceType	= typename BaseType::DistanceType;


		static constexpr enum class Category Category = Category::Bidirectional;


		template<typename ...Parameters>
		BidirectionalIteratorAdapter(InPlace, Parameters&&... parameters);


		ElementType& operator*() const;
		ElementType* operator->() const;

		ThisType& operator++();
		ThisType operator++(Int32);

		ThisType& operator--();
		ThisType operator--(Int32);

		Bool operator==(const ThisType& iterator) const;
		Bool operator!=(const ThisType& iterator) const;
	private:
		using BaseType::Dereference;
		using BaseType::Increment;
		using BaseType::Decrement;
		using BaseType::Equal;
	};


	/**
	* Require:
	* -	ElementType&		Dereference() const
	* -	Void				Increment(DistanceType)
	* -	Void				Decrement(DistanceType)
	* - DistanceType		Distance(const IteratorType&) const
	* -	Bool				Equal(const IteratorType&) const
	*/
	template<typename Base>
	class ContiguousIteratorAdapter : public Base
	{
	public:
		using BaseType		= Base;
		using ThisType		= ContiguousIteratorAdapter<Base>;

		using ElementType	= typename BaseType::ElementType;
		using DistanceType	= typename BaseType::DistanceType;


		static constexpr enum class Category Category = Category::Contiguous;


		template<typename ...Parameters>
		ContiguousIteratorAdapter(InPlace, Parameters&&... parameters);


		ElementType& operator*() const;
		ElementType* operator->() const;

		ThisType& operator++();
		ThisType operator++(Int32);

		ThisType& operator--();
		ThisType operator--(Int32);

		ThisType& operator+=(DistanceType distance);
		ThisType operator+(DistanceType distance) const;

		ThisType& operator-=(DistanceType distance);
		ThisType operator-(DistanceType distance) const;
	
		DistanceType operator-(const ThisType& iterator) const;

		Bool operator==(const ThisType& iterator) const;
		Bool operator!=(const ThisType& iterator) const;
	private:
		using BaseType::Dereference;
		using BaseType::Increment;
		using BaseType::Decrement;
		using BaseType::Distance;
		using BaseType::Equal;
	};


#pragma region Details

	template<typename Base>
	template<typename ...Parameters>
	ForwardIteratorAdapter<Base>::ForwardIteratorAdapter(InPlace, Parameters&&... parameter)
		: BaseType( Forward<Parameters>(parameter)... )
	{

	}

	template<typename Base>
	typename ForwardIteratorAdapter<Base>::ElementType& ForwardIteratorAdapter<Base>::operator*() const
	{
		return Dereference();
	}

	template<typename Base>
	typename ForwardIteratorAdapter<Base>::ElementType* ForwardIteratorAdapter<Base>::operator->() const
	{
		return &Dereference();
	}

	template<typename Base>
	typename ForwardIteratorAdapter<Base>::ThisType& ForwardIteratorAdapter<Base>::operator++()
	{
		Increment();

		return *this;
	}

	template<typename Base>
	typename ForwardIteratorAdapter<Base>::ThisType ForwardIteratorAdapter<Base>::operator++(Int32)
	{
		ThisType result = *this;

		++*this;

		return result;
	}

	template<typename Base>
	Bool ForwardIteratorAdapter<Base>::operator==(const ThisType& iterator) const
	{
		return Equal(iterator);
	}

	template<typename Base>
	Bool ForwardIteratorAdapter<Base>::operator!=(const ThisType& iterator) const
	{
		return !operator==(iterator);
	}

	template<typename Base>
	template<typename ...Parameters>
	BackwardIteratorAdapter<Base>::BackwardIteratorAdapter(InPlace, Parameters&&... parameter)
		: BaseType( Forward<Parameters>(parameter)... )
	{

	}

	template<typename Base>
	typename BackwardIteratorAdapter<Base>::ElementType& BackwardIteratorAdapter<Base>::operator*() const
	{
		return Dereference();
	}

	template<typename Base>
	typename BackwardIteratorAdapter<Base>::ElementType* BackwardIteratorAdapter<Base>::operator->() const
	{
		return &Dereference();
	}

	template<typename Base>
	typename BackwardIteratorAdapter<Base>::ThisType& BackwardIteratorAdapter<Base>::operator--()
	{
		Decrement();

		return *this;
	}

	template<typename Base>
	typename BackwardIteratorAdapter<Base>::ThisType BackwardIteratorAdapter<Base>::operator--(Int32)
	{
		ThisType result = *this;

		--*this;

		return result;
	}

	template<typename Base>
	Bool BackwardIteratorAdapter<Base>::operator==(const ThisType& iterator) const
	{
		return Equal(iterator);
	}

	template<typename Base>
	Bool BackwardIteratorAdapter<Base>::operator!=(const ThisType& iterator) const
	{
		return !operator==(iterator);
	}

	template<typename Base>
	template<typename ...Parameters>
	BidirectionalIteratorAdapter<Base>::BidirectionalIteratorAdapter(InPlace, Parameters&&... parameter)
		: BaseType( Forward<Parameters>(parameter)... )
	{

	}

	template<typename Base>
	typename BidirectionalIteratorAdapter<Base>::ElementType& BidirectionalIteratorAdapter<Base>::operator*() const
	{
		return Dereference();
	}

	template<typename Base>
	typename BidirectionalIteratorAdapter<Base>::ElementType* BidirectionalIteratorAdapter<Base>::operator->() const
	{
		return &Dereference();
	}

	template<typename Base>
	typename BidirectionalIteratorAdapter<Base>::ThisType& BidirectionalIteratorAdapter<Base>::operator++()
	{
		Increment();

		return *this;
	}

	template<typename Base>
	typename BidirectionalIteratorAdapter<Base>::ThisType BidirectionalIteratorAdapter<Base>::operator++(Int32)
	{
		ThisType result = *this;

		++*this;

		return result;
	}

	template<typename Base>
	typename BidirectionalIteratorAdapter<Base>::ThisType& BidirectionalIteratorAdapter<Base>::operator--()
	{
		Decrement();

		return *this;
	}

	template<typename Base>
	typename BidirectionalIteratorAdapter<Base>::ThisType BidirectionalIteratorAdapter<Base>::operator--(Int32)
	{
		ThisType result = *this;

		--*this;

		return result;
	}

	template<typename Base>
	Bool BidirectionalIteratorAdapter<Base>::operator==(const ThisType& iterator) const
	{
		return Equal(iterator);
	}

	template<typename Base>
	Bool BidirectionalIteratorAdapter<Base>::operator!=(const ThisType& iterator) const
	{
		return !operator==(iterator);
	}

	template<typename Base>
	template<typename ...Parameters>
	ContiguousIteratorAdapter<Base>::ContiguousIteratorAdapter(InPlace, Parameters&&... parameters)
		: BaseType( Forward<Parameters>(parameters)... )
	{

	}

	template<typename Base>
	typename ContiguousIteratorAdapter<Base>::ElementType& ContiguousIteratorAdapter<Base>::operator*() const
	{
		return Dereference();
	}

	template<typename Base>
	typename ContiguousIteratorAdapter<Base>::ElementType* ContiguousIteratorAdapter<Base>::operator->() const
	{
		return &Dereference();
	}

	template<typename Base>
	typename ContiguousIteratorAdapter<Base>::ThisType& ContiguousIteratorAdapter<Base>::operator++()
	{
		return *this += 1;
	}

	template<typename Base>
	typename ContiguousIteratorAdapter<Base>::ThisType ContiguousIteratorAdapter<Base>::operator++(Int32)
	{
		ThisType result = *this;

		++*this;

		return result;
	}

	template<typename Base>
	typename ContiguousIteratorAdapter<Base>::ThisType& ContiguousIteratorAdapter<Base>::operator--()
	{
		return *this -= 1;
	}

	template<typename Base>
	typename ContiguousIteratorAdapter<Base>::ThisType ContiguousIteratorAdapter<Base>::operator--(Int32)
	{
		ThisType result = *this;

		--*this;

		return result;
	}

	template<typename Base>
	typename ContiguousIteratorAdapter<Base>::ThisType& ContiguousIteratorAdapter<Base>::operator+=(DistanceType distance)
	{
		Increment(distance);

		return *this;
	}

	template<typename Base>
	typename ContiguousIteratorAdapter<Base>::ThisType ContiguousIteratorAdapter<Base>::operator+(DistanceType distance) const
	{
		ThisType result = *this;

		result += distance;

		return result;
	}

	template<typename Base>
	typename ContiguousIteratorAdapter<Base>::ThisType& ContiguousIteratorAdapter<Base>::operator-=(DistanceType distance)
	{
		Decrement(distance);

		return *this;
	}

	template<typename Base>
	typename ContiguousIteratorAdapter<Base>::ThisType ContiguousIteratorAdapter<Base>::operator-(DistanceType distance) const
	{
		ThisType result = *this;

		result -= distance;

		return result;
	}

	template<typename Base>
	typename ContiguousIteratorAdapter<Base>::DistanceType ContiguousIteratorAdapter<Base>::operator-(const ThisType& iterator) const
	{
		return Distance(iterator);
	}

	template<typename Base>
	Bool ContiguousIteratorAdapter<Base>::operator==(const ThisType& iterator) const
	{
		return Equal(iterator);
	}

	template<typename Base>
	Bool ContiguousIteratorAdapter<Base>::operator!=(const ThisType& iterator) const
	{
		return !operator==(iterator);
	}

#pragma endregion
}