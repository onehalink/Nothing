#pragma once

#include "Assert.h"
#include "Buffer.h"
#include "Type.h"

#include "Iterator/Adapter.h"



namespace Engine
{
	// Represents a non-owning contiguous region of arbitrary memory
	template<typename T> class Span;
	template<typename T> using ReadOnlySpan = Span<const T>;


	template<typename T>
	class Span
	{
	public:
		Span();
		Span(T& value);
		Span(T* buffer, SizeType count);


		Span<T> Slice(SizeType startIndex);
		Span<T> Slice(SizeType startIndex, SizeType count);


		T* GetBuffer();
		SizeType GetCount();


		T& operator[](SizeType index);

		Bool operator==(Span<T> other);
		Bool operator!=(Span<T> other);
	public:
		template<typename U>
		class IteratorBase
		{
		public:
			using ElementType	= U;
			using DistanceType	= Int32;


			IteratorBase(ElementType* pointer = nullptr) : pointer(pointer) {}


			ElementType& Dereference() const { return *pointer; }
			Void Increment(DistanceType distance) { pointer += distance; }
			Void Decrement(DistanceType distance) { pointer -= distance; }
			DistanceType Distance(const IteratorBase<ElementType>& iterator) const { return pointer - iterator.pointer; }
			Bool Equal(const IteratorBase<ElementType>& iterator) const { return pointer == iterator.pointer; }
		private:
			ElementType* pointer;
		};


		using Iterator = Engine::Iterator::ContiguousIteratorAdapter<IteratorBase<T>>;


		Iterator begin();
		Iterator end();
	private:
		T*			buffer;
		SizeType	count;
	};


#pragma region Details

	template<typename T>
	Span<T>::Span()
		: buffer(nullptr), count(0)
	{

	}

	template<typename T>
	Span<T>::Span(T& value)
		: Span( &value, 1 )
	{

	}

	template<typename T>
	Span<T>::Span(T* buffer, SizeType count)
		: buffer(buffer), count(count)
	{

	}

	template<typename T>
	Span<T> Span<T>::Slice(SizeType startIndex)
	{
		ASSERT( startIndex <= count, "Index out of range" );

		return Slice( startIndex, count - startIndex );
	}

	template<typename T>
	Span<T> Span<T>::Slice(SizeType startIndex, SizeType count)
	{
		ASSERT( startIndex + count <= this->count, "Invalid parameter" );

		return { buffer + startIndex, count };
	}

	template<typename T>
	T* Span<T>::GetBuffer()
	{
		return buffer;
	}

	template<typename T>
	SizeType Span<T>::GetCount()
	{
		return count;
	}

	template<typename T>
	T& Span<T>::operator[](SizeType index)
	{
		ASSERT( index < count, "Index out of range" );

		return buffer[index];
	}

	template<typename T>
	Bool Span<T>::operator==(Span<T> other)
	{
		return count == other.count && MemoryEqual( other.buffer, buffer, count );
	}

	template<typename T>
	Bool Span<T>::operator!=(Span<T> other)
	{
		return !operator==(other);
	}

	template<typename T>
	typename Span<T>::Iterator Span<T>::begin()
	{
		return { InPlace(), buffer };
	}

	template<typename T>
	typename Span<T>::Iterator Span<T>::end()
	{
		return { InPlace(), buffer + count };
	}

#pragma endregion
}