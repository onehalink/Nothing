#pragma once

#include "../CoreMinimal.h"



namespace Engine
{
	template<typename T, typename Allocator = DefaultAllocator<T>>
	class DynamicArray
	{
	public:
		DynamicArray();
		DynamicArray(SizeType capacity);
		template<typename ...Parameters>
		DynamicArray(InPlace, Parameters&&... parameters);
		DynamicArray(DynamicArray<T, Allocator>&& other);
		DynamicArray(const DynamicArray<T, Allocator>& other);
		~DynamicArray();


		Void Add(T&& element);
		Void Add(const T& element);
		Void InsertAt(SizeType index, T&& element);
		Void InsertAt(SizeType index, const T& element);
		Void RemoveAt(SizeType index);

		Void Clear();


		T* GetBuffer();
		const T* GetBuffer() const;
		SizeType GetCount() const;
		SizeType GetCapacity() const;


		DynamicArray<T, Allocator>& operator=(DynamicArray<T, Allocator>&& other);
		DynamicArray<T, Allocator>& operator=(const DynamicArray<T, Allocator>& other);

		T& operator[](SizeType index);
		const T& operator[](SizeType index) const;
	public:
		using Iterator		= T*;
		using ConstIterator = const T*;


		Iterator begin();
		Iterator end();

		ConstIterator begin() const;
		ConstIterator end() const;
	private:
		Void Expand();
		Void CopyFrom(const DynamicArray<T, Allocator>& other);
		Void SwapWith(DynamicArray<T, Allocator>& other);
	private:
		Allocator	allocator;

		T*			buffer;
		SizeType	count;
		SizeType	capacity;
	};


#pragma region Details

	template<typename T, typename Allocator>
	DynamicArray<T, Allocator>::DynamicArray()
		: buffer(nullptr), count(0), capacity(0)
	{

	}

	template<typename T, typename Allocator>
	DynamicArray<T, Allocator>::DynamicArray(SizeType capacity)
		: buffer( allocator.Allocate(capacity) ), count(0), capacity(capacity)
	{

	}

	template<typename T, typename Allocator>
	template<typename ...Parameters>
	DynamicArray<T, Allocator>::DynamicArray(InPlace, Parameters&&... parameters)
	{
		static_assert( And<IsConvertible<Parameters, T> ...>::Value );


		capacity = count = sizeof...(parameters);

		buffer = allocator.Allocate(capacity);
		ParameterPackHelper::CopyTo( buffer, Forward<Parameters>(parameters)... );
	}

	template<typename T, typename Allocator>
	DynamicArray<T, Allocator>::DynamicArray(DynamicArray<T, Allocator>&& other)
	{
		buffer = nullptr;

		SwapWith(other);
	}

	template<typename T, typename Allocator>
	DynamicArray<T, Allocator>::DynamicArray(const DynamicArray<T, Allocator>& other)
	{
		CopyFrom(other);
	}

	template<typename T, typename Allocator>
	DynamicArray<T, Allocator>::~DynamicArray()
	{
		allocator.Deallocate(buffer, capacity);
	}

	template<typename T, typename Allocator>
	Void DynamicArray<T, Allocator>::Add(T&& element)
	{
		if ( count == capacity )
			Expand();

		buffer[ count++ ] = Forward<T>(element);
	}

	template<typename T, typename Allocator>
	Void DynamicArray<T, Allocator>::Add(const T& element)
	{
		if ( count == capacity )
			Expand();

		buffer[ count++ ] = element;
	}

	template<typename T, typename Allocator>
	Void DynamicArray<T, Allocator>::InsertAt(SizeType index, T&& element)
	{
		if ( count == capacity )
			Expand();

		count++;
		for (SizeType iteration = count - 1; iteration > index; iteration--)
			buffer[iteration] = Move( buffer[ iteration - 1 ] );

		buffer[index] = Forward<T>(element);
	}

