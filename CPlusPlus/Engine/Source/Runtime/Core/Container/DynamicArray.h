#pragma once

#include "Span.h"



namespace Engine
{
	template<typename T, typename Allocator = DefaultAllocator<T>> class DynamicArray;
	template<typename T, typename Allocator = DefaultAllocator<T>> using Array = DynamicArray<T, Allocator>;


	template<typename T, typename Allocator>
	class DynamicArray
	{
	public:
		DynamicArray();
		DynamicArray(SizeType capacity);
		template<typename ...Parameters> DynamicArray(InPlace, Parameters&&... parameters);
		DynamicArray(const DynamicArray<T, Allocator>& other);
		DynamicArray(DynamicArray<T, Allocator>&& other);
		~DynamicArray();


		Void Add(const T& element);
		Void Add(T&& element);
		Void InsertAt(SizeType index, const T& element);
		Void InsertAt(SizeType index, T&& element);
		Void RemoveAt(SizeType index);

		Void Clear();


		T* GetBuffer();
		const T* GetBuffer() const;
		SizeType GetCount() const;
		SizeType GetCapacity() const;


		DynamicArray<T, Allocator>& operator=(const DynamicArray<T, Allocator>& other);
		DynamicArray<T, Allocator>& operator=(DynamicArray<T, Allocator>&& other);

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
		Span<T, Allocator> storage{};

		SizeType count;
	};


#pragma region Details

	template<typename T, typename Allocator>
	DynamicArray<T, Allocator>::DynamicArray()
		: count(0)
	{

	}

	template<typename T, typename Allocator>
	DynamicArray<T, Allocator>::DynamicArray(SizeType capacity)
		: storage(capacity), count(0)
	{

	}

	template<typename T, typename Allocator>
	template<typename ...Parameters>
	DynamicArray<T, Allocator>::DynamicArray(InPlace, Parameters&&... parameters)
		: storage( InPlace(), Forward<Parameters>(parameters)... ), count( sizeof...(parameters) )
	{

	}

	template<typename T, typename Allocator>
	DynamicArray<T, Allocator>::DynamicArray(const DynamicArray<T, Allocator>& other)
		: storage( other.storage ), count( other.count )
	{

	}

	template<typename T, typename Allocator>
	DynamicArray<T, Allocator>::DynamicArray(DynamicArray<T, Allocator>&& other)
		: storage( Move( other.storage ) ), count( other.count )
	{

	}

	template<typename T, typename Allocator>
	DynamicArray<T, Allocator>::~DynamicArray()
	{

	}

	template<typename T, typename Allocator>
	Void DynamicArray<T, Allocator>::Add(const T& element)
	{
		if ( GetCount() == GetCapacity() )
			storage.Expand();

		GetBuffer()[ count++ ] = element;
	}

	template<typename T, typename Allocator>
	Void DynamicArray<T, Allocator>::Add(T&& element)
	{
		if ( GetCount() == GetCapacity() )
			storage.Expand();

		GetBuffer()[ count++ ] = Forward<T>(element);
	}

	template<typename T, typename Allocator>
	Void DynamicArray<T, Allocator>::InsertAt(SizeType index, const T& element)
	{
		if ( GetCount() == GetCapacity() )
			storage.Expand();

		count++;
		for (SizeType iteration = count - 1; iteration > index; iteration--)
			GetBuffer()[iteration] = Move( GetBuffer()[ iteration - 1 ] );

		GetBuffer()[index] = element;
	}

	template<typename T, typename Allocator>
	Void DynamicArray<T, Allocator>::InsertAt(SizeType index, T&& element)
	{
		if ( GetCount() == GetCapacity() )
			storage.Expand();

		count++;
		for (SizeType iteration = count - 1; iteration > index; iteration--)
			GetBuffer()[iteration] = Move( GetBuffer()[ iteration - 1 ] );

		GetBuffer()[index] = Forward<T>(element);
	}

	template<typename T, typename Allocator>
	Void DynamicArray<T, Allocator>::RemoveAt(SizeType index)
	{
		for (SizeType iteration = index + 1; iteration < count; iteration++)
			GetBuffer()[ iteration - 1 ] = Move( GetBuffer()[iteration] );

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
		return storage.GetBuffer();
	}

	template<typename T, typename Allocator>
	const T* DynamicArray<T, Allocator>::GetBuffer() const
	{
		return storage.GetBuffer();
	}

	template<typename T, typename Allocator>
	SizeType DynamicArray<T, Allocator>::GetCount() const
	{
		return count;
	}

	template<typename T, typename Allocator>
	SizeType DynamicArray<T, Allocator>::GetCapacity() const
	{
		return storage.GetCount();
	}

	template<typename T, typename Allocator>
	DynamicArray<T, Allocator>& DynamicArray<T, Allocator>::operator=(const DynamicArray<T, Allocator>& other)
	{
		storage	= other.storage;
		count	= other.count;

		return *this;
	}

	template<typename T, typename Allocator>
	DynamicArray<T, Allocator>& DynamicArray<T, Allocator>::operator=(DynamicArray<T, Allocator>&& other)
	{
		storage = Move( other.storage );

		Swap( &count, &other.count );

		return *this;
	}

	template<typename T, typename Allocator>
	T& DynamicArray<T, Allocator>::operator[](SizeType index)
	{
		return storage[index];
	}

	template<typename T, typename Allocator>
	const T& DynamicArray<T, Allocator>::operator[](SizeType index) const
	{
		return storage[index];
	}

	template<typename T, typename Allocator>
	typename DynamicArray<T, Allocator>::Iterator DynamicArray<T, Allocator>::begin()
	{
		return GetBuffer();
	}

	template<typename T, typename Allocator>
	typename DynamicArray<T, Allocator>::Iterator DynamicArray<T, Allocator>::end()
	{
		return GetBuffer() + count;
	}

	template<typename T, typename Allocator>
	typename DynamicArray<T, Allocator>::ConstIterator DynamicArray<T, Allocator>::begin() const
	{
		return GetBuffer();
	}

	template<typename T, typename Allocator>
	typename DynamicArray<T, Allocator>::ConstIterator DynamicArray<T, Allocator>::end() const
	{
		return GetBuffer() + count;
	}

#pragma endregion
}