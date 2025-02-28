#include "Clipboard.h"

#include "Windows.h"



namespace Engine::Windows
{
	Result<U16String> Clipboard::Clipboard::ReadText()
	{
		if ( !IsClipboardFormatAvailable(CF_UNICODETEXT) )
			return { InPlaceIndex<0>(), "unicode text format is not supported" };

		if ( !OpenClipboard(nullptr) )
			return { InPlaceIndex<0>(), "failed to open clipboard" };

		HANDLE clipboardHandle = GetClipboardData(CF_UNICODETEXT);
		if ( !clipboardHandle )
		{
			CloseClipboard();

			return { InPlaceIndex<0>(), "failed to read clipboard" };
		}

		U16String result;
		{
			Void* text	= GlobalLock(clipboardHandle);
			result		= U16StringView( reinterpret_cast<const Char16*>(text) );

			GlobalUnlock(clipboardHandle);
		}
		
		CloseClipboard();

		return { InPlaceIndex<1>(), result };
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

		SizeType stringSize	= sizeof(Char16) * ( text.GetCount() + 1 );
		HANDLE stringHandle = GlobalAlloc(GMEM_MOVEABLE, stringSize);
		if ( !stringHandle )
		{
			CloseClipboard();

			return false;
		}

		MemoryCopy( GlobalLock(stringHandle), text.GetBuffer(), stringSize );
		GlobalUnlock(stringHandle);

		SetClipboardData(CF_UNICODETEXT, stringHandle);

		CloseClipboard();

		return true;
	}
}