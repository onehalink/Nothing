#pragma once

#include "../Memory.h"

#include "../Allocator/DefaultAllocator.h"



namespace Engine
{
	// Represent a contiguous region of arbitrary memory that allocated on the heap
	template<typename T, typename Allocator = DefaultAllocator<T>>
	class Span
	{
	public:
		Span();
		Span(SizeType requiredCount);
		Span(const Span<T, Allocator>& other);
		Span(Span<T, Allocator>&& other);
		~Span();


		T* GetBuffer();
		const T* GetBuffer() const;
		SizeType GetCount() const;


		Span<T, Allocator>& operator=(const Span<T, Allocator>& other);
		Span<T, Allocator>& operator=(Span<T, Allocator>&& other);

		T& operator[](SizeType index);
		const T& operator[](SizeType index) const;
	public:
		using Iterator		= T*;
		using ConstIterator = const T* const;


		Iterator begin();
		Iterator end();

		ConstIterator begin() const;
		ConstIterator end() const;
	private:
		Void CopyFrom(const Span<T, Allocator>& other);
		Void SwapWith(Span<T, Allocator>& other);
	private:
		Allocator allocator;

		T*			buffer;
		SizeType	count;
	};


#pragma region Details

	template<typename T, typename Allocator>
	Span<T, Allocator>::Span()
		: buffer(nullptr), count(0)
	{

	}

	template<typename T, typename Allocator>
	Span<T, Allocator>::Span(SizeType requiredCount)
		: buffer( allocator.Allocate(requiredCount) ), count(requiredCount)
	{

	}

	template<typename T, typename Allocator>
	Span<T, Allocator>::Span(const Span<T, Allocator>& other)
	{
		CopyFrom(other);
	}

	template<typename T, typename Allocator>
	Span<T, Allocator>::Span(Span<T, Allocator>&& other)
	{
		buffer = nullptr;

		SwapWith(other);
	}

	template<typename T, typename Allocator>
	Span<T, Allocator>::~Span()
	{
		allocator.Deallocate(buffer, count);
	}

	template<typename T, typename Allocator>
	T* Span<T, Allocator>::GetBuffer()
	{
		return buffer;
	}

	template<typename T, typename Allocator>
	const T* Span<T, Allocator>::GetBuffer() const
	{
		return buffer;
	}

	template<typename T, typename Allocator>
	SizeType Span<T, Allocator>::GetCount() const
	{
		return count;
	}

	template<typename T, typename Allocator>
	Span<T, Allocator>& Span<T, Allocator>::operator=(const Span<T, Allocator>& other)
	{
		this->~Span();
		CopyFrom(other);

		return *this;
	}

	template<typename T, typename Allocator>
	Span<T, Allocator>& Span<T, Allocator>::operator=(Span<T, Allocator>&& other)
	{
		SwapWith(other);

		return *this;
	}

	template<typename T, typename Allocator>
	T& Span<T, Allocator>::operator[](SizeType index)
	{
		ASSERT( index < count, "Index output of range" );


		return buffer[index];
	}

	template<typename T, typename Allocator>
	const T& Span<T, Allocator>::operator[](SizeType index) const
	{
		ASSERT( index < count, "Index output of range" );


		return buffer[index];
	}

	template<typename T, typename Allocator>
	typename Span<T, Allocator>::Iterator Span<T, Allocator>::begin()
	{
		return buffer;
	}

	template<typename T, typename Allocator>
	typename Span<T, Allocator>::Iterator Span<T, Allocator>::end()
	{
		return buffer + count;
	}

	template<typename T, typename Allocator>
	typename Span<T, Allocator>::ConstIterator Span<T, Allocator>::begin() const
	{
		return buffer;
	}

	template<typename T, typename Allocator>
	typename Span<T, Allocator>::ConstIterator Span<T, Allocator>::end() const
	{
		return buffer + count;
	}

	template<typename T, typename Allocator>
	Void Span<T, Allocator>::CopyFrom(const Span<T, Allocator>& other)
	{
		allocator = other.allocator;

		count	= other.count;
		buffer	= allocator.Allocate(count);

		Memory::Copy( other.buffer, buffer, sizeof(T) * count );
	}

	template<typename T, typename Allocator>
	Void Span<T, Allocator>::SwapWith(Span<T, Allocator>& other)
	{
		allocator = Move( other.allocator );

		Swap( &buffer,	&other.buffer	);
		Swap( &count,	&other.count	);
	}

#pragma endregion 
}