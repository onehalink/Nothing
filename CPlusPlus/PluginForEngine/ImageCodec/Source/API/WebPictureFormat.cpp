#include "WebPictureFormat.h"

#include "../../ThirdParty/LibWebP/src/webp/decode.h"
#include "../../ThirdParty/LibWebP/src/webp/encode.h"



namespace Engine::Plugin
{
	Bool WebPictureFormat::IsValid(const Void* buffer, SizeType byteCount)
	{
		return WebPGetInfo( reinterpret_cast<const uint8_t*>(buffer), byteCount, nullptr, nullptr );
	}

	Span<Byte> WebPictureFormat::Encode(const Texture& texture)
	{
		ASSERT(
			texture.format == PixelFormat::R8G8B8 ||
			texture.format == PixelFormat::R8G8B8A8,
			"Unsupported pixel format"
		);


		Texture temporary = texture;
		temporary.FlipVertical();

		Function<size_t, const uint8_t*, int, int, int, uint8_t**> Op = nullptr;
		switch (texture.format)
		{
		case PixelFormat::R8G8B8:
			Op = WebPEncodeLosslessRGB;
			break;
		case PixelFormat::R8G8B8A8:
			Op = WebPEncodeLosslessRGB;
			break;
		}
		
		size_t		outputSize;
		uint8_t*	outputImage;

		outputSize = Op( reinterpret_cast<const uint8_t*>(temporary.storage.GetBuffer()), temporary.width, temporary.height, temporary.width * temporary.texelSize, &outputImage );

		Span<Byte> ret(outputSize);
		Memory::Copy( outputImage, ret.GetBuffer(), outputSize );

		WebPFree(outputImage);

		return ret;
	}

	Texture WebPictureFormat::Decode(const Void* buffer, SizeType byteCount)
	{
		WebPBitstreamFeatures features;
		WebPGetFeatures( reinterpret_cast<const uint8_t*>(buffer), byteCount, &features );

		PixelFormat format = !features.has_alpha ? PixelFormat::R8G8B8 : PixelFormat::R8G8B8A8;

		Function<uint8_t*, const uint8_t*, size_t, int*, int*> Op = nullptr;
		switch (format)
		{
		case PixelFormat::R8G8B8:
			Op = WebPDecodeRGB;
			break;
		case PixelFormat::R8G8B8A8:
			Op = WebPDecodeRGBA;
			break;
		}

		uint8_t*	outputImage;
		int			width;
		int			height;

		outputImage = Op( reinterpret_cast<const uint8_t*>(buffer), byteCount, &width, &height );

		Texture ret(width, height, format);
		Memory::Copy( outputImage, ret.storage.GetBuffer(), ret.storage.GetCount() );

		ret.FlipVertical();

		return ret;
	}
}