	template<typename T, typename Allocator>
	Void DynamicArray<T, Allocator>::InsertAt(SizeType index, const T& element)
	{
		if ( count == capacity )
			Expand();

		count++;
		for (SizeType iteration = count - 1; iteration > index; iteration--)
			buffer[iteration] = Move( buffer[ iteration - 1 ] );

		buffer[index] = element;
	}

	template<typename T, typename Allocator>
	Void DynamicArray<T, Allocator>::RemoveAt(SizeType index)
	{
		for (SizeType iteration = index + 1; iteration < count; iteration++)
			buffer[iteration - 1] = Move( buffer[iteration] );

		count--;
	}

	template<typename T, typename Allocator>
	Void DynamicArray<T, Allocator>::Clear()
	{
		count = 0;
	}

	template<typename T, typename Allocator>
	T* DynamicArray<T, Allocator>::GetBuffer()
	{
		return buffer;
	}

	template<typename T, typename Allocator>
	const T* DynamicArray<T, Allocator>::GetBuffer() const
	{
		return buffer;
	}

	template<typename T, typename Allocator>
	SizeType DynamicArray<T, Allocator>::GetCount() const
	{
		return count;
	}

	template<typename T, typename Allocator>
	SizeType DynamicArray<T, Allocator>::GetCapacity() const
	{
		return capacity;
	}

	template<typename T, typename Allocator>
	DynamicArray<T, Allocator>& DynamicArray<T, Allocator>::operator=(DynamicArray<T, Allocator>&& other)
	{
		SwapWith(other);

		return *this;
	}

	template<typename T, typename Allocator>
	DynamicArray<T, Allocator>& DynamicArray<T, Allocator>::operator=(const DynamicArray<T, Allocator>& other)
	{
		this->~DynamicArray();
		CopyFrom(other);

		return *this;
	}

	template<typename T, typename Allocator>
	T& DynamicArray<T, Allocator>::operator[](SizeType index)
	{
		return buffer[index];
	}

	template<typename T, typename Allocator>
	const T& DynamicArray<T, Allocator>::operator[](SizeType index) const
	{
		return buffer[index];
	}

	template<typename T, typename Allocator>
	typename DynamicArray<T, Allocator>::Iterator DynamicArray<T, Allocator>::begin()
	{
		return buffer;
	}

	template<typename T, typename Allocator>
	typename DynamicArray<T, Allocator>::Iterator DynamicArray<T, Allocator>::end()
	{
		return buffer + count;
	}

	template<typename T, typename Allocator>
	typename DynamicArray<T, Allocator>::ConstIterator DynamicArray<T, Allocator>::begin() const
	{
		return buffer;
	}

	template<typename T, typename Allocator>
	typename DynamicArray<T, Allocator>::ConstIterator DynamicArray<T, Allocator>::end() const
	{
		return buffer + count;
	}

	template<typename T, typename Allocator>
	Void DynamicArray<T, Allocator>::Expand()
	{
		constexpr SizeType MinimumCapacity	= 8;
		constexpr RealType ExpandFactor		= 1.5;


		if ( capacity < MinimumCapacity )
			capacity = MinimumCapacity;
		else
			capacity *= ExpandFactor;

		T* temporary = allocator.Allocate(capacity);
		for (SizeType index = 0; index < count; index++)
			temporary[index] = Move( buffer[index] );

		this->~DynamicArray();
		buffer = temporary;
	}

	template<typename T, typename Allocator>
	Void DynamicArray<T, Allocator>::CopyFrom(const DynamicArray<T, Allocator>& other)
	{
		allocator = other.allocator;

		capacity = count = other.count;

		buffer = allocator.Allocate(capacity);
		for (SizeType index = 0; index < count; index++)
			buffer[index] = other[index];
	}

	template<typename T, typename Allocator>
	Void DynamicArray<T, Allocator>::SwapWith(DynamicArray<T, Allocator>& other)
	{
		allocator = Move( other.allocator );

		Swap( &buffer,		&other.buffer	);
		Swap( &count,		&other.count	);
		Swap( &capacity,	&other.capacity	);
	}

#pragma endregion
}