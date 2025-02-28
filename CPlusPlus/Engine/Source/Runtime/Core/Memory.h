#pragma once

#include "CoreMinimal.h"



namespace Engine::Template
{
	template<typename A>
	class Memory
	{
	public:
		using AllocatorType	= A;
		using ElementType	= typename AllocatorType::ElementType;

		using ThisType		= Memory<AllocatorType>;
		template<typename OtherAllocatorType>
		using OtherType		= Memory<OtherAllocatorType>;


		Memory();
		Memory(SizeType count);
		Memory(ThisType&& other);
		Memory(const ThisType& other);
		ThisType& operator=(ThisType&& other);
		ThisType& operator=(const ThisType& other);
		template<typename B> Memory(OtherType<B>&& other);
		template<typename B> Memory(const OtherType<B>& other);
		template<typename B> ThisType& operator=(OtherType<B>&& other);
		template<typename B> ThisType& operator=(const OtherType<B>& other);
		~Memory();


		ElementType* GetBuffer();
		const ElementType* GetBuffer() const;
		SizeType GetCount() const;


		ElementType& operator[](SizeType index);
		const ElementType& operator[](SizeType index) const;
	private:
		template<typename B> Void SwapWith(OtherType<B>& other);
		template<typename B> Void CopyFrom(const OtherType<B>& other);
	private:
		AllocatorType	allocator;

		ElementType*	buffer;
		SizeType		count;
	};


#pragma region Details

	template<typename A>
	Memory<A>::Memory()
		: buffer(nullptr), count(0)
	{

	}

	template<typename A>
	Memory<A>::Memory(SizeType count)
		: buffer( allocator.Allocate(count) ), count(count)
	{

	}

	template<typename A>
	Memory<A>::Memory(ThisType&& other)
	{
		buffer = nullptr;

		SwapWith(other);
	}

	template<typename A>
	Memory<A>::Memory(const ThisType& other)
	{
		CopyFrom(other);
	}

	template<typename A>
	typename Memory<A>::ThisType& Memory<A>::operator=(ThisType&& other)
	{
		SwapWith(other);

		return *this;
	}

	template<typename A>
	typename Memory<A>::ThisType& Memory<A>::operator=(const ThisType& other)
	{
		this->~Memory();
		CopyFrom(other);

		return *this;
	}

	template<typename A>
	template<typename B>
	Memory<A>::Memory(OtherType<B>&& other)
	{
		buffer = nullptr;

		SwapWith(other);
	}

	template<typename A>
	template<typename B>
	Memory<A>::Memory(const OtherType<B>& other)
	{
		CopyFrom(other);
	}

	template<typename A>
	template<typename B>
	typename Memory<A>::ThisType& Memory<A>::operator=(OtherType<B>&& other)
	{
		SwapWith(other);

		return *this;
	}

	template<typename A>
	template<typename B>
	typename Memory<A>::ThisType& Memory<A>::operator=(const OtherType<B>& other)
	{
		this->~Memory();
		CopyFrom(other);

		return *this;
	}

	template<typename A>
	Memory<A>::~Memory()
	{
		allocator.Deallocate(buffer, count);
	}

	template<typename A>
	typename Memory<A>::ElementType* Memory<A>::GetBuffer()
	{
		return buffer;
	}

	template<typename A>
	const typename Memory<A>::ElementType* Memory<A>::GetBuffer() const
	{
		return buffer;
	}

	template<typename A>
	SizeType Memory<A>::GetCount() const
	{
		return count;
	}

	template<typename A>
	typename Memory<A>::ElementType& Memory<A>::operator[](SizeType index)
	{
		ASSERT( index < count, "Index out of range" );

		return buffer[index];
	}

	template<typename A>
	const typename Memory<A>::ElementType& Memory<A>::operator[](SizeType index) const
	{
		return const_cast<ThisType*>(this)->operator[](index);
	}

	template<typename A>
	template<typename B>
	Void Memory<A>::SwapWith(OtherType<B>& other)
	{
		allocator = Move( other.allocator );

		Swap( &buffer,	&other.buffer	);
		Swap( &count,	&other.count	);
	}

	template<typename A>
	template<typename B>
	Void Memory<A>::CopyFrom(const OtherType<B>& other)
	{
		allocator	= other.allocator;
		count		= other.count;
		buffer		= allocator.Allocate(count);

		MemoryCopy( GetBuffer(), other.GetBuffer(), other.GetCount() );
	}

#pragma endregion
}


namespace Engine
{
	// Represents a owning contiguous region of arbitrary memory
	template<typename T>
	using Memory = Template::Memory<DefaultAllocator<T>>;
}