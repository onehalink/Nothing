#pragma once

#include "Icon.h"



namespace Engine::Windows
{
	using Cursor = Icon;


	/**
	* Reference from https://learn.microsoft.com/en-us/windows/win32/menurc/about-cursors
	* 
	* @remark
	* Windows system cursor
	*/
	extern ENGINE_API const Cursor Cursor_Arrow;
	extern ENGINE_API const Cursor Cursor_Ibeam;
	extern ENGINE_API const Cursor Cursor_Wait;
	extern ENGINE_API const Cursor Cursor_Cross;
	extern ENGINE_API const Cursor Cursor_UpArrow;
	extern ENGINE_API const Cursor Cursor_SizeNWSE;
	extern ENGINE_API const Cursor Cursor_SizeNESW;
	extern ENGINE_API const Cursor Cursor_SizeWE;
	extern ENGINE_API const Cursor Cursor_SizeNS;
	extern ENGINE_API const Cursor Cursor_SizeAll;
	extern ENGINE_API const Cursor Cursor_No;
	extern ENGINE_API const Cursor Cursor_Hand;
	extern ENGINE_API const Cursor Cursor_AppStarting;
	extern ENGINE_API const Cursor Cursor_Help;
	extern ENGINE_API const Cursor Cursor_Pin;
	extern ENGINE_API const Cursor Cursor_Persion;
}