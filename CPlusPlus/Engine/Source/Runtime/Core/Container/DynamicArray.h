#pragma once

#include "../CoreMinimal.h"



namespace Engine::Template
{
	template<typename A>
	class DynamicArray
	{
	public:
		using AllocatorType	= A;
		using ElementType	= typename AllocatorType::ElementType;

		using ThisType		= DynamicArray<AllocatorType>;
		template<typename OtherAllocatorType>
		using OtherType		= DynamicArray<OtherAllocatorType>;


		DynamicArray();
		DynamicArray(SizeType capacity);
		template<typename ...Elements>
		DynamicArray(InPlace, Elements&&... elements);
		DynamicArray(ThisType&& other);
		DynamicArray(const ThisType& other);
		ThisType& operator=(ThisType&& other);
		ThisType& operator=(const ThisType& other);
		template<typename B> DynamicArray(OtherType<B>&& other);
		template<typename B> DynamicArray(const OtherType<B>& other);
		template<typename B> ThisType& operator=(OtherType<B>&& other);
		template<typename B> ThisType& operator=(const OtherType<B>& other);
		~DynamicArray();


		Void Add(ElementType&& element);
		Void Add(const ElementType& element);
		Void InsertAt(SizeType index, ElementType&& element);
		Void InsertAt(SizeType index, const ElementType& element);
		Void RemoveAt(SizeType index);

		Void Clear();


		ElementType* GetBuffer();
		const ElementType* GetBuffer() const;
		SizeType GetCount() const;
		SizeType GetCapacity() const;


		ElementType& operator[](SizeType index);
		const ElementType& operator[](SizeType index) const;
	public:
		template<typename U>
		using IteratorBase = typename Span<ElementType>::template IteratorBase<U>;


		using Iterator		= Engine::Iterator::ContiguousIteratorAdapter<IteratorBase<ElementType>>;
		using ConstIterator	= Engine::Iterator::ContiguousIteratorAdapter<IteratorBase<const ElementType>>;


		Iterator begin();
		Iterator end();

		ConstIterator begin() const;
		ConstIterator end() const;
	private:
		Void Expand();

		template<typename B> Void SwapWith(OtherType<B>& other);
		template<typename B> Void CopyFrom(const OtherType<B>& other);
	private:
		AllocatorType	allocator;

		ElementType*	buffer;
		SizeType		count;
		SizeType		capacity;
	};


#pragma region Details

	template<typename A>
	DynamicArray<A>::DynamicArray()
		: buffer(nullptr), count(0), capacity(0)
	{

	}

	template<typename A>
	DynamicArray<A>::DynamicArray(SizeType capacity)
		: buffer( allocator.Allocate(capacity) ), count(0), capacity(capacity)
	{

	}

	template<typename A>
	template<typename ...Elements>
	DynamicArray<A>::DynamicArray(InPlace, Elements&&... elements)
	{
		static_assert( And<IsConvertible<Elements, ElementType> ...>::Value );


		capacity = count = sizeof...(elements);

		buffer = allocator.Allocate(capacity);
		ParameterPack::CopyTo( buffer, Forward<Elements>(elements)... );
	}

	template<typename A>
	DynamicArray<A>::DynamicArray(ThisType&& other)
	{
		buffer = nullptr;

		SwapWith(other);
	}
	template<typename A>
	DynamicArray<A>::DynamicArray(const ThisType& other)
	{
		CopyFrom(other);
	}

	template<typename A>
	typename DynamicArray<A>::ThisType& DynamicArray<A>::operator=(ThisType&& other)
	{
		SwapWith(other);

		return *this;
	}

	template<typename A>
	typename DynamicArray<A>::ThisType& DynamicArray<A>::operator=(const ThisType& other)
	{
		this->~DynamicArray();
		CopyFrom(other);

		return *this;
	}

	template<typename A>
	template<typename B>
	DynamicArray<A>::DynamicArray(OtherType<B>&& other)
	{
		buffer = nullptr;

		SwapWith(other);
	}

	template<typename A>
	template<typename B>
	DynamicArray<A>::DynamicArray(const OtherType<B>& other)
	{
		CopyFrom(other);
	}

	template<typename A>
	template<typename B>
	typename DynamicArray<A>::ThisType& DynamicArray<A>::operator=(OtherType<B>&& other)
	{
		SwapWith(other);

		return *this;
	}

	template<typename A>
	template<typename B>
	typename DynamicArray<A>::ThisType& DynamicArray<A>::operator=(const OtherType<B>& other)
	{
		this->~DynamicArray();
		CopyFrom(other);

		return *this;
	}

