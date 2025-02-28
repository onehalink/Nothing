#include "Path.h"

#if defined(PLATFORM_WINDOWS)
#include "../Windows/Windows.h"
#endif



namespace Engine
{
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

	U8String Path::GetFullQualifiedPathName(const U8String& path)
	{
	#if defined(PLATFORM_WINDOWS)
		Span<Char16> span(512);
		SizeType length = GetFullPathNameW( static_cast<U16String>(path), span.GetCount(), span.GetBuffer(), nullptr );

		Span<Char16> ret( length + 1 );
		SetNullTerminatorForRawString(ret);

		Memory::Copy( span.GetBuffer(), ret.GetBuffer(), sizeof(Char16) * length );

		return static_cast<U8String>( U16String(ret) );
	#else
	#error No implementation
	#endif
	}

	Bool Path::HasFileExtension(const U8String& path)
	{
		return
			( FindLast(path, '.') != -1 ) &&
			!EndWith(path, '.');
	}
}