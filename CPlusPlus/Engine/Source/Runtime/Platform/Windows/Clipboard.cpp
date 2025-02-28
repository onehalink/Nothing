#include "Clipboard.h"

#include "Windows.h"



namespace Engine::Windows
{
	Bool Clipboard::ReadText(U16String* outputResult)
	{
		if ( !IsClipboardFormatAvailable(CF_UNICODETEXT) )
			return false;

		if ( !OpenClipboard(nullptr) )
			return false;

		HANDLE clipboardHandle = GetClipboardData(CF_UNICODETEXT);
		if ( !clipboardHandle )
		{
			CloseClipboard();

			return false;
		}

		if (outputResult)
		{
			Void* text		= GlobalLock(clipboardHandle);
			*outputResult	= reinterpret_cast<Char16*>(text);

			GlobalUnlock(clipboardHandle);
		}
		
		CloseClipboard();

		return true;
	}

	Bool Clipboard::WriteText(const U16String& text)
	{
		if ( !OpenClipboard(nullptr) )
			return false;

		if ( !EmptyClipboard() )
		{
			CloseClipboard();

			return false;
		}

		SizeType totalStringSize	= sizeof(Char16) * ( text.GetCount() + 1 );
		HANDLE stringHandle			= GlobalAlloc(GMEM_MOVEABLE, totalStringSize);
		if ( !stringHandle )
		{
			CloseClipboard();

			return false;
		}

		Memory::Copy( text, GlobalLock(stringHandle), totalStringSize );
		GlobalUnlock(stringHandle);

		SetClipboardData(CF_UNICODETEXT, stringHandle);

		CloseClipboard();

		return true;
	}
}