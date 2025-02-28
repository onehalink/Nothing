#pragma once

#include "JointPhotographicExpertsGroup.h"
#include "PortableNetworkGraphics.h"
#include "WebPictureFormat.h"



namespace Engine::Plugin
{
	enum class ImageFormat
	{
		Unknown,

		BMP,
		JPG,
		PNG,
		WEBP,
	};


	struct ENGINE_PLUGIN_API ImageExtension
	{
		static Texture ConvertTexturePixelFormat(const Texture& texture, PixelFormat targetPixelFormat);
		static U8String GetImageFileExtension(ImageFormat format);
		static ImageFormat GetImageFormatFromFileExtension(const U8String& extension);

		/**
		* @remark
		* Uses file extension to deduce which image format it is
		*/
		static Texture LoadFromFile(const U8String& path);
		static Texture LoadFromFile(const U8String& path, ImageFormat format);
		static Texture LoadFromMemory(const Void* buffer, SizeType byteCount, ImageFormat format);
		static Span<Byte> SaveToMemory(const Texture& texture, ImageFormat format);
		static Void SaveToFile(const U8String& path, const Texture& texture, ImageFormat format);
	};
}
