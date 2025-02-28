#include "PortableNetworkGraphics.h"

#define LODEPNG_NO_COMPILE_DISK
#include "../../../ThirdParty/LodePNG/lodepng.h"

// for free
#include <stdlib.h>



namespace Engine::Plugin
{
	using PNGState = lodepng::State;


	static PNGState GetPNGState(const Void* buffer, SizeType byteCount)
	{
		unsigned int	width;
		unsigned int	height;
		PNGState		state;
		lodepng_inspect( &width, &height, &state, reinterpret_cast<const unsigned char*>(buffer), byteCount );

		return state;
	}


	Bool PortableNetworkGraphics::IsValid(const Void* buffer, SizeType byteCount)
	{
		auto state = GetPNGState(buffer, byteCount);

		if ( state.error )
			return false;

		auto colorType = state.info_png.color.colortype;
		if (
			colorType != LCT_RGB &&
			colorType != LCT_RGBA
			)
			return false;

		return true;
	}

	Memory<Byte> PortableNetworkGraphics::Encode(const Texture& texture)
	{
		ASSERT(
			texture.format == PixelFormat::R8G8B8 ||
			texture.format == PixelFormat::R8G8B8A8,
			"Unsupported pixel format"
		);


		Texture temporary = texture;
		temporary.FlipVertical();

		unsigned char*	output;
		size_t			outputSize;
		lodepng_encode_memory( &output, &outputSize, reinterpret_cast<const unsigned char*>( temporary.storage.GetBuffer() ), temporary.width, temporary.height, temporary.format == PixelFormat::R8G8B8 ? LCT_RGB : LCT_RGBA, 8 );

		Memory<Byte> result(outputSize);
		MemoryCopy( output, result.GetBuffer(), outputSize );

		free(output);

		return result;
	}

	Texture PortableNetworkGraphics::Decode(const Void* buffer, SizeType byteCount)
	{
		ASSERT( IsValid(buffer, byteCount), "This is not a valid portable network graphics file representation" );


		LodePNGColorType colorType = GetPNGState(buffer, byteCount).info_png.color.colortype;

		unsigned char*	output;
		unsigned int	width;
		unsigned int	height;
		lodepng_decode_memory( &output, &width, &height, reinterpret_cast<const unsigned char*>(buffer), byteCount, colorType, 8 );

		Texture result( width, height, colorType == LCT_RGB ? PixelFormat::R8G8B8 : PixelFormat::R8G8B8A8 );
		MemoryCopy( output, result.storage.GetBuffer(), result.storage.GetCount() );

		free(output);

		result.FlipVertical();

		return result;
	}
}