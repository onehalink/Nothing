#include "Bitmap.h"



namespace Engine
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
		Byte	magic[2]; // Must be "BM"
		UInt32	size;
		UInt32	reserved; // Must be 0
		UInt32	offset;
	};
	#pragma pack(pop)


	/**
	* Reference from https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader
	*/
	struct InfoHeader
	{
		UInt32 size;
		UInt32 width;
		UInt32 height;
		UInt16 planes;
		UInt16 bitCount; // Must be 1
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


	Bool Bitmap::IsValid(const Void* buffer, SizeType byteCount)
	{
		if ( byteCount < DefaultBitsOffset )
			return false;

		if ( !MemoryEqual( buffer, "BM", 2 ) )
			return false;

		const InfoHeader* descriptor = reinterpret_cast<const InfoHeader*>( reinterpret_cast<const Byte*>(buffer) + FileHeaderSize );
		if (
			descriptor->bitCount != 24 &&
			descriptor->bitCount != 32
			)
			return false;

		return true;
	}

	Memory<Byte> Bitmap::Encode(const Texture& texture)
	{
		ASSERT(
			texture.format == PixelFormat::B8G8R8 ||
			texture.format == PixelFormat::B8G8R8A8,
			"Unsupported pixel format"
		);

		
		SizeType imageSize = texture.width * texture.height * texture.texelSize;
		SizeType totalSize = imageSize + DefaultBitsOffset;

		Memory<Byte> result(totalSize);
		{
			MemoryClear( result.GetBuffer(), DefaultBitsOffset );
			MemoryCopy( texture.storage.GetBuffer(), result.GetBuffer() + DefaultBitsOffset, imageSize );

			{
				FileHeader* descriptor	= reinterpret_cast<FileHeader*>( result.GetBuffer() );
				descriptor->magic[0]	= 'B';
				descriptor->magic[1]	= 'M';
				descriptor->size		= totalSize;
				descriptor->offset		= DefaultBitsOffset;
			}

			{
				InfoHeader* descriptor	= reinterpret_cast<InfoHeader*>( result.GetBuffer() + FileHeaderSize );
				descriptor->size		= InfoHeaderSize;
				descriptor->width		= texture.width;
				descriptor->height		= texture.height;
				descriptor->bitCount	= texture.texelSize * 8;
				descriptor->planes		= 1;
				descriptor->imageSize	= imageSize;
			}
		}

		return result;
	}

	Texture Bitmap::Decode(const Void* buffer, SizeType byteCount)
	{
		ASSERT( IsValid(buffer, byteCount), "This is not a valid bitmap file representation" );


		const InfoHeader* descriptor = reinterpret_cast<const InfoHeader*>( reinterpret_cast<const Byte*>(buffer) + FileHeaderSize );

		Texture result( descriptor->width, descriptor->height, descriptor->bitCount == 24 ? PixelFormat::B8G8R8 : PixelFormat::B8G8R8A8 );
		MemoryCopy( reinterpret_cast<const Byte*>(buffer) + reinterpret_cast<const FileHeader*>(buffer)->offset, result.storage.GetBuffer(), descriptor->imageSize );

		return result;
	}
}
