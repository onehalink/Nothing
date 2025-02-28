#pragma once

#include "../Core.h"



namespace Engine
{
	struct ENGINE_API Texture
	{
		Memory<Byte> storage;

		SizeType	width;
		SizeType	height;
		PixelFormat	format;
		SizeType	texelSize;


		Texture();
		Texture(SizeType width, SizeType height, PixelFormat format = PixelFormat::R8G8B8);
		Texture(const Texture& other);
		Texture(Texture&& other);
		~Texture();


		Void SetPixel(SizeType x, SizeType y, UInt32 pixel);
		UInt32 GetPixel(SizeType x, SizeType y) const;

		Void FlipHorizontal();
		Void FlipVertical();

		Texture ConvertPixelFormat(PixelFormat specific) const;


		Texture& operator=(const Texture& other);
		Texture& operator=(Texture&& other);
	private:
		Void CopyFrom(const Texture& other);
		Void SwapWith(Texture& other);
	};
}