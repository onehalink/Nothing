#pragma once

#include "String.h"



namespace Engine
{
	template<typename T>
	class StringBuilder
	{
	public:
		StringBuilder();
		StringBuilder(SizeType capacity);
		StringBuilder(const StringBuilder<T>& other);
		StringBuilder(StringBuilder<T>&& other);
		~StringBuilder();


		StringBuilder<T>& Append(const T* rawString, Int32 length = -1);
		StringBuilder<T>& Append(const String<T>& string);

		String<T> ToString() const;


		T* GetBuffer();
		const T* GetBuffer() const;
		SizeType GetCount() const;
		SizeType GetCapacity() const;


		StringBuilder<T>& operator=(const StringBuilder<T>& other);
		StringBuilder<T>& operator=(StringBuilder<T>&& other);
	private:
		Void Expand(SizeType requiredCount);
		Void CopyFrom(const StringBuilder<T>& other);
		Void SwapWith(StringBuilder<T>& other);
	private:
		Memory<T> storage;

		SizeType count;
	};


#pragma region Details

	template<typename T>
	StringBuilder<T>::StringBuilder()
		: count(0)
	{

	}

	template<typename T>
	StringBuilder<T>::StringBuilder(SizeType capacity)
		: storage(capacity), count(0)
	{

	}

	template<typename T>
	StringBuilder<T>::StringBuilder(const StringBuilder<T>& other)
	{
		CopyFrom(other);
	}

	template<typename T>
	StringBuilder<T>::StringBuilder(StringBuilder<T>&& other)
	{
		SwapWith(other);
	}

	template<typename T>
	StringBuilder<T>::~StringBuilder()
	{

	}

	template<typename T>
	StringBuilder<T>& StringBuilder<T>::Append(const T* rawString, Int32 length)
	{
		if ( length == -1 )
			length = StringLength(rawString);

		SizeType required = count + length;
		if ( required > GetCapacity() )
			Expand(required);

		MemoryOp::Copy( rawString, GetBuffer() + count, sizeof(T) * length );
		count += length;

		return *this;
	}

	template<typename T>
	StringBuilder<T>& StringBuilder<T>::Append(const String<T>& string)
	{
		return Append( string.GetBuffer(), string.GetCount() );
	}

	template<typename T>
	String<T> StringBuilder<T>::ToString() const
	{
		Memory<T> ret( count + 1 );
		SetNullForRawString(ret);

		MemoryOp::Copy( GetBuffer(), ret.GetBuffer(), sizeof(T) * count );

		return ret;
	}

	template<typename T>
	T* StringBuilder<T>::GetBuffer()
	{
		return storage.GetBuffer();
	}

	template<typename T>
	const T* StringBuilder<T>::GetBuffer() const
	{
		return storage.GetBuffer();
	}

	template<typename T>
	SizeType StringBuilder<T>::GetCount() const
	{
		return count;
	}

	template<typename T>
	SizeType StringBuilder<T>::GetCapacity() const
	{
		return storage.GetCount();
	}

	template<typename T>
	StringBuilder<T>& StringBuilder<T>::operator=(const StringBuilder<T>& other)
	{
		CopyFrom(other);

		return *this;
	}

	template<typename T>
	StringBuilder<T>& StringBuilder<T>::operator=(StringBuilder<T>&& other)
	{
		SwapWith(other);

		return *this;
	}

	template<typename T>
	Void StringBuilder<T>::Expand(SizeType requiredCount)
	{
		constexpr SizeType MinimumCapacity	= 64;
		constexpr RealType ExpandFactor		= 1.25;


		SizeType capacity = GetCapacity();
		{
			if ( capacity < MinimumCapacity )
				capacity = MinimumCapacity;

			while ( capacity < requiredCount )
				capacity *= ExpandFactor;
		}

		Memory<T> temporary(capacity);
		MemoryOp::Copy( GetBuffer(), temporary.GetBuffer(), sizeof(T) * count );

		storage = Move(temporary);
	}

	template<typename T>
	Void StringBuilder<T>::CopyFrom(const StringBuilder<T>& other)
	{
		storage	= other.storage;
		count	= other.count;
	}

	template<typename T>
	Void StringBuilder<T>::SwapWith(StringBuilder<T>& other)
	{
		storage = Move( other.storage );

		Swap( &count, &other.count );
	}

#pragma endregion
}