#pragma once

#include "../../Core.h"



namespace Engine::Windows
{
	struct ENGINE_API Clipboard
	{
		static Nullable<U8String> ReadText();
		static Bool WriteText(const U8String& text);
	};
}