#pragma once

#include "File.h"
#include "Path.h"



namespace Engine::FileSystem
{
	class ENGINE_API Directory
	{
	public:
		enum class SearchOption
		{
			File		= 1 << 0,
			Directory	= 1 << 1,

			All			= File | Directory,
		};
		CLASS_ENUMCLASS_FLAGS(SearchOption);


		static Void Copy(const U8String& from, const U8String& to);
		static Void Create(const U8String& path);
		static Void Delete(const U8String& path);
		static Bool Exist(const U8String& path);
		static Void Move(const U8String& from, const U8String& to);

		static DynamicArray<U8String> EnumerateEntries(const U8String& path, SearchOption searchOption = SearchOption::All);
	};
}