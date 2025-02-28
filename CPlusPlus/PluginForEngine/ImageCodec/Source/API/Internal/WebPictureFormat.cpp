#include "WebPictureFormat.h"

#include "../../../ThirdParty/LibWebP/src/webp/decode.h"
#include "../../../ThirdParty/LibWebP/src/webp/encode.h"



namespace Engine::Plugin
{
	Bool WebPictureFormat::IsValid(const Void* buffer, SizeType byteCount)
	{
		return WebPGetInfo( reinterpret_cast<const uint8_t*>(buffer), byteCount, nullptr, nullptr );
	}

	Memory<Byte> WebPictureFormat::Encode(const Texture& texture)
	{
		ASSERT(
			texture.format == PixelFormat::R8G8B8 ||
			texture.format == PixelFormat::R8G8B8A8,
			"Unsupported pixel format"
		);


		Texture temporary = texture;
		temporary.FlipVertical();

		Function<size_t, const uint8_t*, int, int, int, float, uint8_t**> Op = nullptr;
		switch ( texture.format )
		{
		case PixelFormat::R8G8B8:
			Op = WebPEncodeRGB;
			break;
		case PixelFormat::R8G8B8A8:
			Op = WebPEncodeRGBA;
			break;
		}

		float imageQualityFactor = 100; // lossless

		uint8_t* outputImage;
		size_t outputSize = Op( reinterpret_cast<const uint8_t*>( temporary.storage.GetBuffer() ), temporary.width, temporary.height, temporary.width * temporary.texelSize, imageQualityFactor, &outputImage );

		Memory<Byte> result(outputSize);
		MemoryCopy( outputImage, result.GetBuffer(), outputSize );
		
		WebPFree(outputImage);

		return result;
	}

	Texture WebPictureFormat::Decode(const Void* buffer, SizeType byteCount)
	{
		ASSERT( IsValid(buffer, byteCount), "This is not a valid web picture format file representation" );


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

		int width;
		int height;
		uint8_t* outputImage = Op( reinterpret_cast<const uint8_t*>(buffer), byteCount, &width, &height );

		Texture result(width, height, format);
		MemoryCopy( outputImage, result.storage.GetBuffer(), result.storage.GetCount() );

		result.FlipVertical();

		return result;
	}
}