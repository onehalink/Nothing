#pragma once

#include "../CoreMinimal.h"
#include "../Memory.h"

#include "String.h"
#include "StringView.h"



namespace Engine
{
	template<typename T>
	class StringBuilder
	{
	public:
		static_assert( IsChar<T>::Value );


		StringBuilder();
		StringBuilder(SizeType capacity);
		StringBuilder(StringBuilder<T>&& other);
		StringBuilder(const StringBuilder<T>& other);
		StringBuilder<T>& operator=(StringBuilder<T>&& other);
		StringBuilder<T>& operator=(const StringBuilder<T>& other);


		StringBuilder<T>& Append(T value);
		StringBuilder<T>& Append(StringView<T> view);

		Void Clear();


		String<T> ToString() const;


		Bool IsEmpty() const;


		T* GetBuffer();
		const T* GetBuffer() const;
		SizeType GetCount() const;
		SizeType GetCapacity() const;
	private:
		Void Expand(SizeType requiredCount);

		Void SwapWith(StringBuilder<T>& other);
		Void CopyFrom(const StringBuilder<T>& other);
	private:
		Memory<T>	storage;
		SizeType	count;


		// For Visual Studio's natvis file
		#if defined(COMPILER_MSVC) && defined(DEBUG)
		static constexpr SizeType CharSize = sizeof(T);
		#endif
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
	StringBuilder<T>::StringBuilder(StringBuilder<T>&& other)
	{
		SwapWith(other);
	}

	template<typename T>
	StringBuilder<T>::StringBuilder(const StringBuilder<T>& other)
	{
		CopyFrom(other);
	}

	template<typename T>
	StringBuilder<T>& StringBuilder<T>::operator=(StringBuilder<T>&& other)
	{
		SwapWith(other);

		return *this;
	}

	template<typename T>
	StringBuilder<T>& StringBuilder<T>::operator=(const StringBuilder<T>& other)
	{
		CopyFrom(other);

		return *this;
	}

	template<typename T>
	StringBuilder<T>& StringBuilder<T>::Append(T value)
	{
		return Append( { &value, 1 } );
	}

	template<typename T>
	StringBuilder<T>& StringBuilder<T>::Append(StringView<T> view)
	{
		SizeType required = count + view.GetCount();
		if ( required > GetCapacity() )
			Expand(required);

		MemoryCopy( GetBuffer() + count, view.GetBuffer(), view.GetCount() );
		count += view.GetCount();

		return *this;
	}

	template<typename T>
	Void StringBuilder<T>::Clear()
	{
		count = 0;
	}

	template<typename T>
	String<T> StringBuilder<T>::ToString() const
	{
		String<T> result(count);

		MemoryCopy( result.GetBuffer(), GetBuffer(), GetCount() );

		return result;
	}

	template<typename T>
	Bool StringBuilder<T>::IsEmpty() const
	{
		return GetCount() == 0;
	}

	template<typename T>
	T* StringBuilder<T>::GetBuffer()
	{
		return storage.GetBuffer();
	}

	template<typename T>
	const T* StringBuilder<T>::GetBuffer() const
	{
		return const_cast<StringBuilder<T>*>(this)->GetBuffer();
	}

	template<typename T>
	SizeType StringBuilder<T>::GetCount() const
	{
		return count;
	}

	template<typename T>
	inline SizeType StringBuilder<T>::GetCapacity() const
	{
		return storage.GetCount();
	}

	template<typename T>
	Void StringBuilder<T>::Expand(SizeType requiredCount)
	{
		constexpr SizeType MinimumCapacity	= 64;


		SizeType capacity = GetCapacity();
		{
			if ( capacity < MinimumCapacity )
				capacity = MinimumCapacity;

			while ( capacity < requiredCount )
				capacity += capacity / 4;
		}

		decltype(storage) temporary(capacity);
		MemoryCopy( temporary.GetBuffer(), GetBuffer(), GetCount() );

		storage = Move(temporary);
	}

	template<typename T>
	Void StringBuilder<T>::SwapWith(StringBuilder<T>& other)
	{
		storage = Move( other.storage );

		Swap( &count, &other.count );
	}

	template<typename T>
	Void StringBuilder<T>::CopyFrom(const StringBuilder<T>& other)
	{
		storage	= other.storage;
		count	= other.count;
	}

#pragma endregion
}