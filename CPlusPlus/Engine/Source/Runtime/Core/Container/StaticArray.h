#pragma once

#include "../Mathematics/NumericCalculation.h"

#include "../Template/ParameterPackHelper.h"



namespace Engine
{
	// Stack allocated array in fixed size
	template<SizeType N, typename T>
	class StaticArray
	{
	public:
		StaticArray();
		template<typename ...Parameters> StaticArray(InPlace, Parameters&&... parameters);
		StaticArray(const StaticArray<N, T>& other);


		T* GetBuffer();
		const T* GetBuffer() const;
		constexpr SizeType GetCount() const;


		StaticArray<N, T>& operator=(const StaticArray<N, T>& other);

		T& operator[](SizeType index);
		const T& operator[](SizeType index) const;

		operator T*();
		operator const T*() const;
	public:
		using Iterator		= T*;
		using ConstIterator	= const T* const;


		Iterator begin();
		Iterator end();

		ConstIterator begin() const;
		ConstIterator end() const;
	private:
		T storage[N];
	};


#pragma region Details

	template<SizeType N, typename T>
	StaticArray<N, T>::StaticArray()
	{

	}

	template<SizeType N, typename T>
	template<typename ...Parameters>
	StaticArray<N, T>::StaticArray(InPlace, Parameters&&... parameters)
	{
		static_assert( sizeof...(parameters) <= N );


		ParameterPackHelper::CopyTo( storage, Forward<Parameters>(parameters)... );
	}

	template<SizeType N, typename T>
	StaticArray<N, T>::StaticArray(const StaticArray<N, T>& other)
	{
		for (SizeType index = 0; index < N; index++)
			storage[index] = other.storage[index];
	}

	template<SizeType N, typename T>
	T* StaticArray<N, T>::GetBuffer()
	{
		return storage;
	}

	template<SizeType N, typename T>
	const T* StaticArray<N, T>::GetBuffer() const
	{
		return storage;
	}

	template<SizeType N, typename T>
	constexpr SizeType StaticArray<N, T>::GetCount() const
	{
		return N;
	}

	template<SizeType N, typename T>
	StaticArray<N, T>& StaticArray<N, T>::operator=(const StaticArray<N, T>& other)
	{
		for (SizeType index = 0; index < N; index++)
			storage[index] = other.storage[index];

		return *this;
	}

	template<SizeType N, typename T>
	T& StaticArray<N, T>::operator[](SizeType index)
	{
		ASSERT( index < N, "Index output of range" );


		return storage[index];
	}

	template<SizeType N, typename T>
	const T& StaticArray<N, T>::operator[](SizeType index) const
	{
		ASSERT( index < N, "Index output of range" );


		return storage[index];
	}

	template<SizeType N, typename T>
	StaticArray<N, T>::operator T*()
	{
		return GetBuffer();
	}

	template<SizeType N, typename T>
	StaticArray<N, T>::operator const T*() const
	{
		return GetBuffer();
	}

	template<SizeType N, typename T>
	typename StaticArray<N, T>::Iterator StaticArray<N, T>::begin()
	{
		return GetBuffer();
	}

	template<SizeType N, typename T>
	typename StaticArray<N, T>::Iterator StaticArray<N, T>::end()
	{
		return GetBuffer() + N;
	}

	template<SizeType N, typename T>
	typename StaticArray<N, T>::ConstIterator StaticArray<N, T>::begin() const
	{
		return GetBuffer();
	}

	template<SizeType N, typename T>
	typename StaticArray<N, T>::ConstIterator StaticArray<N, T>::end() const
	{
		return GetBuffer() + N;
	}

#pragma endregion
}