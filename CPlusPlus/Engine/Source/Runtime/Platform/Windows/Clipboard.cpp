#include "Clipboard.h"

#include "Windows.h"



namespace Engine::Windows
{
	Optional<U16String> Clipboard::Clipboard::ReadText()
	{
		if ( !IsClipboardFormatAvailable(CF_UNICODETEXT) )
			return NullOptional();

		if ( !OpenClipboard(nullptr) )
			return NullOptional();

		HANDLE clipboardHandle = GetClipboardData(CF_UNICODETEXT);
		if ( !clipboardHandle )
		{
			CloseClipboard();

			return NullOptional();
		}

		U16String ret;
		{
			Void* text		= GlobalLock(clipboardHandle);
			ret				= reinterpret_cast<Char16*>(text);

			GlobalUnlock(clipboardHandle);
		}
		
		CloseClipboard();

		return ret;
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