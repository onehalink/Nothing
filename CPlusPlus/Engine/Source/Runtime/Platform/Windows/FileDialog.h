#pragma once

#include "../../Core.h"



namespace Engine::Windows
{
	struct ENGINE_API FileDialog
	{
		static Nullable<U16String> Open(const DynamicArray<U16String>& filters = { InPlace(), "*.*" }, const U16String& initialDirectory = "./", const U16String& title = "Open file", Void* owner = nullptr /** window handle */);
		static Nullable<U16String> Save(const DynamicArray<U16String>& filters = { InPlace(), "*.*" }, const U16String& initialDirectory = "./", const U16String& title = "Save as..", Void* owner = nullptr);
	};
}