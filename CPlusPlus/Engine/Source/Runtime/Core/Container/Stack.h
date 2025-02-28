#pragma once

#include "../CoreMinimal.h"

#include "../Iterator/Adapter.h"

#include "DynamicArray.h"



namespace Engine::Template
{
	template<typename A>
	class Stack
	{
	public:
		using AllocatorType	= A;
		using ElementType	= typename AllocatorType::ElementType;

		using ThisType		= Stack<AllocatorType>;
		template<typename OtherAllocatorType>
		using OtherType		= Stack<OtherAllocatorType>;


		Stack();
		Stack(SizeType capacity);
		Stack(ThisType&& other);
		Stack(const ThisType& other);
		ThisType& operator=(ThisType&& other);
		ThisType& operator=(const ThisType& other);
		template<typename B> Stack(OtherType<B>&& other);
		template<typename B> Stack(const OtherType<B>& other);
		template<typename B> ThisType& operator=(OtherType<B>&& other);
		template<typename B> ThisType& operator=(const OtherType<B>& other);


		// Remove the element at the top of stack and return it
		ElementType& Pop();
		// Insert a element at the top of stack
		Void Push(ElementType&& element);
		Void Push(const ElementType& element);

		Void Clear();


		// Return the element at the top of stack without removing it
		ElementType& Top();
		const ElementType& Top() const;

		Bool IsEmpty() const;


		SizeType GetCount() const;
	public:
		template<typename U>
		class IteratorBase
		{
		public:
			using ElementType	= U;
			using DistanceType	= Int32;


			IteratorBase(ElementType* pointer = nullptr) : pointer(pointer) {}


			ElementType& Dereference() const { return *pointer; }
			Void Increment() { --pointer; }
			Bool Equal(const IteratorBase<ElementType>& iterator) const { return pointer == iterator.pointer; }
		private:
			ElementType* pointer;
		};


		using Iterator		= Engine::Iterator::ForwardIteratorAdapter<IteratorBase<ElementType>>;
		using ConstIterator	= Engine::Iterator::ForwardIteratorAdapter<IteratorBase<const ElementType>>;


		Iterator begin();
		Iterator end();

		ConstIterator begin() const;
		ConstIterator end() const;
	private:
		DynamicArray<AllocatorType> storage;
	};


#pragma region Details

	template<typename A>
	Stack<A>::Stack()
	{

	}

	template<typename A>
	Stack<A>::Stack(SizeType capacity)
		: storage(capacity)
	{

	}

	template<typename A>
	Stack<A>::Stack(ThisType&& other)
		: storage( Move( other.storage ) )
	{

	}

	template<typename A>
	Stack<A>::Stack(const ThisType& other)
		: storage( other.storage )
	{

	}

	template<typename A>
	typename Stack<A>::ThisType& Stack<A>::operator=(ThisType&& other)
	{
		storage = Move( other.storage );

		return *this;
	}

	template<typename A>
	typename Stack<A>::ThisType& Stack<A>::operator=(const ThisType& other)
	{
		storage = other.storage;

		return *this;
	}

	template<typename A>
	template<typename B>
	Stack<A>::Stack(OtherType<B>&& other)
		: storage( Move( other.storage ) )
	{

	}

	template<typename A>
	template<typename B>
	Stack<A>::Stack(const OtherType<B>& other)
		: storage( other.storage )
	{

	}

	template<typename A>
	template<typename B>
	typename Stack<A>::ThisType& Stack<A>::operator=(OtherType<B>&& other)
	{
		storage = Move( other.storage );

		return *this;
	}

	template<typename A>
	template<typename B>
	typename Stack<A>::ThisType& Stack<A>::operator=(const OtherType<B>& other)
	{
		storage = other.storage;

		return *this;
	}

	template<typename A>
	typename Stack<A>::ElementType& Stack<A>::Pop()
	{
		ASSERT( !IsEmpty(), "Stack is empty" );

		SizeType index = GetCount() - 1;
		storage.RemoveAt(index);

		return storage[index];
	}

	template<typename A>
	Void Stack<A>::Push(ElementType&& element)
	{
		storage.Add( Move(element) );
	}

	template<typename A>
	Void Stack<A>::Push(const ElementType& element)
	{
		storage.Add(element);
	}

	template<typename A>
	Void Stack<A>::Clear()
	{
		storage.Clear();
	}

	template<typename A>
	typename Stack<A>::ElementType& Stack<A>::Top()
	{
		ASSERT( !IsEmpty(), "Stack is empty" );

		return *begin();
	}

	template<typename A>
	const typename Stack<A>::ElementType& Stack<A>::Top() const
	{
		return const_cast<ThisType*>(this)->Top();
	}

	template<typename A>
	Bool Stack<A>::IsEmpty() const
	{
		return GetCount() == 0;
	}

	template<typename A>
	SizeType Stack<A>::GetCount() const
	{
		return storage.GetCount();
	}

	template<typename A>
	typename Stack<A>::Iterator Stack<A>::begin()
	{
		return { InPlace(), storage.GetBuffer() + GetCount() - 1 };
	}

	template<typename A>
	typename Stack<A>::Iterator Stack<A>::end()
	{
		return { InPlace(), storage.GetBuffer() - 1 };
	}

	template<typename A>
	typename Stack<A>::ConstIterator Stack<A>::begin() const
	{
		return { InPlace(), storage.GetBuffer() + GetCount() - 1 };
	}

	template<typename A>
	typename Stack<A>::ConstIterator Stack<A>::end() const
	{
		return { InPlace(), storage.GetBuffer() - 1 };
	}

#pragma endregion
}


namespace Engine
{
	template<typename T>
	using Stack = Template::Stack<DefaultAllocator<T>>;
}