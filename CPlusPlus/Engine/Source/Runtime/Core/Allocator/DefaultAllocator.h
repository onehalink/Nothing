#pragma once

#include "../Type.h"



namespace Engine
{
	template<typename T>
	class DefaultAllocator
	{
	public:
		using ElementType = T;


		/**
		* Used when need same allocator with different element type
		* 
		* Usage:
		* template<typename T, typename Allocator = DefaultAllocator<T>>
		* class Container
		* {
		*     template<typename SpecificElementType>
		*     NewAllocatorType = typename Allocator::template Rebind<SpecificElementType>::Other
		* };
		*/
		template<typename U>
		struct Rebind
		{
			using Other = DefaultAllocator<U>;
		};


		DefaultAllocator();
		template<typename U>
		DefaultAllocator(const DefaultAllocator<U>& other);
		~DefaultAllocator();


		ElementType* Allocate(SizeType count);
		Void Deallocate(ElementType* pointer, SizeType count);
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
	typename DefaultAllocator<T>::ElementType* DefaultAllocator<T>::Allocate(SizeType count)
	{
		return new ElementType[count];
	}

	template<typename T>
	Void DefaultAllocator<T>::Deallocate(ElementType* pointer, SizeType count)
	{
		delete[] pointer;
	}

#pragma endregion
}