#pragma once

#include "Type.h"



namespace Engine
{
	template<typename T>
	class DefaultAllocator
	{
	public:
		using ElementType = T;


		template<typename U>
		struct Rebind
		{
			using Other = DefaultAllocator<U>;
		};


		DefaultAllocator();
		template<typename U>
		DefaultAllocator(const DefaultAllocator<U>& other);
		~DefaultAllocator();


		T* Allocate(SizeType count);
		Void Deallocate(T* pointer, SizeType count);
	};


#pragma region Details

	template<typename T>
	DefaultAllocator<T>::DefaultAllocator()
	{

	}

	template<typename T>
	template<typename U>
	DefaultAllocator<T>::DefaultAllocator(const DefaultAllocator<U>& other)
	{

	}

	template<typename T>
	DefaultAllocator<T>::~DefaultAllocator()
	{

	}

	template<typename T>
	T* DefaultAllocator<T>::Allocate(SizeType count)
	{
		return new T[count];
	}

	template<typename T>
	Void DefaultAllocator<T>::Deallocate(T* pointer, SizeType count)
	{
		delete[] pointer;
	}

#pragma endregion
}