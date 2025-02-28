#include "Directory.h"

#if defined(PLATFORM_WINDOWS)
#include "../Windows/Windows.h"
#endif



namespace Engine
{
	Void Directory::Copy(const U8String& from, const U8String& to)
	{
		if ( !Exist(to) )
			Create(to);

		for ( auto& entry : EnumEntries(from) )
		{
			U8String combinedFrom	= Path::Combine(from, entry);
			U8String combinedTo		= Path::Combine(to, entry);

			if ( File::Exist(combinedFrom) )
				File::Copy(combinedFrom, combinedTo);

			if ( Exist(combinedFrom) )
				Copy(combinedFrom, combinedTo);
		}
	}

	Void Directory::Create(const U8String& path)
	{
	#if defined(PLATFORM_WINDOWS)
		CreateDirectoryW( static_cast<U16String>(path), nullptr );
	#else
	#error No implementation
	#endif
	}

	Void Directory::Delete(const U8String& path)
	{
		for ( auto& entry : EnumEntries(path) )
		{
			U8String combined = Path::Combine(path, entry);

			if ( File::Exist(combined) )
				File::Delete(combined);

			if ( Exist(combined) )
				Delete(combined);
		}

	#if defined(PLATFORM_WINDOWS)
		RemoveDirectoryW( static_cast<U16String>(path) );
	#else
	#error No implementation
	#endif
	}

	Bool Directory::Exist(const U8String& path)
	{
	#if defined(PLATFORM_WINDOWS)
		{
			File file( path, File::Mode::Read );

			if ( GetLastError() == ERROR_FILE_NOT_FOUND )
				return false;
		}

		Bool isDirectory = GetFileAttributesW( static_cast<U16String>(path) );
		if (isDirectory)
			return true;

		return false;
	#else
	#error No implementation
	#endif
	}

	Void Directory::Move(const U8String& from, const U8String& to)
	{
		if ( !Exist(to) )
			Create(to);

		for ( auto& entry : EnumEntries(from) )
		{
			U8String combinedFrom	= Path::Combine(from, entry);
			U8String combinedTo		= Path::Combine(to, entry);

			if ( File::Exist(combinedFrom) )
				File::Move(combinedFrom, combinedTo);

			if ( Exist(combinedFrom) )
				Move(combinedFrom, combinedTo);
		}

		Delete(from);
	}

	Array<U8String> Directory::EnumEntries(const U8String& path, SearchOption searchOption)
	{
	#if defined(PLATFORM_WINDOWS)
		WIN32_FIND_DATAW findData;
		HANDLE findHandle = FindFirstFileW( static_cast<U16String>( Path::Combine( path, "*.*" ) ), &findData );

		if ( findHandle == INVALID_HANDLE_VALUE )
			return Array<U8String>();

		Array<U8String> ret;
		do
		{
			DWORD attributes	= findData.dwFileAttributes;
			Char16* name		= findData.cFileName;

			// ignore default entries("." and "..")
			if (
				Memory::Equal( name, L".",	sizeof(Char16) * ( 1 + 1 ) ) ||
				Memory::Equal( name, L"..", sizeof(Char16) * ( 2 + 1 ) )
				)
				continue;

			Bool selectFile			= ( searchOption & SearchOption::File		) == SearchOption::File;
			Bool selectDirectory	= ( searchOption & SearchOption::Directory	) == SearchOption::Directory;

			Bool isFile			= ( attributes & FILE_ATTRIBUTE_DIRECTORY ) != FILE_ATTRIBUTE_DIRECTORY;
			Bool isDirectory	= !isFile;

			if (
				( selectFile		&& isFile		) ||
				( selectDirectory	&& isDirectory	)
				)
				ret.Add(name);
		}
		while ( FindNextFileW( findHandle, &findData ) );

		FindClose(findHandle);

		return ret;
	#else
	#error No implementation
	#endif
	}
}