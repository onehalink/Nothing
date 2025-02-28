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
		static Memory<Byte> SaveToMemory(const Texture& texture, Format format);
		static Void SaveToFile(const U8String& path, const Texture& texture, Format format);
	};
}
