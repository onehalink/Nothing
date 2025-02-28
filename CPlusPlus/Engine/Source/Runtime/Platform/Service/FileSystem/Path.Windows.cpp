#include "Path.h"


#if defined(PLATFORM_WINDOWS)

#include "../../Windows/Windows.h"



namespace Engine
{
	U8String Path::GetFullQualifiedPathName(const U8String& path)
	{
		constexpr SizeType size = 512;
		Char16 buffer[size];

		SizeType length = GetFullPathNameW( static_cast<U16String>(path), size, buffer, nullptr );

		Memory<Char16> result( length + 1 );
		SetNullTerminator(result);

		MemoryCopy( buffer, result.GetBuffer(), sizeof(Char16) * length );

		return static_cast<U8String>( U16String( Move(result) ) );
	}
}

#endif