#pragma once



namespace Engine
{
	enum class Error
	{
		Unspecific,

		// Parameter
		InvalidParameter,
		NullPointer = InvalidParameter,
		IndexOfRange = InvalidParameter,
		DivisorIsZero = InvalidParameter,

		// Container
		Empty,

		// File system
		FileExisted,
		FileNotFound,
		DirectoryExisted,
		DirectoryNotFound,
	};
}