#pragma once

#include "../../Asset/Texture.h"



namespace Engine::Windows
{
	class ENGINE_API Icon : NonCopyable
	{
	public:
		Icon(Void* handle);
		/**
		* @remark
		* xHotspot and yHotspot are ignored if !asSystemCursor
		*/
		Icon(const Texture& texture, Bool asSystemCursor = false, SizeType xHotspot = 0, SizeType yHotspot = 0);
		Icon(const U16String& executableFilePath);
		~Icon();


		Texture Extract() const;


		Void* GetHandle() const;
	private:
		Void* handle;
	};
}