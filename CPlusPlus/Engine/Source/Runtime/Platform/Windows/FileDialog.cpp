#include "FileDialog.h"

#include "Windows.h"



namespace Engine::Windows
{
	using Callback = BOOL(APIENTRY*)(OPENFILENAMEW*);


	static U16String CombineFilters(ReadOnlySpan<U16StringView> filters)
	{
		StringBuilder<Char16> result;
		for (auto filter : filters)
			result.Append('(').Append(filter).Append(')').
			Append('\0').Append(filter).Append('\0');

		return result.ToString();
	}

	static Result<U16String> OpenDialog(ReadOnlySpan<U16StringView> filters, const U16String& initialDirectory, const U16String& title, Void* owner, Callback Fn)
	{
		Char16 buffer[512];
		MemoryClear( buffer, CountArray(buffer) );

		U16String combined = CombineFilters(filters);

		OPENFILENAMEW descriptor;
		MemoryClear( &descriptor );
		descriptor.lStructSize		= sizeof(descriptor);
		descriptor.hwndOwner		= reinterpret_cast<HWND>(owner);
		descriptor.lpstrFilter		= combined.GetBuffer();
		descriptor.lpstrFile		= buffer;
		descriptor.nMaxFile			= CountArray(buffer);
		descriptor.lpstrInitialDir	= initialDirectory.GetBuffer();
		descriptor.lpstrTitle		= title.GetBuffer();
		descriptor.Flags			= OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if( Fn( &descriptor ) )
			return { InPlaceIndex<1>(), reinterpret_cast<const Char16*>(buffer) };

		return { InPlaceIndex<0>(), "canceled" };
	}


	Result<U16String> FileDialog::Open(ReadOnlySpan<U16StringView> filters, const U16String& initialDirectory, const U16String& title, Void* owner)
	{
		return OpenDialog(filters, initialDirectory, title, owner, GetOpenFileNameW);
	}

	Result<U16String> FileDialog::Save(ReadOnlySpan<U16StringView> filters, const U16String& initialDirectory, const U16String& title, Void* owner)
	{
		return OpenDialog(filters, initialDirectory, title, owner, GetSaveFileNameW);
	}
}
