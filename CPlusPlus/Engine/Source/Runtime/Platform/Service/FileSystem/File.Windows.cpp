#include "File.h"


#if defined(PLATFORM_WINDOWS)

#include "../../Windows/Windows.h"



namespace Engine
{
	File::File(const U8String& path, Mode mode)
	{
		DWORD access;
		DWORD creation;
		switch (mode)
		{
		case Mode::Read:
			access		= GENERIC_READ;
			creation	= OPEN_EXISTING;
			break;
		case Mode::Write:
			access		= GENERIC_WRITE;
			creation	= CREATE_NEW;
			break;
		}

		handle = CreateFileW( static_cast<U16String>(path), access, 0, nullptr, creation, FILE_ATTRIBUTE_NORMAL, nullptr );
	}

	File::~File()
	{
		CloseHandle( reinterpret_cast<HANDLE>(handle) );
	}

	Void File::Seek(Whence whence, Int64 offset)
	{
		DWORD method;
		switch (whence)
		{
		case Whence::Begin:
			method = FILE_BEGIN;
			break;
		case Whence::Current:
			method = FILE_CURRENT;
			break;
		case Whence::End:
			method = FILE_END;
			break;
		}

		LARGE_INTEGER distance;
		distance.QuadPart = offset;

		SetFilePointerEx( reinterpret_cast<HANDLE>(handle), distance, nullptr, method );
	}

	Void File::Read(Void* buffer, SizeType byteCount)
	{
		ReadFile( reinterpret_cast<HANDLE>(handle), buffer, byteCount, nullptr, nullptr );
	}

	Void File::Write(const Void* buffer, SizeType byteCount)
	{
		WriteFile( reinterpret_cast<HANDLE>(handle), buffer, byteCount, nullptr, nullptr );
	}

	Void File::Copy(const U8String& from, const U8String& to)
	{
		CopyFileW( static_cast<U16String>(from), static_cast<U16String>(to), true );
	}

	Void File::Delete(const U8String& path)
	{
		DeleteFileW( static_cast<U16String>(path) );
	}

	Bool File::Exist(const U8String& path)
	{
		{
			File file( path, Mode::Read );

			if ( GetLastError() == ERROR_FILE_NOT_FOUND )
				return false;
		}

		Bool isDirectory = GetFileAttributesW( static_cast<U16String>(path) ) & FILE_ATTRIBUTE_DIRECTORY;
		if ( !isDirectory )
			return true;

		return false;
	}

	SizeType File::GetFileSize(const U8String& path)
	{
		File file( path, Mode::Read );

		LARGE_INTEGER result;
		GetFileSizeEx( reinterpret_cast<HANDLE>( file.handle ), &result );

		return result.QuadPart;
	}

	Void File::Move(const U8String& from, const U8String& to)
	{
		MoveFileW( static_cast<U16String>(from), static_cast<U16String>(to) );
	}
}

#endif