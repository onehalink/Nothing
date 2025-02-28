#pragma once

#include "Mathematics/Numeric.h"

#include "Template/SameAsAny.h"

#include "Buffer.h"
#include "ClassConstructorDestructor.h"
#include "Forward.h"
#include "InPlace.h"
#include "ParameterPack.h"



namespace Engine
{
	template<typename ...Types>
	class Variant
	{
	public:
		static_assert( sizeof...(Types) >= 2, "Must be greater than or equal to 2" );
		static_assert( !SameAsAny<Void, Types ...>::Value, "Incompleted type(Void) is not allowed" );
		static_assert( !( ( ParameterPack::TypeCount<Types, Types ...>::Value >= 2 ) || ... ), "Same types are not allowed" );


		using ThisType = Variant<Types ...>;


		// Default initialize the Variant to the first type in the parameter pack
		Variant();
		// Perform in-place construction of a type into the variant
		template<typename ElementType, typename ...Parameters>
		Variant(InPlaceType<ElementType>, Parameters&&... parameters);
		Variant(ThisType&& other);
		Variant(const ThisType& other);
		ThisType& operator=(ThisType&& other);
		ThisType& operator=(const ThisType& other);
		~Variant();


		// Get a reference to the held value. Bad things can happen if this is called on a variant that does not hold the type asked for
		template<typename ElementType> ElementType& Get();
		template<typename ElementType> const ElementType& Get() const;

		// Set a specifically-typed value into the variant using in-place construction
		template<typename ElementType, typename ...Parameters> Void Emplace(Parameters&&... parameters);
		// Set a specifically-typed value into the variant
		template<typename ElementType> Void Set(ElementType&& value);
		template<typename ElementType> Void Set(const ElementType& value);

		// Determine if the variant holds the specific type
		template<typename ElementType> Bool IsType() const;


		// Returns the currently held type's index into the template parameter pack
		SizeType GetIndex() const;
	private:
		// Lookup the index of a type in the template parameter pack at compile time
		template<typename ElementType>
		static constexpr SizeType IndexOfType = ParameterPack::TypeIndex<ElementType, Types ...>::Value;

		SizeType	index;
		Byte		storage[ Maximum( sizeof(Types)... ) ];
	};


#pragma region Details

	namespace Private::VariantHelper
	{
		template<typename ...Types>
		struct MoveConstructorLookup
		{
			static Void Construct(Int32 index, Void* address, Void* value)
			{
				Void(*Constructors[])(Void*, Void*) = { Class::MoveConstructor<Types>... };

				Constructors[index](address, value);
			}
		};

		template<typename ...Types>
		struct CopyConstructorLookup
		{
			static Void Construct(Int32 index, Void* address, const Void* value)
			{
				Void(*Constructors[])(Void*, const Void*) = { Class::CopyConstructor<Types>... };

				Constructors[index](address, value);
			}
		};

		template<typename ...Types>
		struct DestructorLookup
		{
			static Void Destruct(Int32 index, Void* address)
			{
				Void(*Destructors[])(Void*) = { Class::Destructor<Types>... };

				Destructors[index](address);
			}
		};
	}


	template<typename ...Types>
	Variant<Types...>::Variant()
	{
		index = 0;

		Class::UniversalConstructor<typename ParameterPack::Nth<0, Types ...>::Type>(storage);
	}

	template<typename ...Types>
	template<typename ElementType, typename ...Parameters>
	Variant<Types...>::Variant(InPlaceType<ElementType>, Parameters&&... parameters)
	{
		static_assert( SameAsAny<ElementType, Types ...>::Value );


		index = IndexOfType<ElementType>;

		Class::UniversalConstructor<ElementType>( storage, Forward<Parameters>(parameters)... );
	}

	template<typename ...Types>
	Variant<Types...>::Variant(ThisType&& other)
	{
		index = other.index;

		Private::VariantHelper::MoveConstructorLookup<Types ...>::Construct( index, storage, other.storage );
	}

	template<typename ...Types>
	Variant<Types...>::Variant(const ThisType& other)
	{
		index = other.index;

		Private::VariantHelper::CopyConstructorLookup<Types ...>::Construct( index, storage, other.storage );
	}

	template<typename ...Types>
	typename Variant<Types...>::ThisType& Variant<Types...>::operator=(ThisType&& other)
	{
		Swap( &index, &other.index );

		constexpr SizeType size = sizeof(storage);
		Byte buffer[size];
		MemoryCopy( buffer,			storage,		size );
		MemoryCopy( storage,		other.storage,	size );
		MemoryCopy( other.storage,	buffer,			size );

		return *this;
	}

	template<typename ...Types>
	typename Variant<Types...>::ThisType& Variant<Types...>::operator=(const ThisType& other)
	{
		this->~Variant();
		{
			ThisType temporary = other;

			MemoryCopy( this, &temporary );

			MemoryClear( &temporary );
		}

		return *this;
	}

	template<typename ...Types>
	Variant<Types...>::~Variant()
	{
		Private::VariantHelper::DestructorLookup<Types ...>::Destruct(index, storage);
	}

	template<typename ...Types>
	template<typename ElementType>
	ElementType& Variant<Types...>::Get()
	{
		static_assert( SameAsAny<ElementType, Types ...>::Value );


		return *reinterpret_cast<ElementType*>(storage);
	}

	template<typename ...Types>
	template<typename ElementType>
	const ElementType& Variant<Types...>::Get() const
	{
		return const_cast<ThisType*>(this)->template Get<ElementType>();
	}

	template<typename ...Types>
	template<typename ElementType, typename ...Parameters>
	Void Variant<Types...>::Emplace(Parameters&&... parameters)
	{
		static_assert( SameAsAny<ElementType, Types ...>::Value );


		this->~Variant();

		index = IndexOfType<ElementType>;
		Class::UniversalConstructor<ElementType>( storage, Forward<Parameters>(parameters)... );
	}

	template<typename ...Types>
	template<typename ElementType>
	Void Variant<Types...>::Set(ElementType&& value)
	{
		Emplace<ElementType>( Move(value) );
	}

	template<typename ...Types>
	template<typename ElementType>
	Void Variant<Types...>::Set(const ElementType& value)
	{
		Emplace<ElementType>(value);
	}

	template<typename ...Types>
	template<typename ElementType>
	Bool Variant<Types...>::IsType() const
	{
		return index == IndexOfType<ElementType>;
	}

	template<typename ...Types>
	SizeType Variant<Types...>::GetIndex() const
	{
		return index;
	}

#pragma endregion
}