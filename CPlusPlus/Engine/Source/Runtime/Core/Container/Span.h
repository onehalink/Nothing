#pragma once

#include "../Error.h"
#include "../Initialization.h"
#include "../InPlace.h"
#include "../Memory.h"
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
		Span(SizeType count /** required for storing elements */, Initialization initialization = Initialization::DoNothing);
		template<typename ...Parameters> Span(InPlace, Parameters&&... parameters);
		Span(const Span<T, Allocator>& other);
		Span(Span<T, Allocator>&& other);
		~Span();


		Void Expand(SizeType minimumCount = 8, RealType expandFactor = 1.5);


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
	Span<T, Allocator>::Span(SizeType count, Initialization initialization)
		: buffer( allocator.Allocate(count) ), count(count)
	{
		if( initialization == Initialization::ForceToZeroMemory )
			if constexpr ( IsTriviallyCopyable<T>::Value )
				Memory::Clear( buffer, sizeof(T) * count );
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
	Void Span<T, Allocator>::Expand(SizeType minimumCount, RealType expandFactor)
	{
		SizeType required;
		if ( count < minimumCount )
			required = minimumCount;
		else
			required = count * expandFactor;

		T* temporary = allocator.Allocate(required);

		if constexpr ( IsTriviallyCopyable<T>::Value )
			Memory::Copy( buffer, temporary, sizeof(T) * count );
		else
			for (SizeType index = 0; index < count; index++)
				temporary[index] = Move( buffer[index] );

		{
			this->~Span();

			buffer	= temporary;
			count	= required;
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
		ASSERT( index < count, Error::IndexOfRange );


		return buffer[index];
	}

	template<typename T, typename Allocator>
	const T& Span<T, Allocator>::operator[](SizeType index) const
	{
		ASSERT( index < count, Error::IndexOfRange );


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

		if constexpr ( IsTriviallyCopyable<T>::Value )
			Memory::Copy( other.buffer, buffer, sizeof(T) * count );
		else
			for (SizeType index = 0; index < count; index++)
				buffer[index] = other[index];
	}

#pragma endregion 
}