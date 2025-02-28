#include "Cursor.h"

#include "Windows.h"



namespace Engine::Windows
{
	const Cursor Cursor_Arrow		= LoadCursorW(nullptr, IDC_ARROW);
	const Cursor Cursor_Ibeam		= LoadCursorW(nullptr, IDC_IBEAM);
	const Cursor Cursor_Wait		= LoadCursorW(nullptr, IDC_WAIT);
	const Cursor Cursor_Cross		= LoadCursorW(nullptr, IDC_CROSS);
	const Cursor Cursor_UpArrow		= LoadCursorW(nullptr, IDC_UPARROW);
	const Cursor Cursor_SizeNWSE	= LoadCursorW(nullptr, IDC_SIZENWSE);
	const Cursor Cursor_SizeNESW	= LoadCursorW(nullptr, IDC_SIZENESW);
	const Cursor Cursor_SizeWE		= LoadCursorW(nullptr, IDC_SIZEWE);
	const Cursor Cursor_SizeNS		= LoadCursorW(nullptr, IDC_SIZENS);
	const Cursor Cursor_SizeAll		= LoadCursorW(nullptr, IDC_SIZEALL);
	const Cursor Cursor_No			= LoadCursorW(nullptr, IDC_NO);
	const Cursor Cursor_Hand		= LoadCursorW(nullptr, IDC_HAND);
	const Cursor Cursor_AppStarting	= LoadCursorW(nullptr, IDC_APPSTARTING);
	const Cursor Cursor_Help		= LoadCursorW(nullptr, IDC_HELP);
	const Cursor Cursor_Pin			= LoadCursorW(nullptr, IDC_PIN);
	const Cursor Cursor_Persion		= LoadCursorW(nullptr, IDC_PERSON);
}