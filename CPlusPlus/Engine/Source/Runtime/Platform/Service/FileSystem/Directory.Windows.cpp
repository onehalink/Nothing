#include "Directory.h"


#if defined(PLATFORM_WINDOWS)

#include "../../Windows/Windows.h"



namespace Engine
{
	Void Directory::Create(const U8String& path)
	{
		U8String entryWalker = Path::GetFullQualifiedPathName(path);

		Stack<U8String> stack;
		while ( !Exist(entryWalker) )
		{
			Int32 startIndex	= FindLast(entryWalker, '\\') + 1;
			U8String folder		= Substring(entryWalker, startIndex);

			stack.Push(folder);

			entryWalker = Substring( entryWalker, 0, startIndex - 1 );
		}

		for (auto& folder : stack)
		{
			entryWalker = Path::Combine(entryWalker, folder);

			CreateDirectoryW( static_cast<U16String>(entryWalker), nullptr );
		}
	}

	Void Directory::Delete(const U8String& path)
	{
		for ( auto& entry : EnumerateEntries(path) )
		{
			U8String combined = Path::Combine(path, entry);

			if ( File::Exist(combined) )
				File::Delete(combined);

			if ( Exist(combined) )
				Delete(combined);
		}

		RemoveDirectoryW( static_cast<U16String>(path) );
	}

	Bool Directory::Exist(const U8String& path)
	{
		{
			File file( path, File::Mode::Read );

			if ( GetLastError() == ERROR_FILE_NOT_FOUND )
				return false;

			if ( GetLastError() == ERROR_PATH_NOT_FOUND )
				return false;
		}

		Bool isDirectory = GetFileAttributesW( static_cast<U16String>(path) ) & FILE_ATTRIBUTE_DIRECTORY;
		if (isDirectory)
			return true;

		return false;
	}

	DynamicArray<U8String> Directory::EnumerateEntries(const U8String& path, SearchOption searchOption)
	{
		WIN32_FIND_DATAW findData;
		HANDLE findHandle = FindFirstFileW( static_cast<U16String>( Path::Combine( path, "*.*" ) ), &findData );

		if ( findHandle == INVALID_HANDLE_VALUE )
			return DynamicArray<U8String>();

		DynamicArray<U8String> result;
		do
		{
			DWORD attributes	= findData.dwFileAttributes;
			Char16* name		= findData.cFileName;

			// ignore default entries("." and "..")
			if (
				MemoryEqual( name, L".",	sizeof(Char16) * ( 1 + 1 ) ) ||
				MemoryEqual( name, L"..",	sizeof(Char16) * ( 2 + 1 ) )
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
				result.Add( static_cast<U8String>( U16String(name) ) );
		}
		while ( FindNextFileW( findHandle, &findData ) );

		FindClose(findHandle);

		return result;
	}
}

#endif