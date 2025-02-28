#pragma once

#include "Forward.h"
#include "PlacementNew.h"
#include "Type.h"



namespace Engine::Class
{
	template<typename T, typename ...Parameters> Void UniversalConstructor(Void* address, Parameters&&... parameters);
	template<typename T> Void MoveConstructor(Void* address, Void* value);
	template<typename T> Void CopyConstructor(Void* address, const Void* value);
	template<typename T> Void Destructor(Void* address);


#pragma region Details

	template<typename T, typename ...Parameters>
	Void UniversalConstructor(Void* address, Parameters&&... parameters)
	{
		new (address) T( Forward<Parameters>(parameters)... );
	}

	template<typename T>
	Void MoveConstructor(Void* address, Void* value)
	{
		new (address) T( Move( *reinterpret_cast<T*>(value) ) );
	}

	template<typename T>
	Void CopyConstructor(Void* address, const Void* value)
	{
		new (address) T( *reinterpret_cast<const T*>(value) );
	}

	template<typename T>
	Void Destructor(Void* address)
	{
		using ElementTypeAlias = T;


		reinterpret_cast<ElementTypeAlias*>(address)->ElementTypeAlias::~ElementTypeAlias();
	}

#pragma endregion
}