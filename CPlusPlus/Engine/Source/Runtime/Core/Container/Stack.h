#pragma once

#include "Span.h"



namespace Engine
{
	template<typename T, typename Allocator = DefaultAllocator<T>>
	class Stack
	{
	public:
		Stack();
		Stack(SizeType capacity);
		Stack(const Stack<T, Allocator>& other);
		Stack(Stack<T, Allocator>&& other);
		~Stack();


		// Remove the element at the top of stack and return it
		T& Pop();
		// Insert a element at the top of stack
		Void Push(const T& element);
		Void Push(T&& element);
		
		// Return the element at the top of stack without removing it
		T& Top();
		const T& Top() const;

		Void Clear();


		T* GetBuffer();
		const T* GetBuffer() const;
		SizeType GetCount() const;
		SizeType GetCapacity() const;


		Stack<T, Allocator>& operator=(const Stack<T, Allocator>& other);
		Stack<T, Allocator>& operator=(Stack<T, Allocator>&& other);
	private:
		Span<T, Allocator> storage{};

		SizeType count;
	};


#pragma region Details

	template<typename T, typename Allocator>
	Stack<T, Allocator>::Stack()
		: count(0)
	{

	}

	template<typename T, typename Allocator>
	Stack<T, Allocator>::Stack(SizeType capacity)
		: storage(capacity), count(0)
	{

	}

	template<typename T, typename Allocator>
	Stack<T, Allocator>::Stack(const Stack<T, Allocator>& other)
		: storage( other.storage ), count( other.count )
	{

	}

	template<typename T, typename Allocator>
	Stack<T, Allocator>::Stack(Stack<T, Allocator>&& other)
		: storage( Move( other.storage ) ), count( other.count )
	{

	}

	template<typename T, typename Allocator>
	Stack<T, Allocator>::~Stack()
	{

	}

	template<typename T, typename Allocator>
	T& Stack<T, Allocator>::Pop()
	{
		return GetBuffer()[ --count ];
	}

	template<typename T, typename Allocator>
	Void Stack<T, Allocator>::Push(const T& element)
	{
		if ( GetCount() == GetCapacity() )
			storage.Expand();

		GetBuffer()[ count++ ] = element;
	}

	template<typename T, typename Allocator>
	Void Stack<T, Allocator>::Push(T&& element)
	{
		if ( GetCount() == GetCapacity() )
			storage.Expand();

		GetBuffer()[ count++ ] = Forward<T>(element);
	}

	template<typename T, typename Allocator>
	T& Stack<T, Allocator>::Top()
	{
		return GetBuffer()[ count - 1 ];
	}

	template<typename T, typename Allocator>
	const T& Stack<T, Allocator>::Top() const
	{
		return GetBuffer()[ count - 1 ];
	}

	template<typename T, typename Allocator>
	Void Stack<T, Allocator>::Clear()
	{
		count = 0;
	}

	template<typename T, typename Allocator>
	T* Stack<T, Allocator>::GetBuffer()
	{
		return storage.GetBuffer();
	}

	template<typename T, typename Allocator>
	const T* Stack<T, Allocator>::GetBuffer() const
	{
		return storage.GetBuffer();
	}

	template<typename T, typename Allocator>
	SizeType Stack<T, Allocator>::GetCount() const
	{
		return count;
	}

	template<typename T, typename Allocator>
	SizeType Stack<T, Allocator>::GetCapacity() const
	{
		return storage.GetCount();
	}

	template<typename T, typename Allocator>
	Stack<T, Allocator>& Stack<T, Allocator>::operator=(const Stack<T, Allocator>& other)
	{
		storage	= other.storage;
		count	= other.count;

		return *this;
	}

	template<typename T, typename Allocator>
	Stack<T, Allocator>& Stack<T, Allocator>::operator=(Stack<T, Allocator>&& other)
	{
		storage = Move( other.storage );

		Swap( &count, &other.count );

		return *this;
	}

#pragma endregion
}