#pragma once

#include "Type.h"



namespace Engine
{
	enum class PixelFormat
	{
		Unknown,

		R8G8B8,
		R8G8B8A8,

		B8G8R8,
		B8G8R8A8,
	};


	constexpr SizeType GetPixelStoreSize(PixelFormat format)
	{
		switch (format)
		{
		case PixelFormat::R8G8B8:
		case PixelFormat::B8G8R8:
			return 3;
		case PixelFormat::R8G8B8A8:
		case PixelFormat::B8G8R8A8:
			return 4;
		default:
			return 0;
		}
	}
}