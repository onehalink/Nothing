#pragma once

#include "../../Core.h"



namespace Engine::Windows
{
	struct ENGINE_API FileDialog
	{
		static Result<U16String> Open(ReadOnlySpan<U16StringView> filters = L"*.*"U16SV, const U16String& initialDirectory = L"./", const U16String& title = L"Open file", Void* owner = nullptr /** window handle */);
		static Result<U16String> Save(ReadOnlySpan<U16StringView> filters = L"*.*"U16SV, const U16String& initialDirectory = L"./", const U16String& title = L"Save as..", Void* owner = nullptr);
	};
}