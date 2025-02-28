#include "Path.h"


#if !defined(PLATFORM_WINDOWS)

#include <filesystem>



namespace Engine
{
	U8String Path::GetFullQualifiedPathName(const U8String& path)
	{
		return std::filesystem::absolute( path.GetBuffer() ).c_str();
	}
}

#endif