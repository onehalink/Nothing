#pragma once

#include "../../Core.h"



namespace Engine
{
	class ENGINE_API File : INonCopyable
	{
	public:
		enum class Mode
		{
			Read,
			Write,
		};


		enum class Whence
		{
			Begin,
			Current,
			End,
		};


		File(const U8String& path, Mode mode);
		~File();


		Void Seek(Whence whence, Int64 offset);

		Void Read(Void* buffer, SizeType byteCount);
		Void Write(const Void* buffer, SizeType byteCount);


		static Void Copy(const U8String& from, const U8String& to);
		static Void Delete(const U8String& path);
		static Bool Exist(const U8String& path);
		static SizeType GetFileSize(const U8String& path);
		static Void Move(const U8String& from, const U8String& to);

		static Span<Byte> ReadAllBytes(const U8String& path);
		static Void WriteAllBytes(const U8String& path, const Void* buffer, SizeType byteCount);
	private:
		Void* handle;
	};
}