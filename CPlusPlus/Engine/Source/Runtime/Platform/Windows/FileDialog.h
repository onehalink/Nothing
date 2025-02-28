#pragma once

#include "../../Core.h"



namespace Engine::Windows
{
	struct ENGINE_API FileDialog
	{
		static Nullable<U8String> Open(const DynamicArray<U8String>& filters = { InPlace(), "*.*" }, const U8String& initialDirectory = "./", const U8String& title = "Open file", Void* owner = nullptr /** window handle */);
		static Nullable<U8String> Save(const DynamicArray<U8String>& filters = { InPlace(), "*.*" }, const U8String& initialDirectory = "./", const U8String& title = "Save as..", Void* owner = nullptr);
	};
}