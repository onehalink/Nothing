#pragma once

#include "../Core.h"



namespace Engine
{
	struct ENGINE_API Texture
	{
		enum class PixelFormat
		{
			Unknown,

			R8,
			R8G8,
			R8G8B8,
			R8G8B8A8,

			B8G8R8,
			B8G8R8A8,
		};


		Memory<Byte>	storage;
		PixelFormat		format;

		SizeType channelCount;
		SizeType texelSize;
		SizeType width;
		SizeType height;


		Texture();
		Texture(SizeType width, SizeType height, PixelFormat format = PixelFormat::R8G8B8);
		Texture(Texture&& other);
		Texture(const Texture& other);
		Texture& operator=(Texture&& other);
		Texture& operator=(const Texture& other);


		Void SetPixel(SizeType x, SizeType y, UInt32 pixel);
		UInt32 GetPixel(SizeType x, SizeType y) const;

		Void FlipHorizontal();
		Void FlipVertical();

		Texture Convert(PixelFormat specific) const;
	private:
		Void SwapWith(Texture& other);
		Void CopyFrom(const Texture& other);
	};
}

