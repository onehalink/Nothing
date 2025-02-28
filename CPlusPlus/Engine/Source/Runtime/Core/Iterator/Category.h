#pragma once



namespace Engine::Iterator
{
	enum class Category
	{
		Forward			= 1 << 0,
		Backward		= 1 << 1,
		Bidirectional	= Forward | Backward,
		Contiguous		= Bidirectional | 1 << 2,
	};
}