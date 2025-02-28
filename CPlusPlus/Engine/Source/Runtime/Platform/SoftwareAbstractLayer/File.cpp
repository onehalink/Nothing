#include "File.h"

#if defined(PLATFORM_WINDOWS)
#include "../Windows/Windows.h"
#endif



namespace Engine
{
	File::File(const U8String& path, Mode mode)
	{
	#if defined(PLATFORM_WINDOWS)
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
	#else
	#error No implementation
	#endif
	}

	File::~File()
	{
	#if defined(PLATFORM_WINDOWS)
		CloseHandle( reinterpret_cast<HANDLE>(handle) );
	#else
	#error No implementation
	#endif
	}

	Void File::Seek(Whence whence, Int64 offset)
	{
	#if defined(PLATFORM_WINDOWS)
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
	#else
	#error No implementation
	#endif
	}

	Void File::Read(Void* buffer, SizeType byteCount)
	{
	#if defined(PLATFORM_WINDOWS)
		ReadFile( reinterpret_cast<HANDLE>(handle), buffer, byteCount, nullptr, nullptr );
	#else
	#error No implementation
	#endif
	}

	Void File::Write(const Void* buffer, SizeType byteCount)
	{
	#if defined(PLATFORM_WINDOWS)
		WriteFile( reinterpret_cast<HANDLE>(handle), buffer, byteCount, nullptr, nullptr );
	#else
	#error No implementation
	#endif
	}

	Void File::Copy(const U8String& from, const U8String& to)
	{
		Span<Byte> loaded = ReadAllBytes(from);
		WriteAllBytes( to, loaded.GetBuffer(), loaded.GetCount() );
	}

	Void File::Delete(const U8String& path)
	{
	#if defined(PLATFORM_WINDOWS)
		DeleteFileW( static_cast<U16String>(path) );
	#else
	#error No implementation
	#endif
	}

	Bool File::Exist(const U8String& path)
	{
	#if defined(PLATFORM_WINDOWS)
		{
			File file( path, Mode::Read );

			if ( GetLastError() == ERROR_FILE_NOT_FOUND )
				return false;
		}

	Bool isDirectory = GetFileAttributesW( static_cast<U16String>(path) ) & FILE_ATTRIBUTE_DIRECTORY;
	if ( !isDirectory )
		return true;

	return false;
	#else
	#error No implementation
	#endif
	}

	SizeType File::GetFileSize(const U8String& path)
	{
	#if defined(PLATFORM_WINDOWS)
		File file( path, Mode::Read );

		LARGE_INTEGER ret;
		GetFileSizeEx( reinterpret_cast<HANDLE>( file.handle ), &ret );

		return ret.QuadPart;
	#else
	#error No implementation
	#endif
	}

	Void File::Move(const U8String& from, const U8String& to)
	{
		/*
		Copy(from, to);
		Delete(from);
		*/

	#if defined(PLATFORM_WINDOWS)
		MoveFileW( static_cast<U16String>(from), static_cast<U16String>(to) );
	#else
	#error No implementation
	#endif
	}

	Span<Byte> File::ReadAllBytes(const U8String& path)
	{
		Span<Byte> ret( GetFileSize(path) );

		File file( path, Mode::Read );
		file.Read( ret.GetBuffer(), ret.GetCount() );

		return ret;
	}

	Void File::WriteAllBytes(const U8String& path, const Void* buffer, SizeType byteCount)
	{
		File file( path, Mode::Write );
		file.Write(buffer, byteCount);
	}
}