	template<typename A>
	DynamicArray<A>::~DynamicArray()
	{
		allocator.Deallocate(buffer, capacity);
	}

	template<typename A>
	Void DynamicArray<A>::Add(ElementType&& element)
	{
		if ( count == capacity )
			Expand();

		buffer[ count++ ] = Move(element);
	}

	template<typename A>
	Void DynamicArray<A>::Add(const ElementType& element)
	{
		if ( count == capacity )
			Expand();

		buffer[ count++ ] = element;
	}

	template<typename A>
	Void DynamicArray<A>::InsertAt(SizeType index, ElementType&& element)
	{
		ASSERT( index < count, "Index out of range" );

		if ( count == capacity )
			Expand();

		++count;
		for (SizeType iteration = count - 1; iteration > index; --iteration)
			buffer[iteration] = Move( buffer[ iteration - 1 ] );

		buffer[index] = Move(element);
	}

	template<typename A>
	Void DynamicArray<A>::InsertAt(SizeType index, const ElementType& element)
	{
		ASSERT( index < count, "Index out of range" );

		if ( count == capacity )
			Expand();

		++count;
		for (SizeType iteration = count - 1; iteration > index; --iteration)
			buffer[iteration] = Move( buffer[ iteration - 1 ] );

		buffer[index] = element;
	}

	template<typename A>
	Void DynamicArray<A>::RemoveAt(SizeType index)
	{
		ASSERT( index < count, "Index out of range" );

		for (SizeType iteration = index + 1; iteration < count; ++iteration)
			buffer[ iteration - 1 ] = Move( buffer[iteration] );

		--count;
	}

	template<typename A>
	Void DynamicArray<A>::Clear()
	{
		count = 0;
	}

	template<typename A>
	typename DynamicArray<A>::ElementType* DynamicArray<A>::GetBuffer()
	{
		return buffer;
	}

	template<typename A>
	const typename DynamicArray<A>::ElementType* DynamicArray<A>::GetBuffer() const
	{
		return const_cast<ThisType*>(this)->GetBuffer();
	}

	template<typename A>
	SizeType DynamicArray<A>::GetCount() const
	{
		return count;
	}

	template<typename A>
	SizeType DynamicArray<A>::GetCapacity() const
	{
		return capacity;
	}

	template<typename A>
	typename DynamicArray<A>::ElementType& DynamicArray<A>::operator[](SizeType index)
	{
		return buffer[index];
	}

	template<typename A>
	const typename DynamicArray<A>::ElementType& DynamicArray<A>::operator[](SizeType index) const
	{
		return const_cast<ThisType*>(this)->operator[](index);
	}

	template<typename A>
	typename DynamicArray<A>::Iterator DynamicArray<A>::begin()
	{
		return { InPlace(), buffer };
	}

	template<typename A>
	typename DynamicArray<A>::Iterator DynamicArray<A>::end()
	{
		return { InPlace(), buffer + count };
	}

	template<typename A>
	typename DynamicArray<A>::ConstIterator DynamicArray<A>::begin() const
	{
		return { InPlace(), buffer };
	}

	template<typename A>
	typename DynamicArray<A>::ConstIterator DynamicArray<A>::end() const
	{
		return { InPlace(), buffer + count };
	}

	template<typename A>
	Void DynamicArray<A>::Expand()
	{
		constexpr SizeType MinimumCapacity	= 8;


		if ( capacity < MinimumCapacity )
			capacity = MinimumCapacity;
		else
			capacity += capacity / 2;

		ElementType* temporary = allocator.Allocate(capacity);
		for (SizeType index = 0; index < count; ++index)
			temporary[index] = Move( buffer[index] );

		this->~DynamicArray();
		buffer = temporary;
	}

	template<typename A>
	template<typename B>
	Void DynamicArray<A>::SwapWith(OtherType<B>& other)
	{
		allocator = Move( other.allocator );

		Swap( &buffer,		&other.buffer	);
		Swap( &count,		&other.count	);
		Swap( &capacity,	&other.capacity	);
	}

	template<typename A>
	template<typename B>
	Void DynamicArray<A>::CopyFrom(const OtherType<B>& other)
	{
		allocator = other.allocator;

		capacity = count = other.count;

		buffer = allocator.Allocate(capacity);
		for (SizeType index = 0; index < count; ++index)
			buffer[index] = other[index];
	}

#pragma endregion
}


namespace Engine
{
	template<typename T>
	using DynamicArray = Template::DynamicArray<DefaultAllocator<T>>;
}
