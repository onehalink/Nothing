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

	Span<Byte> PortableNetworkGraphics::Encode(const Texture& texture)
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

		Span<Byte> ret(outputSize);
		Memory::Copy( output, ret.GetBuffer(), outputSize );

		free(output);

		return ret;
	}

	Texture PortableNetworkGraphics::Decode(const Void* buffer, SizeType byteCount)
	{
		ASSERT( IsValid(buffer, byteCount), "This is not a valid portable network graphics file representation" );


		LodePNGColorType colorType = GetPNGState(buffer, byteCount).info_png.color.colortype;

		unsigned char*	output;
		unsigned int	width;
		unsigned int	height;
		lodepng_decode_memory( &output, &width, &height, reinterpret_cast<const unsigned char*>(buffer), byteCount, colorType, 8 );

		Texture ret( width, height, colorType == LCT_RGB ? PixelFormat::R8G8B8 : PixelFormat::R8G8B8A8 );
		Memory::Copy( output, ret.storage.GetBuffer(), ret.storage.GetCount() );

		free(output);

		ret.FlipVertical();

		return ret;
	}
}