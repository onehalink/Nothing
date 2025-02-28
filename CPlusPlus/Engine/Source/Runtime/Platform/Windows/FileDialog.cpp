#include "FileDialog.h"

#include "Windows.h"



namespace Engine::Windows
{
	using Callback = BOOL(APIENTRY*)(OPENFILENAMEW*);


	static U16String CombineFilters(const Array<U16String>& filters)
	{
		U16String ret;
		for (auto& filter : filters)
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

	static Bool OpenDialog(U16String* outputResult, const Array<U16String>& filters, const U16String& initialDirectory, const U16String& title, Void* owner, Callback Fn)
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

		Bool ret = Fn( &descriptor );

		if (outputResult)
			*outputResult = temporary.GetBuffer();

		return ret != 0;
	}


	Bool FileDialog::Open(U16String* outputResult, const Array<U16String>& filters, const U16String& initialDirectory, const U16String& title, Void* owner)
	{
		return OpenDialog(outputResult, filters, initialDirectory, title, owner, GetOpenFileNameW);
	}

	Bool FileDialog::Save(U16String* outputResult, const Array<U16String>& filters, const U16String& initialDirectory, const U16String& title, Void* owner)
	{
		return OpenDialog(outputResult, filters, initialDirectory, title, owner, GetSaveFileNameW);
	}
}
