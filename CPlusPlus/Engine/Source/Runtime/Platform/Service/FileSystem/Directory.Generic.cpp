#include "Directory.h"


#if !defined(PLATFORM_WINDOWS)

#include <filesystem>



namespace Engine
{
	Void Directory::Create(const U8String& path)
	{
		std::filesystem::create_directories( path.GetBuffer() );
	}

	Void Directory::Delete(const U8String& path)
	{
		std::filesystem::remove_all( path.GetBuffer() );
	}

	Bool Directory::Exist(const U8String& path)
	{
		return std::filesystem::is_directory( path.GetBuffer() );
	}

	DynamicArray<U8String> Directory::EnumerateEntries(const U8String& path, SearchOption searchOption)
	{
		DynamicArray<U8String> result;

		for (auto& entry : std::filesystem::recursive_directory_iterator( path.GetBuffer() ))
		{
			Bool selectFile			= ( searchOption & SearchOption::File		) == SearchOption::File;
			Bool selectDirectory	= ( searchOption & SearchOption::Directory	) == SearchOption::Directory;

			if (
				( selectFile		&& entry.is_regular_file()	) ||
				( selectDirectory	&& entry.is_directory()		)
				)
				result.Add( entry.path().c_str() );
		}

		return result;
	}
}

#endif