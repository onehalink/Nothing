#pragma once

#include "../../Core.h"



namespace Engine::Windows
{
	struct ENGINE_API FileDialog
	{
		static Optional<U16String> Open(const Array<U16String>& filters = { InPlace(), "*.*" }, const U16String& initialDirectory = "./", const U16String& title = "Open file", Void* owner = nullptr /** window handle */);
		static Optional<U16String> Save(const Array<U16String>& filters = { InPlace(), "*.*" }, const U16String& initialDirectory = "./", const U16String& title = "Save as..", Void* owner = nullptr);
	};
}