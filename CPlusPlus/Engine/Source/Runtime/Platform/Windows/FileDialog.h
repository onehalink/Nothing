#pragma once

#include "../../Core.h"



namespace Engine::Windows
{
	struct ENGINE_API FileDialog
	{
		static Bool Open(U16String* outputResult, const Array<U16String>& filters = { InPlace(), "*.*" }, const U16String& initialDirectory = "./", const U16String& title = "Open file", Void* owner = nullptr /** window handle */);
		static Bool Save(U16String* outputResult, const Array<U16String>& filters = { InPlace(), "*.*" }, const U16String& initialDirectory = "./", const U16String& title = "Save as..", Void* owner = nullptr);
	};
}