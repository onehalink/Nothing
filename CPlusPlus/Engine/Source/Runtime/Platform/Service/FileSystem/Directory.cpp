#include "Directory.h"

#if defined(PLATFORM_WINDOWS)
#include "../../Windows/Windows.h"
#endif



namespace Engine
{
	Void Directory::Copy(U8StringView from, U8StringView to)
	{
		if ( !Exist(to) )
			Create(to);

		EnumerateEntries(from,
			[=](U8StringView entry)
			{
				U8String combinedFrom	= Path::Combine(from, entry);
				U8String combinedTo		= Path::Combine(to, entry);

				if ( File::Exist(combinedFrom) )
					File::Copy(combinedFrom, combinedTo);

				if ( Exist(combinedFrom) )
					Copy(combinedFrom, combinedTo);
			}
		);
	}

	Void Directory::Create(U8StringView path)
	{
	#if defined(PLATFORM_WINDOWS)
		U8String entryWalker			= Path::GetFullQualifiedPathName(path);
		U8StringView entryWalkerView	= entryWalkerView;

		Stack<U8StringView> folders;
		while ( !Exist(entryWalkerView) )
		{
			folders.Push( Path::GetFileName(entryWalkerView) );

			entryWalkerView = Path::GetDirectoryName(entryWalkerView);
		}

		U8String current = entryWalkerView;
		for (auto folder : folders)
		{
			current = Path::Combine(current, folder);

			CreateDirectoryW( U16String(current).GetBuffer(), nullptr );
		}
	#else
	#error No implementation
	#endif
	}

	Void Directory::Delete(U8StringView path)
	{
	#if defined(PLATFORM_WINDOWS)
		EnumerateEntries(path,
			[=](U8StringView entry)
			{
				U8String combined = Path::Combine(path, entry);

				if ( File::Exist(combined) )
					File::Delete(combined);

				if ( Exist(combined) )
					Delete(combined);
			}
		);

		RemoveDirectoryW( U16String(path).GetBuffer() );
	#else
	#error No implementation
	#endif
	}

	Bool Directory::Exist(U8StringView path)
	{
	#if defined(PLATFORM_WINDOWS)
		DWORD fileAttributes = GetFileAttributesW( U16String(path).GetBuffer() );
		
		if ( fileAttributes == INVALID_FILE_ATTRIBUTES )
			return false;

		return fileAttributes & FILE_ATTRIBUTE_DIRECTORY;
	#else
	#error No implementation
	#endif
	}

	Void Directory::Move(U8StringView from, U8StringView to)
	{
		if ( !Exist(to) )
			Create(to);

		EnumerateEntries(from,
			[=](U8StringView entry)
			{
				U8String combinedFrom	= Path::Combine(from, entry);
				U8String combinedTo		= Path::Combine(to, entry);

				if ( File::Exist(combinedFrom) )
					File::Move(combinedFrom, combinedTo);

				if ( Exist(combinedFrom) )
					Move(combinedFrom, combinedTo);
			}
		);

		Delete(from);
	}

	Void Directory::EnumerateEntries(U8StringView path, Action<U8StringView> Visitor, SearchOption searchOption)
	{
	#if defined(PLATFORM_WINDOWS)
		U16String u16Filter = Path::Combine(path, "*.*");

		WIN32_FIND_DATAW findData;
		HANDLE findHandle = FindFirstFileW( u16Filter.GetBuffer(), &findData );

		if ( findHandle == INVALID_HANDLE_VALUE )
			return;

		do
		{
			DWORD fileAttributes	= findData.dwFileAttributes;
			Char16* fileName		= findData.cFileName;

			// ignore default entries("." and "..")
			if (
				MemoryEqual( fileName, L".",	1 + 1 ) ||
				MemoryEqual( fileName, L"..",	2 + 1 )
				)
				continue;

			Bool selectFile			= Enum::HasAll( searchOption, SearchOption::File		);
			Bool selectDirectory	= Enum::HasAll( searchOption, SearchOption::Directory	);

			Bool isDirectory	= fileAttributes & FILE_ATTRIBUTE_DIRECTORY;
			Bool isFile			= !isDirectory;

			if (
				( selectFile		&& isFile		) ||
				( selectDirectory	&& isDirectory	)
				)
			{
				U8String entry = U16StringView( reinterpret_cast<const Char16*>(fileName) );

				Visitor(entry);
			}

		}
		while ( FindNextFileW( findHandle, &findData ) );

		FindClose(findHandle);
	#else
	#error No implementation
	#endif
	}
}