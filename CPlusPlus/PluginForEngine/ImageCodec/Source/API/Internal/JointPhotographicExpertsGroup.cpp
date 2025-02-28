#include "JointPhotographicExpertsGroup.h"

#include "../../../ThirdParty/JpegCompressor/jpge.h"
#include "../../../ThirdParty/JpegCompressor/jpgd.h"

// for free
#include <stdlib.h>



using namespace jpgd;


using CompressionParameters = jpge::params;

using MemoryStream	= jpeg_decoder_mem_stream;
using JpegDecoder	= jpeg_decoder;


namespace Engine::Plugin
{
	Bool JointPhotographicExpertsGroup::IsValid(const Void* buffer, SizeType byteCount)
	{
		MemoryStream data( reinterpret_cast<const uint8_t*>(buffer), byteCount );

		return JpegDecoder( &data ).get_error_code() == JPGD_SUCCESS;
	}

	Memory<Byte> JointPhotographicExpertsGroup::Encode(const Texture& texture)
	{
		ASSERT(
			texture.format == PixelFormat::R8G8B8 ||
			texture.format == PixelFormat::R8G8B8A8,
			"Unsupported pixel format"
		);


		Texture temporary = texture;
		temporary.FlipVertical();

		Memory<Byte> span( temporary.storage.GetCount() );

		int compressedImageSize = span.GetCount();

		CompressionParameters params;
		params.m_quality = 100; // lossless

		jpge::compress_image_to_jpeg_file_in_memory( span.GetBuffer(), compressedImageSize, temporary.width, temporary.height, temporary.format == PixelFormat::R8G8B8 ? 3 : 4, reinterpret_cast<const uint8_t*>( temporary.storage.GetBuffer() ), params );

		Memory<Byte> result(compressedImageSize);
		MemoryCopy( span.GetBuffer(), result.GetBuffer(), compressedImageSize );

		return result;
	}

	Texture JointPhotographicExpertsGroup::Decode(const Void* buffer, SizeType byteCount)
	{
		int requiredComponents = 0;
		{
			MemoryStream data( reinterpret_cast<const uint8_t*>(buffer), byteCount );
			requiredComponents = JpegDecoder( &data ).get_num_components();
		}

		int width;
		int height;
		int actualComponents;
		unsigned char* outputImage = decompress_jpeg_image_from_memory( reinterpret_cast<const unsigned char*>(buffer), byteCount, &width, &height, &actualComponents, requiredComponents );

		Texture result( width, height, requiredComponents == 3 ? PixelFormat::R8G8B8 : PixelFormat::R8G8B8A8 );
		MemoryCopy( outputImage, result.storage.GetBuffer(), result.storage.GetCount() );

		free(outputImage);

		result.FlipVertical();

		return result;
	}
}