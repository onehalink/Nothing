#include "FileDialog.h"

#include "Windows.h"



namespace Engine::Windows
{
	using Callback = BOOL(APIENTRY*)(OPENFILENAMEW*);


	static U16String CombineFilters(const Array<U16String>& filters)
	{
		U16String ret;
		for (const auto& filter: filters)
		{
			ret += L'(';
			ret += filter;
			ret += L')';
			ret += L'\0';
			ret += filter;
			ret += L'\0';
		}

		return ret;
	}

	static Optional<U16String> OpenDialog(const Array<U16String>& filters, const U16String& initialDirectory, const U16String& title, Void* owner, Callback Fn)
	{
		Span<Char16> temporary(512);
		Memory::Clear( temporary.GetBuffer(), temporary.GetCount() );

		U16String combined = CombineFilters(filters);

		OPENFILENAMEW descriptor;
		Memory::Clear( &descriptor, sizeof(descriptor) );
		descriptor.lStructSize		= sizeof(descriptor);
		descriptor.hwndOwner		= reinterpret_cast<HWND>(owner);
		descriptor.lpstrFilter		= combined;
		descriptor.lpstrFile		= temporary.GetBuffer();
		descriptor.nMaxFile			= temporary.GetCount();
		descriptor.lpstrInitialDir	= initialDirectory;
		descriptor.lpstrTitle		= title;
		descriptor.Flags			= OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if( Fn( &descriptor ) )
			return U16String( temporary.GetBuffer() );
		else
			return NullOptional();
	}


	Optional<U16String> FileDialog::Open(const Array<U16String>& filters, const U16String& initialDirectory, const U16String& title, Void* owner)
	{
		return OpenDialog(filters, initialDirectory, title, owner, GetOpenFileNameW);
	}

	Optional<U16String> FileDialog::Save(const Array<U16String>& filters, const U16String& initialDirectory, const U16String& title, Void* owner)
	{
		return OpenDialog(filters, initialDirectory, title, owner, GetSaveFileNameW);
	}
}
