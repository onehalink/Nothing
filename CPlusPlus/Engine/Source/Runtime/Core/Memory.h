#pragma once

#include "CoreMinimal.h"



namespace Engine
{
	// Represent a contiguous region of memory that allocated on the heap
	template<typename T, typename Allocator = DefaultAllocator<T>>
	class Memory
	{
	public:
		Memory();
		Memory(SizeType count);
		Memory(Memory<T, Allocator>&& other);
		Memory(const Memory<T, Allocator>& other);
		~Memory();


		T* GetBuffer();
		const T* GetBuffer() const;
		SizeType GetCount() const;


		Memory<T, Allocator>& operator=(Memory<T, Allocator>&& other);
		Memory<T, Allocator>& operator=(const Memory<T, Allocator>& other);

		T& operator[](SizeType index);
		const T& operator[](SizeType index) const;
	private:
		Void CopyFrom(const Memory<T, Allocator>& other);
		Void SwapWith(Memory<T, Allocator>& other);
	private:
		Allocator	allocator;

		T*			buffer;
		SizeType	count;
	};


#pragma region Details

	template<typename T, typename Allocator>
	Memory<T, Allocator>::Memory()
		: buffer(nullptr), count(0)
	{

	}

	template<typename T, typename Allocator>
	Memory<T, Allocator>::Memory(SizeType count)
		: buffer( allocator.Allocate(count) ), count(count)
	{

	}

	template<typename T, typename Allocator>
	Memory<T, Allocator>::Memory(Memory<T, Allocator>&& other)
	{
		buffer = nullptr;

		SwapWith(other);
	}

	template<typename T, typename Allocator>
	Memory<T, Allocator>::Memory(const Memory<T, Allocator>& other)
	{
		CopyFrom(other);
	}

	template<typename T, typename Allocator>
	Memory<T, Allocator>::~Memory()
	{
		allocator.Deallocate(buffer, count);
	}

	template<typename T, typename Allocator>
	T* Memory<T, Allocator>::GetBuffer()
	{
		return buffer;
	}

	template<typename T, typename Allocator>
	const T* Memory<T, Allocator>::GetBuffer() const
	{
		return buffer;
	}

	template<typename T, typename Allocator>
	SizeType Memory<T, Allocator>::GetCount() const
	{
		return count;
	}

	template<typename T, typename Allocator>
	Memory<T, Allocator>& Memory<T, Allocator>::operator=(Memory<T, Allocator>&& other)
	{
		SwapWith(other);

		return *this;
	}

	template<typename T, typename Allocator>
	Memory<T, Allocator>& Memory<T, Allocator>::operator=(const Memory<T, Allocator>& other)
	{
		this->~Memory();
		CopyFrom(other);

		return *this;
	}

	template<typename T, typename Allocator>
	T& Memory<T, Allocator>::operator[](SizeType index)
	{
		return buffer[index];
	}

	template<typename T, typename Allocator>
	const T& Memory<T, Allocator>::operator[](SizeType index) const
	{
		return buffer[index];
	}

	template<typename T, typename Allocator>
	Void Memory<T, Allocator>::CopyFrom(const Memory<T, Allocator>& other)
	{
		allocator = other.allocator;

		count	= other.count;
		buffer	= allocator.Allocate(count);

		MemoryCopy( other.buffer, buffer, sizeof(T) * count );
	}

	template<typename T, typename Allocator>
	Void Memory<T, Allocator>::SwapWith(Memory<T, Allocator>& other)
	{
		allocator = Move( other.allocator );

		Swap( &buffer,	&other.buffer	);
		Swap( &count,	&other.count	);
	}

#pragma endregion 
}