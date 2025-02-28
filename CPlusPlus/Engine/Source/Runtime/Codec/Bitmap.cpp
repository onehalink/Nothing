#include "Bitmap.h"



namespace Engine::Bitmap
{
	/**
	* Reference from https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
	*
	* @remark
	* The size in bytes of struct must be 14
	*/
	#pragma pack(push, 2)
	struct FileHeader
	{
		Byte	magic[2]; // must be "BM"
		UInt32	size;
		UInt32	reserved; // must be 0
		UInt32	offset;
	};
	#pragma pack(pop)


	// Reference from https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader
	struct InfoHeader
	{
		UInt32 size;
		UInt32 width;
		UInt32 height;
		UInt16 planes; // must be 1
		UInt16 bitCount;
		UInt32 compression;
		UInt32 imageSize;
		UInt32 xPixelsPerMeter;
		UInt32 yPixelsPerMeter;
		UInt32 colorUsed;
		UInt32 colorImportant;
	};


	constexpr SizeType FileHeaderSize		= sizeof(FileHeader);
	constexpr SizeType InfoHeaderSize		= sizeof(InfoHeader);
	constexpr SizeType DefaultBitsOffset	= FileHeaderSize + InfoHeaderSize;


	Bool IsValid(ReadOnlySpan<Byte> bytes)
	{
		if ( bytes.GetCount() < DefaultBitsOffset )
			return false;

		if ( !MemoryEqual( bytes.GetBuffer(), "BM", 2 ) )
			return false;

		auto descriptor = reinterpret_cast<const InfoHeader*>( bytes.GetBuffer() + FileHeaderSize );
		if (
			descriptor->bitCount != 24 &&
			descriptor->bitCount != 32
			)
			return false;

		return true;
	}

	Memory<Byte> Encode(const Texture& texture)
	{
		ASSERT(
			texture.format == Texture::PixelFormat::B8G8R8 ||
			texture.format == Texture::PixelFormat::B8G8R8A8,
			"unsupported pixel format"
		);

		SizeType imageSize = texture.width * texture.height * texture.texelSize;
		SizeType totalSize = imageSize + DefaultBitsOffset;

		Memory<Byte> result(totalSize);
		{
			MemoryClear( result.GetBuffer(), DefaultBitsOffset );
			MemoryCopy( result.GetBuffer() + DefaultBitsOffset, texture.storage.GetBuffer(), imageSize );

			{
				auto descriptor			= reinterpret_cast<FileHeader*>( result.GetBuffer() );
				descriptor->magic[0]	= 'B';
				descriptor->magic[1]	= 'M';
				descriptor->size		= totalSize;
				descriptor->offset		= DefaultBitsOffset;
			}

			{
				auto descriptor			= reinterpret_cast<InfoHeader*>( result.GetBuffer() + FileHeaderSize );
				descriptor->size		= InfoHeaderSize;
				descriptor->width		= texture.width;
				descriptor->height		= texture.height;
				descriptor->planes		= 1;
				descriptor->bitCount	= texture.texelSize * 8;
				descriptor->imageSize	= imageSize;
			}
		}

		return result;
	}

	Texture Decode(ReadOnlySpan<Byte> bytes)
	{
		auto descriptor = reinterpret_cast<const InfoHeader*>( bytes.GetBuffer() + FileHeaderSize );

		Texture result( descriptor->width, descriptor->height, descriptor->bitCount == 24 ? Texture::PixelFormat::B8G8R8 : Texture::PixelFormat::B8G8R8A8 );
		MemoryCopy( result.storage.GetBuffer(), bytes.GetBuffer() + reinterpret_cast<const FileHeader*>( bytes.GetBuffer() )->offset, result.storage.GetCount() );

		return result;
	}
}
