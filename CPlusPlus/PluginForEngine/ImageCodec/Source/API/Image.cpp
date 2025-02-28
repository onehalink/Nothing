#include "Image.h"

#include "Internal/JointPhotographicExpertsGroup.h"
#include "Internal/PortableNetworkGraphics.h"
#include "Internal/WebPictureFormat.h"



namespace Engine::Plugin
{
	U8String Image::GetFileExtension(Format format)
	{
		switch (format)
		{
		case Format::Bmp:
			return ".bmp";
		case Format::Jpg:
			return ".jpg";
		case Format::Png:
			return ".png";
		case Format::Webp:
			return ".webp";
		default:
			return "";
		}
	}

	Image::Format Image::GetFormat(const U8String& extension)
	{
		if ( extension == ".bmp" )
			return Format::Bmp;
		else if ( extension == ".jpg" )
			return Format::Jpg;
		else if ( extension == ".png" )
			return Format::Png;
		else if ( extension == ".webp" )
			return Format::Webp;
		else
			return Format::Unknown;
	}

	Texture Image::LoadFromFile(const U8String& path)
	{
		return LoadFromFile( path, GetFormat( Path::GetFileExtension(path) ) );
	}

	Texture Image::LoadFromFile(const U8String& path, Format format)
	{
		Memory<Byte> loaded = File::ReadAllBytes(path);

		return LoadFromMemory( loaded.GetBuffer(), loaded.GetCount(), format );
	}

	Texture Image::LoadFromMemory(const Void* buffer, SizeType byteCount, Format format)
	{
		switch (format)
		{
		case Format::Bmp:
			return Bitmap::Decode(buffer, byteCount);
		case Format::Jpg:
			return JointPhotographicExpertsGroup::Decode(buffer, byteCount);
		case Format::Png:
			return PortableNetworkGraphics::Decode(buffer, byteCount);
		case Format::Webp:
			return WebPictureFormat::Decode(buffer, byteCount);
		default:
			return Texture();
		}
	}

	Memory<Byte> Image::SaveToMemory(const Texture& texture, Format format)
	{
		switch (format)
		{
		case Format::Bmp:
			return Bitmap::Encode(texture);
		case Format::Jpg:
			return JointPhotographicExpertsGroup::Encode(texture);
		case Format::Png:
			return PortableNetworkGraphics::Encode(texture);
		case Format::Webp:
			return WebPictureFormat::Encode(texture);
		default:
			return Memory<Byte>();
		}
	}

	Void Image::SaveToFile(const U8String& path, const Texture& texture, Format format)
	{
		Memory<Byte> image = SaveToMemory(texture, format);

		File::WriteAllBytes( path, image.GetBuffer(), image.GetCount() );
	}
}