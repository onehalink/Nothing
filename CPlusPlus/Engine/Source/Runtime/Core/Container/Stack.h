#pragma once

#include "DynamicArray.h"



namespace Engine
{
	template<typename T, typename Allocator = DefaultAllocator<T>>
	class Stack
	{
	public:
		Stack();
		Stack(SizeType capacity);
		Stack(Stack<T, Allocator>&& other);
		Stack(const Stack<T, Allocator>& other);
		~Stack();


		// Remove the element at the top of stack and return it
		T& Pop();
		// Insert a element at the top of stack
		Void Push(T&& element);
		Void Push(const T& element);

		Void Clear();


		// Return the element at the top of stack without removing it
		T& Top();
		const T& Top() const;

		Bool IsEmpty() const;


		T* GetBuffer();
		const T* GetBuffer() const;
		SizeType GetCount() const;
		SizeType GetCapacity() const;


		Stack<T, Allocator>& operator=(Stack<T, Allocator>&& other);
		Stack<T, Allocator>& operator=(const Stack<T, Allocator>& other);
	public:
		class Iterator
		{
		public:
			Iterator(T* pointer);


			T& operator*();
			Iterator& operator++();
			Bool operator!=(Iterator other) const;
		private:
			T* pointer;
		};


		Iterator begin();
		Iterator end();

		const Iterator begin() const;
		const Iterator end() const;
	private:
		DynamicArray<T, Allocator> storage;
	};


#pragma region Details

	template<typename T, typename Allocator>
	Stack<T, Allocator>::Stack()
	{

	}

	template<typename T, typename Allocator>
	Stack<T, Allocator>::Stack(SizeType capacity)
		: storage(capacity)
	{

	}

	template<typename T, typename Allocator>
	Stack<T, Allocator>::Stack(Stack<T, Allocator>&& other)
		: storage( Move( other.storage ) )
	{

	}

	template<typename T, typename Allocator>
	Stack<T, Allocator>::Stack(const Stack<T, Allocator>& other)
		: storage( other.storage )
	{

	}

	template<typename T, typename Allocator>
	Stack<T, Allocator>::~Stack()
	{

	}

	template<typename T, typename Allocator>
	T& Stack<T, Allocator>::Pop()
	{
		SizeType index = GetCount() - 1;
		storage.RemoveAt(index);

		return GetBuffer()[index];
	}

	template<typename T, typename Allocator>
	Void Stack<T, Allocator>::Push(T&& element)
	{
		storage.Add( Forward<T>(element) );
	}

	template<typename T, typename Allocator>
	Void Stack<T, Allocator>::Push(const T& element)
	{
		storage.Add(element);
	}

	template<typename T, typename Allocator>
	Void Stack<T, Allocator>::Clear()
	{
		storage.Clear();
	}

	template<typename T, typename Allocator>
	T& Stack<T, Allocator>::Top()
	{
		return *begin();
	}

	template<typename T, typename Allocator>
	const T& Stack<T, Allocator>::Top() const
	{
		return *begin();
	}

	template<typename T, typename Allocator>
	Bool Stack<T, Allocator>::IsEmpty() const
	{
		return GetCount() == 0;
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
		return storage.GetCount();
	}

	template<typename T, typename Allocator>
	SizeType Stack<T, Allocator>::GetCapacity() const
	{
		return storage.GetCapacity();
	}

	template<typename T, typename Allocator>
	Stack<T, Allocator>& Stack<T, Allocator>::operator=(Stack<T, Allocator>&& other)
	{
		storage = Move( other.storage );

		return *this;
	}

	template<typename T, typename Allocator>
	Stack<T, Allocator>& Stack<T, Allocator>::operator=(const Stack<T, Allocator>& other)
	{
		storage	= other.storage;

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
	Bool Stack<T, Allocator>::Iterator::operator!=(Iterator other) const
	{
		return pointer != other.pointer;
	}

	template<typename T, typename Allocator>
	typename Stack<T, Allocator>::Iterator Stack<T, Allocator>::begin()
	{
		return GetBuffer() + GetCount() - 1;
	}

	template<typename T, typename Allocator>
	typename Stack<T, Allocator>::Iterator Stack<T, Allocator>::end()
	{
		return GetBuffer() - 1;
	}

	template<typename T, typename Allocator>
	const typename Stack<T, Allocator>::Iterator Stack<T, Allocator>::begin() const
	{
		// convert to T* from const T*

		return (T*)GetBuffer() + GetCount() - 1;
	}

	template<typename T, typename Allocator>
	const typename Stack<T, Allocator>::Iterator Stack<T, Allocator>::end() const
	{
		return (T*)GetBuffer() - 1;
	}

#pragma endregion
}