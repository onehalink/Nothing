#pragma once

#include "../../Core.h"



namespace Engine::Windows
{
	struct ENGINE_API Clipboard
	{
		static Optional<U16String> ReadText();
		static Bool WriteText(const U16String& text);
	};
}