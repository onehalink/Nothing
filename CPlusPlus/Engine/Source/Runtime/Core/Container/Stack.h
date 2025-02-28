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
		
		Void Clear();

		// Return the element at the top of stack without removing it
		T& Top();
		const T& Top() const;

		Bool IsEmpty() const;


		T* GetBuffer();
		const T* GetBuffer() const;
		SizeType GetCount() const;
		SizeType GetCapacity() const;


		Stack<T, Allocator>& operator=(const Stack<T, Allocator>& other);
		Stack<T, Allocator>& operator=(Stack<T, Allocator>&& other);
	public:
		// Backend iterator
		class Iterator
		{
		public:
			Iterator(T* pointer);


			T& operator*();

			Iterator& operator++();
			Iterator operator++(Int32);

			Bool operator!=(Iterator other) const;
		private:
			T* pointer;
		};


		Iterator begin();
		Iterator end();

		const Iterator begin() const;
		const Iterator end() const;
	private:
		Span<T, Allocator> storage;

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
		ASSERT( !IsEmpty(), Error::Empty );


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
	Void Stack<T, Allocator>::Clear()
	{
		count = 0;
	}

	template<typename T, typename Allocator>
	T& Stack<T, Allocator>::Top()
	{
		ASSERT( !IsEmpty(), Error::Empty );


		return GetBuffer()[ count - 1 ];
	}

	template<typename T, typename Allocator>
	const T& Stack<T, Allocator>::Top() const
	{
		ASSERT( !IsEmpty(), Error::Empty );


		return GetBuffer()[ count - 1 ];
	}

	template<typename T, typename Allocator>
	Bool Stack<T, Allocator>::IsEmpty() const
	{
		return count == 0;
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

	template<typename T, typename Allocator>
	Stack<T, Allocator>::Iterator::Iterator(T* pointer)
		: pointer(pointer)
	{

	}

	template<typename T, typename Allocator>
	T& Stack<T, Allocator>::Iterator::operator*()
	{
		return *pointer;
	}

	template<typename T, typename Allocator>
	typename Stack<T, Allocator>::Iterator& Stack<T, Allocator>::Iterator::operator++()
	{
		pointer--;

		return *this;
	}

	template<typename T, typename Allocator>
	typename Stack<T, Allocator>::Iterator Stack<T, Allocator>::Iterator::operator++(Int32)
	{
		Iterator ret = *this;

		++( *this );

		return ret;
	}

	template<typename T, typename Allocator>
	Bool Stack<T, Allocator>::Iterator::operator !=(Iterator other) const
	{
		return pointer != other.pointer;
	}

	template<typename T, typename Allocator>
	typename Stack<T, Allocator>::Iterator Stack<T, Allocator>::begin()
	{
		return GetBuffer() - 1 + count;
	}

	template<typename T, typename Allocator>
	typename Stack<T, Allocator>::Iterator Stack<T, Allocator>::end()
	{
		return GetBuffer() - 1;
	}

	template<typename T, typename Allocator>
	const typename Stack<T, Allocator>::Iterator Stack<T, Allocator>::begin() const
	{
		return GetBuffer() - 1 + count;
	}

	template<typename T, typename Allocator>
	const typename Stack<T, Allocator>::Iterator Stack<T, Allocator>::end() const
	{
		return GetBuffer() - 1;
	}

#pragma endregion
}