#pragma once

#include "InPlace.h"
#include "Forward.h"
#include "Variant.h"

#include "String/String.h"
#include "String/StringView.h"



namespace Engine
{
	// Helper that either contains a valid result or an error
	template<typename T>
	class Result
	{
	public:
		Result();
		template<SizeType Index, typename ...Parameters>
		Result(InPlaceIndex<Index>, Parameters&&... parameters);


		Void SetValue(T&& value);
		Void SetValue(const T& value);
		const T& GetValue() const;

		Void SetError(U8StringView errorText);
		U8StringView GetError() const;


		Bool IsValid() const;


		operator Bool() const;
	private:
		struct String
		{
			U8String errorText;


			template<typename ...Parameters>
			String(Parameters&&... parameters)
				: errorText( Forward<Parameters>(parameters)... )
			{

			}
		};


		Variant<String, T> value;
	};


#pragma region

	template<typename T>
	Result<T>::Result()
	{

	}

	template<typename T>
	template<SizeType Index, typename ...Parameters>
	Result<T>::Result(InPlaceIndex<Index>, Parameters&&... parameters)
	{
		value = { InPlaceType<typename ParameterPack::Nth<Index, String, T>::Type>(), Forward<Parameters>(parameters)... };
	}

	template<typename T>
	Void Result<T>::SetValue(T&& value)
	{
		this->value.Set<T>( Move(value) );
	}

	template<typename T>
	Void Result<T>::SetValue(const T& value)
	{
		this->value.Set<T>(value);
	}

	template<typename T>
	const T& Result<T>::GetValue() const
	{
		return value.Get<T>();
	}

	template<typename T>
	Void Result<T>::SetError(U8StringView errorText)
	{
		value.Emplace<String>(errorText);
	}

	template<typename T>
	U8StringView Result<T>::GetError() const
	{
		return value.Get<String>().errorText;
	}

	template<typename T>
	Bool Result<T>::IsValid() const
	{
		return value.IsType<T>();
	}

	template<typename T>
	Result<T>::operator Bool() const
	{
		return IsValid();
	}

#pragma
}