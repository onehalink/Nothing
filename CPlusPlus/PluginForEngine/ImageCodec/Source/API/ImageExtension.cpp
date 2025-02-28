#include "ImageExtension.h"



namespace Engine::Plugin
{
	Texture ImageExtension::ConvertTexturePixelFormat(const Texture& texture, PixelFormat targetPixelFormat)
	{
		Function<Color, UInt32> OpA = nullptr;
		switch ( texture.format )
		{
		case PixelFormat::R8G8B8:
			OpA = FromR8G8B8;
			break;
		case PixelFormat::R8G8B8A8:
			OpA = FromR8G8B8A8;
			break;
		case PixelFormat::B8G8R8:
			OpA = FromB8G8R8;
			break;
		case PixelFormat::B8G8R8A8:
			OpA = FromB8G8R8A8;
			break;
		}

		Function<UInt32, const Color&> OpB = nullptr;
		switch (targetPixelFormat)
		{
		case PixelFormat::R8G8B8:
			OpB = ToR8G8B8;
			break;
		case PixelFormat::R8G8B8A8:
			OpB = ToR8G8B8A8;
			break;
		case PixelFormat::B8G8R8:
			OpB = ToB8G8R8;
			break;
		case PixelFormat::B8G8R8A8:
			OpB = ToB8G8R8A8;
			break;
		}

		Texture ret( texture.width, texture.height, targetPixelFormat );

		for (SizeType y = 0; y < texture.height; y++)
			for (SizeType x = 0; x < texture.width; x++)
				ret.SetPixel(
					x, y,
					OpB( OpA( texture.GetPixel(x, y) ) )
				);

		return ret;
	}

	U8String ImageExtension::GetImageFileExtension(ImageFormat format)
	{
		switch (format)
		{
		case ImageFormat::BMP:
			return ".bmp";
		case ImageFormat::JPG:
			return ".jpg";
		case ImageFormat::PNG:
			return ".png";
		case ImageFormat::WEBP:
			return "*.webp";
		default:
			return "";
		}
	}

	ImageFormat ImageExtension::GetImageFormatFromFileExtension(const U8String& extension)
	{
		if ( extension == U8String(".bmp") )
			return ImageFormat::BMP;
		else if ( extension == U8String(".jpg") )
			return ImageFormat::JPG;
		else if ( extension == U8String(".png") )
			return ImageFormat::PNG;
		else if ( extension == U8String(".webp") )
			return ImageFormat::WEBP;
		else
			return ImageFormat::Unknown;
	}

	Texture ImageExtension::LoadFromFile(const U8String& path)
	{
		return LoadFromFile( path, GetImageFormatFromFileExtension( Path::GetFileExtension(path) ) );
	}

	Texture ImageExtension::LoadFromFile(const U8String& path, ImageFormat format)
	{
		Span<Byte> loaded = File::ReadAllBytes(path);

		return LoadFromMemory( loaded.GetBuffer(), loaded.GetCount(), format );
	}

	Texture ImageExtension::LoadFromMemory(const Void* buffer, SizeType byteCount, ImageFormat format)
	{
		switch (format)
		{
		case ImageFormat::BMP:
			return Bitmap::Decode(buffer, byteCount);
		case ImageFormat::JPG:
			return JointPhotographicExpertsGroup::Decode(buffer, byteCount);
		case ImageFormat::PNG:
			return PortableNetworkGraphics::Decode(buffer, byteCount);
		case ImageFormat::WEBP:
			return WebPictureFormat::Decode(buffer, byteCount);
		default:
			return Texture();
		}
	}

	Span<Byte> ImageExtension::SaveToMemory(const Texture& texture, ImageFormat format)
	{
		switch (format)
		{
		case ImageFormat::BMP:
			return Bitmap::Encode(texture);
		case ImageFormat::JPG:
			return JointPhotographicExpertsGroup::Encode(texture);
		case ImageFormat::PNG:
			return PortableNetworkGraphics::Encode(texture);
		case ImageFormat::WEBP:
			return WebPictureFormat::Encode(texture);
		default:
			return Span<Byte>();
		}
	}

	Void ImageExtension::SaveToFile(const U8String& path, const Texture& texture, ImageFormat format)
	{
		Span<Byte> image = SaveToMemory(texture, format);

		File::WriteAllBytes( path, image.GetBuffer(), image.GetCount() );
	}
}