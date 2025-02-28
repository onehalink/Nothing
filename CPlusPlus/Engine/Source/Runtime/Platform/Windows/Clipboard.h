#pragma once

#include "../../Core.h"



namespace Engine::Windows
{
	struct ENGINE_API Clipboard
	{
		static Bool ReadText(U16String* outputResult);
		static Bool WriteText(const U16String& text);
	};
}