#pragma once

#include "Memory.h"



namespace Engine
{
	template<typename Allocator = DefaultAllocator<Byte>>
	class BitSet
	{
	public:
		BitSet();
		BitSet(SizeType capacity);
		BitSet(BitSet<Allocator>&& other);
		BitSet(const BitSet<Allocator>& other);
		~BitSet();


		Void Add(Bool value);
		Void InsertAt(SizeType index, Bool value);
		Void RemoveAt(SizeType index);

		Void Clear();


		Byte* GetBuffer();
		const Byte* GetBuffer() const;
		SizeType GetCount() const;
		SizeType GetCapacity() const;


		BitSet<Allocator>& operator=(BitSet<Allocator>&& other);
		BitSet<Allocator>& operator=(const BitSet<Allocator>& other);

		Bool operator[](SizeType index) const;
	public:
		class Iterator
		{
		public:
			Iterator(const BitSet<Allocator>& container, SizeType index);


			Bool operator*();
			Iterator& operator++();
			Bool operator!=(Iterator other) const;
		private:
			BitSet<Allocator>&	container;
			SizeType			index;
		};


		Iterator begin();
		Iterator end();

		const Iterator begin() const;
		const Iterator end() const;
	private:
		Void Expand();
		Void CopyFrom(const BitSet<Allocator>& other);
		Void SwapWith(BitSet<Allocator>& other);

		Void SetBit(SizeType index, Bool value);
	private:
		using Storage = Memory<typename Allocator::ElementType, Allocator>;


		Storage		storage;
		SizeType	count;
	};


#pragma region Details

	template<typename Allocator>
	BitSet<Allocator>::BitSet()
		: storage(0), count(0)
	{

	}

	template<typename Allocator>
	BitSet<Allocator>::BitSet(SizeType capacity)
		: storage( ( capacity + 7 ) / 8 ), count(0)
	{

	}

	template<typename Allocator>
	BitSet<Allocator>::BitSet(BitSet<Allocator>&& other)
	{
		SwapWith(other);
	}

	template<typename Allocator>
	BitSet<Allocator>::BitSet(const BitSet<Allocator>& other)
	{
		CopyFrom(other);
	}

	template<typename Allocator>
	BitSet<Allocator>::~BitSet()
	{

	}

	template<typename Allocator>
	Void BitSet<Allocator>::Add(Bool value)
	{
		if ( count == GetCapacity() )
			Expand();

		SetBit( count++, value );
	}

	template<typename Allocator>
	Void BitSet<Allocator>::InsertAt(SizeType index, Bool value)
	{
		if ( count == GetCapacity() )
			Expand();

		count++;
		for (SizeType iteration = count - 1; iteration > index; iteration--)
			SetBit( iteration, ( *this )[ iteration - 1 ] );

		SetBit(index, value);
	}

	template<typename Allocator>
	Void BitSet<Allocator>::RemoveAt(SizeType index)
	{
		for (SizeType iteration = index + 1; iteration < count; iteration++)
			SetBit( iteration - 1, (*this)[iteration] );

		count--;
	}

	template<typename Allocator>
	Void BitSet<Allocator>::Clear()
	{
		count = 0;
	}

	template<typename Allocator>
	Byte* BitSet<Allocator>::GetBuffer()
	{
		return storage.GetBuffer();
	}

	template<typename Allocator>
	const Byte* BitSet<Allocator>::GetBuffer() const
	{
		return storage.GetBuffer();
	}

	template<typename Allocator>
	SizeType BitSet<Allocator>::GetCount() const
	{
		return count;
	}

	template<typename Allocator>
	SizeType BitSet<Allocator>::GetCapacity() const
	{
		return storage.GetCount() * 8;
	}

	template<typename Allocator>
	BitSet<Allocator>& BitSet<Allocator>::operator=(BitSet<Allocator>&& other)
	{
		SwapWith(other);

		return *this;
	}

	template<typename Allocator>
	BitSet<Allocator>& BitSet<Allocator>::operator=(const BitSet<Allocator>& other)
	{
		CopyFrom(other);

		return *this;
	}

	template<typename Allocator>
	Bool BitSet<Allocator>::operator[](SizeType index) const
	{
		return storage[ index / 8 ] & ( 1 << ( index % 8 ) );
	}

	
	template<typename Allocator>
	BitSet<Allocator>::Iterator::Iterator(const BitSet<Allocator>& container, SizeType index)
		: container( (BitSet<Allocator>&)container ), index(index)
	{

	}

	template<typename Allocator>
	Bool BitSet<Allocator>::Iterator::operator*()
	{
		return container[index];
	}

	template<typename Allocator>
	typename BitSet<Allocator>::Iterator& BitSet<Allocator>::Iterator::operator++()
	{
		index++;

		return *this;
	}

	template<typename Allocator>
	Bool BitSet<Allocator>::Iterator::operator!=(Iterator other) const
	{
		return index != other.index;
	}

	template<typename Allocator>
	typename BitSet<Allocator>::Iterator BitSet<Allocator>::begin()
	{
		return Iterator( *this, 0 );
	}

	template<typename Allocator>
	typename BitSet<Allocator>::Iterator BitSet<Allocator>::end()
	{
		return Iterator( *this, count );
	}

	template<typename Allocator>
	const typename BitSet<Allocator>::Iterator BitSet<Allocator>::begin() const
	{
		return Iterator( *this, 0 );
	}

	template<typename Allocator>
	const typename BitSet<Allocator>::Iterator BitSet<Allocator>::end() const
	{
		return Iterator( *this, count );
	}

	template<typename Allocator>
	Void BitSet<Allocator>::Expand()
	{
		constexpr SizeType MinimumCapacity	= 64;
		constexpr RealType ExpandFactor		= 1.25;


		SizeType capacity = GetCapacity();
		if ( capacity < MinimumCapacity )
			capacity = MinimumCapacity;
		else
			capacity *= ExpandFactor;

		Storage temporary(capacity);
		MemoryCopy( storage.GetBuffer(), temporary.GetBuffer(), ( count + 7 ) / 8 );

		storage = Move(temporary);
	}

	template<typename Allocator>
	Void BitSet<Allocator>::CopyFrom(const BitSet<Allocator>& other)
	{
		storage = other.storage;

		count = other.count;
	}

	template<typename Allocator>
	Void BitSet<Allocator>::SwapWith(BitSet<Allocator>& other)
	{
		storage = Move( other.storage );

		Swap( &count, &other.count );
	}

	template<typename Allocator>
	Void BitSet<Allocator>::SetBit(SizeType index, Bool value)
	{
		Byte set	= 1 << ( index % 8 );
		Byte mask	= ~set;

		Byte& selected = storage[ index / 8 ];

		selected &= mask;
		if (value)
			selected |= set;
	}

#pragma endregion
}
