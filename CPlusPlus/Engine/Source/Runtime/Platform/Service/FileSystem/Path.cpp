#include "Path.h"

#if defined(PLATFORM_WINDOWS)
#include "../../Windows/Windows.h"
#endif



namespace Engine
{
	U8String Path::ChangeFileExtension(U8StringView path, U8StringView newFileExtension)
	{
		SizeType count = FindLastChar(path, '.');

		return static_cast<U8StringView>( path.Slice(0, count) ) + newFileExtension;
	}

	U8StringView Path::GetDirectoryName(U8StringView path)
	{
		SizeType count = FindLastOfAnyChar( path, ReadOnlySpan<Char8>("/\\", 2) );

		return path.Slice(0, count);
	}

	U8StringView Path::GetFileExtension(U8StringView path)
	{
		return path.Slice( FindLastChar(path, '.') );
	}

	U8StringView Path::GetFileName(U8StringView path)
	{
		SizeType startIndex = FindLastOfAnyChar( path, ReadOnlySpan<Char8>("/\\", 2) );

		return path.Slice( startIndex + 1 );
	}

	U8StringView Path::GetFileNameWithoutExtension(U8StringView path)
	{
		SizeType startIndex	= FindLastOfAnyChar( path, ReadOnlySpan<Char8>("/\\", 2) ) + 1;
		SizeType count		= FindLastChar(path, '.') - startIndex;

		return path.Slice(startIndex, count);
	}

	U8String Path::GetFullQualifiedPathName(U8StringView path)
	{
	#if defined(PLATFORM_WINDOWS)
		Char16 buffer[256];
		SizeType length = GetFullPathNameW( U16String(path).GetBuffer(), CountArray(buffer), buffer, nullptr );

		U16String result(length);
		MemoryCopy( buffer, result.GetBuffer(), length );

		return result;
	#else
	#error No implementation
	#endif
	}

	Bool Path::HasFileExtension(U8StringView path)
	{
		return
			FindLastChar(path, '.') != -1 &&
			!EndWith(path, '.');
	}
}