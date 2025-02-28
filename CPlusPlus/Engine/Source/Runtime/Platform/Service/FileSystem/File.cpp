#include "File.h"



namespace Engine
{
	Memory<Byte> File::ReadAllBytes(const U8String& path)
	{
		Memory<Byte> result( GetFileSize(path) );

		File file( path, Mode::Read );
		file.Read( result.GetBuffer(), result.GetCount() );

		return result;
	}

	Void File::WriteAllBytes(const U8String& path, const Void* buffer, SizeType byteCount)
	{
		File file( path, Mode::Write );
		file.Write(buffer, byteCount);
	}
}