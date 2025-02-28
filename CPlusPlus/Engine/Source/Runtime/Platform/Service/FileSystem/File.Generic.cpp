#include "File.h"


#if !defined(PLATFORM_WINDOWS)

#include <fstream>
#include <filesystem>



namespace Engine
{
	File::File(const U8String& path, Mode mode)
	{
		handle = new std::fstream( path.GetBuffer(), mode == Mode::Read ? std::ios::in : std::ios::out );

		this->mode = mode;
	}

	File::~File()
	{
		delete reinterpret_cast<std::fstream*>(handle);
	}

	Void File::Seek(Whence whence, Int64 offset)
	{
		int seekMethod;
		switch (whence)
		{
		case Whence::Begin:
			seekMethod = std::ios::beg;
			break;
		case Whence::Current:
			seekMethod = std::ios::cur;
			break;
		case Whence::End:
			seekMethod = std::ios::end;
			break;
		}

		if ( mode == Mode::Read )
			reinterpret_cast<std::fstream*>(handle)->seekg(offset, seekMethod);
		else
			reinterpret_cast<std::fstream*>(handle)->seekp(offset, seekMethod);
	}

	Void File::Read(Void* buffer, SizeType byteCount)
	{
		reinterpret_cast<std::fstream*>(handle)->read( (char*)buffer, byteCount );
	}

	Void File::Write(const Void* buffer, SizeType byteCount)
	{
		reinterpret_cast<std::fstream*>(handle)->write( (char*)buffer, byteCount );
	}

	Void File::Copy(const U8String& from, const U8String& to)
	{
		std::filesystem::copy_file( from.GetBuffer(), to.GetBuffer() );
	}

	Void File::Delete(const U8String& path)
	{
		std::filesystem::remove( path.GetBuffer() );
	}

	Bool File::Exist(const U8String& path)
	{
		std::filesystem::is_regular_file( path.GetBuffer() )
	}

	SizeType File::GetFileSize(const U8String& path)
	{
		return std::filesystem::file_size( path.GetBuffer() );
	}

	Void File::Move(const U8String& from, const U8String& to)
	{
		std::filesystem::rename( from.GetBuffer(), to.GetBuffer() );
	}
}

#endif