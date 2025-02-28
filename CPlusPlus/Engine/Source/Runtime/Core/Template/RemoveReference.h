#pragma once



namespace Engine
{
	// Remove lvalue/rvalue reference
	template<typename T>
	struct RemoveReference
	{
		using Type = T;
	};


	template<typename T>
	struct RemoveReference<T&>
	{
		using Type = T;
	};


	template<typename T>
	struct RemoveReference<T&&>
	{
		using Type = T;
	};
}