#include "File.h"

#if defined(PLATFORM_WINDOWS)
#include "../../Windows/Windows.h"
#endif



namespace Engine
{
	File::File(U8StringView path, Mode mode)
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

		DWORD share = mode != Mode::Read ? 0 : FILE_SHARE_READ;

		handle = CreateFileW( U16String(path).GetBuffer(), access, share, nullptr, creation, FILE_ATTRIBUTE_NORMAL, nullptr );
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

	Void File::Read(Span<Byte> buffer)
	{
	#if defined(PLATFORM_WINDOWS)
		ReadFile( reinterpret_cast<HANDLE>(handle), buffer.GetBuffer(), buffer.GetCount(), nullptr, nullptr );
	#else
	#error No implementation
	#endif
	}

	Void File::Write(ReadOnlySpan<Byte> bytes)
	{
	#if defined(PLATFORM_WINDOWS)
		WriteFile( reinterpret_cast<HANDLE>(handle), bytes.GetBuffer(), bytes.GetCount(), nullptr, nullptr );
	#else
	#error No implementation
	#endif;
	}

	Void File::Copy(U8StringView from, U8StringView to)
	{
	#if defined(PLATFORM_WINDOWS)
		CopyFileW( U16String(from).GetBuffer(), U16String(to).GetBuffer(), true );
	#else
	#error No implementation
	#endif
	}

	Void File::Delete(U8StringView path)
	{
	#if defined(PLATFORM_WINDOWS)
		DeleteFileW( U16String(path).GetBuffer() );
	#else
	#error No implementation
	#endif
	}

	Bool File::Exist(U8StringView path)
	{
	#if defined(PLATFORM_WINDOWS)
		DWORD fileAttributes = GetFileAttributesW( U16String(path).GetBuffer() );
		
		if ( fileAttributes == INVALID_FILE_ATTRIBUTES )
			return false;

		return !( fileAttributes & FILE_ATTRIBUTE_DIRECTORY );
	#else
	#error No implementation
	#endif
	}

	SizeType File::GetFileSize(U8StringView path)
	{
	#if defined(PLATFORM_WINDOWS)
		File file( path, Mode::Read );

		LARGE_INTEGER result;
		GetFileSizeEx( reinterpret_cast<HANDLE>( file.handle ), &result );

		return result.QuadPart;
	#else
	#error No implementation
	#endif
	}

	Void File::Move(U8StringView from, U8StringView to)
	{
	#if defined(PLATFORM_WINDOWS)
		MoveFileW( U16String(from).GetBuffer(), U16String(to).GetBuffer() );
	#else
	#error No implementation
	#endif
	}

	Void File::WriteAllBytes(U8StringView path, ReadOnlySpan<Byte> bytes)
	{
		if ( Exist(path) )
			Delete(path);

		File file( path, Mode::Write );
		file.Write(bytes);
	}

	Memory<Byte> File::ReadAllBytes(U8StringView path)
	{
		Memory<Byte> result( GetFileSize(path) );

		File file( path, Mode::Read );
		file.Read( { result.GetBuffer(), result.GetCount() } );

		return result;
	}
}