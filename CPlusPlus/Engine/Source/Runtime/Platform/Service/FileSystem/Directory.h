#pragma once

#include "File.h"
#include "Path.h"



namespace Engine
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


		static Void Copy(U8StringView from, U8StringView to);
		static Void Create(U8StringView path);
		static Void Delete(U8StringView path);
		static Bool Exist(U8StringView path);
		static Void Move(U8StringView from, U8StringView to);

		static Void EnumerateEntries(U8StringView path, Action<U8StringView> Visitor, SearchOption searchOption = SearchOption::All);
	};
}