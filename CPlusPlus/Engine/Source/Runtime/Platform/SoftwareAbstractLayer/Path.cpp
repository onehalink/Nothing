#include "Path.h"

#if defined(PLATFORM_WINDOWS)
#include "../Windows/Windows.h"
#endif



#if defined(GetFullPathName)
#undef GetFullPathName
#endif


namespace Engine
{
	#if defined(PLATFORM_WINDOWS)
	const Array<Char32> InvalidFileNameCharacters	= { InPlace(), 0x22, 0x3C, 0x3E, 0x7C, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x3A, 0x2A, 0x3F, 0x5C, 0x2F, };
	const Array<Char32> InvalidPathCharacters		= { InPlace(), 0x7C, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, };
	#else
	const Array<Char32> InvalidFileNameCharacters;
	const Array<Char32> InvalidPathCharacters;
	#endif


	U8String Path::ChangeFileExtension(const U8String& path, const U8String& newFileExtension)
	{
		return Substring( path, 0, FindLast(path, '.') ) + newFileExtension;
	}

	U8String Path::Combine(const U8String& first, const U8String& second)
	{
		if (
			(  ( EndWith(first, '/') || EndWith(first, '\\') ) && !( StartWith(second, '/') || StartWith(second, '\\') ) ) ||
			( !( EndWith(first, '/') || EndWith(first, '\\') ) &&  ( StartWith(second, '/') || StartWith(second, '\\') ) )
			)
			return first + second;

		if (
			( EndWith(first, '/') || EndWith(first, '\\') ) && ( StartWith(second, '/') || StartWith(second, '\\') )
			)
			return first + Substring(second, 1);

		return first + '/' + second;
	}

	U8String Path::GetDirectoryName(const U8String& path)
	{
		return Substring( path, 0, FindLastOfAny( path, U8String("/\\") ) );
	}

	U8String Path::GetFileExtension(const U8String& path)
	{
		return Substring( path, FindLast(path, '.') );
	}

	U8String Path::GetFileName(const U8String& path)
	{
		return Substring( path, FindLastOfAny(path, U8String("/\\")) + 1 );
	}

	U8String Path::GetFileNameWithoutExtension(const U8String& path)
	{
		SizeType startIndex	= FindLastOfAny( path, U8String("/\\") ) + 1;
		SizeType count		= FindLast(path, '.') - startIndex;

		return Substring(path, startIndex, count);
	}

	U8String Path::GetFullPathName(const U8String& relativePath)
	{
	#if defined(PLATFORM_WINDOWS)
		Span<Char16> span(512);
		SizeType length = GetFullPathNameW( static_cast<U16String>(relativePath), span.GetCount(), span.GetBuffer(), nullptr );

		Span<Char16> ret( length + 1 );
		SetNullTerminatorForRawString(ret);

		Memory::Copy( span.GetBuffer(), ret.GetBuffer(), sizeof(Char16) * length );

		return static_cast<U8String>( U16String(ret) );
	#else
	#error No implementation
	#endif
	}

	Array<Char32> Path::GetInvalidFileNameCharacters()
	{
		return InvalidFileNameCharacters;
	}

	Array<Char32> Path::GetInvalidPathCharacters()
	{
		return InvalidPathCharacters;
	}

	Bool Path::HasFileExtension(const U8String& path)
	{
		return
			( FindLast(path, '.') != -1 ) &&
			!EndWith(path, '.');
	}
}