#pragma once

#include "../../../Core.h"



namespace Engine
{
	class ENGINE_API File
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


		NONCOPYABLE(File)
		File(U8StringView path, Mode mode);
		~File();


		Void Seek(Whence whence, Int64 offset);

		Void Read(Span<Byte> buffer);
		Void Write(ReadOnlySpan<Byte> bytes);


		static Void Copy(U8StringView from, U8StringView to);
		static Void Delete(U8StringView path);
		static Bool Exist(U8StringView path);
		static SizeType GetFileSize(U8StringView path);
		static Void Move(U8StringView from, U8StringView to);

		// Opens a binary file, reads the contents of the file into a byte array, and then closes the file.
		static Memory<Byte> ReadAllBytes(U8StringView path);
		/**
		* Creates a new file, writes the specified byte array to the file, and then closes the file.
		* If the target file already exists, it is overwritten.
		*/
		static Void WriteAllBytes(U8StringView path, ReadOnlySpan<Byte> bytes);
	private:
		Void* handle;
	};
}