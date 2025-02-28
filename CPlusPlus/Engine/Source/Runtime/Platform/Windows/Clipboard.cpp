#include "Clipboard.h"

#include "Windows.h"



namespace Engine::Windows
{
	Optional<U8String> Clipboard::Clipboard::ReadText()
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

		return static_cast<U8String>(ret);
	}

	Bool Clipboard::WriteText(const U8String& text)
	{
		if ( !OpenClipboard(nullptr) )
			return false;

		if ( !EmptyClipboard() )
		{
			CloseClipboard();

			return false;
		}

		U16String u16Text = static_cast<U16String>(text);

		SizeType totalStringSize	= sizeof(Char16) * ( u16Text.GetCount() + 1 );
		HANDLE stringHandle			= GlobalAlloc(GMEM_MOVEABLE, totalStringSize);
		if ( !stringHandle )
		{
			CloseClipboard();

			return false;
		}

		MemoryOp::Copy( u16Text, GlobalLock(stringHandle), totalStringSize );
		GlobalUnlock(stringHandle);

		SetClipboardData(CF_UNICODETEXT, stringHandle);

		CloseClipboard();

		return true;
	}
}