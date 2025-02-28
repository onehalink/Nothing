#pragma once

#include "Engine.h"



namespace Engine::Plugin
{
	struct ENGINE_PLUGIN_API Image
	{
		enum class Format
		{
			Unknown,

			Bmp,
			Jpg,
			Png,
			Webp,
		};


		static U8String GetFileExtension(Format format);
		static Format GetFormat(const U8String& fileExtension);

		/**
		* @remark
		* Uses file extension to deduce which image format it is
		*/
		static Texture LoadFromFile(const U8String& path);
		static Texture LoadFromFile(const U8String& path, Format format);
		static Texture LoadFromMemory(const Void* buffer, SizeType byteCount, Format format);
		/**
		* @param imageQualityFactor: 1-100, higher is better. typical values are around 50-95.
		* 
		* @remark
		* Currently only Jpg and Webp image format is supported to set the parameter "imageQualityFactor"
		*/
		static Span<Byte> SaveToMemory(const Texture& texture, Format format, SizeType imageQualityFactor = 100);
		static Void SaveToFile(const U8String& path, const Texture& texture, Format format, SizeType imageQualityFactor = 100);
	};
}
