#pragma once

#include "../../Core.h"



namespace Engine
{
	class ENGINE_API Path
	{
	public:
		/**
		* @remark
		* File extension should be leading with a period(".")
		*/
		static U8String ChangeFileExtension(const U8String& path, const U8String& newFileExtension);
		static U8String Combine(const U8String& first, const U8String& second);
		template<typename ...Parameters> static U8String Combine(const U8String& first, const U8String& second, Parameters&&... parameters);
		static U8String GetDirectoryName(const U8String& path);
		static U8String GetFileExtension(const U8String& path);
		static U8String GetFileName(const U8String& path);
		static U8String GetFileNameWithoutExtension(const U8String& path);
		/**
		* @remark
		* Not check if (file/directory) existed
		* Get current process's working directory: GetFullPathName(".")
		*/
		static U8String GetFullPathName(const U8String& relativePath);
		static Array<Char32> GetInvalidFileNameCharacters();
		static Array<Char32> GetInvalidPathCharacters();
		static Bool HasFileExtension(const U8String& path);
	};


#pragma region Details

	template<typename ...Parameters>
	U8String Path::Combine(const U8String& first, const U8String& second, Parameters&&... parameters)
	{
		U8String ret = Combine(first, second);

		if constexpr ( sizeof...(parameters) > 0 )
			return Combine( ret, Forward<Parameters>(parameters)... );

		return ret;
	}

#pragma endregion
}