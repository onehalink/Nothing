#pragma once

#include "../InPlace.h"
#include "../Template.h"

#include "../Allocator/DefaultAllocator.h"

#include "../Mathematics/NumericCalculation.h"



namespace Engine
{
	// Represent a contiguous region of arbitrary memory that allocated on the heap
	template<typename T, typename Allocator = DefaultAllocator<T>>
	class Span
	{
	public:
		Span();
		Span(SizeType count /** preallocated for storing elements */);
		template<typename ...Parameters> Span(InPlace, Parameters&&... parameters);
		Span(const Span<T, Allocator>& other);
		Span(Span<T, Allocator>&& other);
		~Span();


		Void Expand(SizeType minimumCapacity = 8, RealType expandFactor = 1.5);


		T* GetBuffer();
		const T* GetBuffer() const;
		SizeType GetCount() const;


		Span<T, Allocator>& operator=(const Span<T, Allocator>& other);
		Span<T, Allocator>& operator=(Span<T, Allocator>&& other);

		T& operator[](SizeType index);
		const T& operator[](SizeType index) const;
	private:
		Void CopyFrom(const Span<T, Allocator>& other);
	private:
		Allocator allocator{};

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
	Span<T, Allocator>::Span(SizeType count)
		: buffer( allocator.Allocate(count) ), count(count)
	{

	}

	template<typename T, typename Allocator>
	template<typename ...Parameters>
	Span<T, Allocator>::Span(InPlace, Parameters&&... parameters)
	{
		count	= sizeof...(parameters);
		buffer	= allocator.Allocate(count);

		ParameterPackHelper::CopyTo( buffer, Forward<Parameters>(parameters)... );
	}

	template<typename T, typename Allocator>
	Span<T, Allocator>::Span(const Span<T, Allocator>& other)
	{
		CopyFrom(other);
	}

	template<typename T, typename Allocator>
	Span<T, Allocator>::Span(Span<T, Allocator>&& other)
	{
		allocator = Move( other.allocator );

		buffer	= other.buffer;
		count	= other.count;

		other.buffer = nullptr;
	}

	template<typename T, typename Allocator>
	Span<T, Allocator>::~Span()
	{
		allocator.Deallocate(buffer, count);
	}

	template<typename T, typename Allocator>
	Void Span<T, Allocator>::Expand(SizeType minimumCapacity, RealType expandFactor)
	{
		SizeType capacity;
		if ( count < minimumCapacity )
			capacity = minimumCapacity;
		else
			capacity = count * expandFactor;

		T* temporary = allocator.Allocate(capacity);
		for (SizeType index = 0; index < count; index++)
			temporary[index] = Move( buffer[index] );

		{
			this->~Span();

			buffer	= temporary;
			count	= capacity;
		}
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
		allocator = Move( other.allocator );

		Swap( &buffer,	&other.buffer	);
		Swap( &count,	&other.count	);

		return *this;
	}

	template<typename T, typename Allocator>
	T& Span<T, Allocator>::operator[](SizeType index)
	{
		return buffer[index];
	}

	template<typename T, typename Allocator>
	const T& Span<T, Allocator>::operator[](SizeType index) const
	{
		return buffer[index];
	}

	template<typename T, typename Allocator>
	Void Span<T, Allocator>::CopyFrom(const Span<T, Allocator>& other)
	{
		allocator = other.allocator;

		count	= other.count;
		buffer	= allocator.Allocate(count);

		for (SizeType index = 0; index < count; index++)
			buffer[index] = other[index];
	}

#pragma endregion 
}