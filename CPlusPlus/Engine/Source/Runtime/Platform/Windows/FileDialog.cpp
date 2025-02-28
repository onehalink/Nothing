#include "FileDialog.h"

#include "Windows.h"



namespace Engine::Windows
{
	using Callback = BOOL(APIENTRY*)(OPENFILENAMEW*);


	static U16String CombineFilters(const DynamicArray<U16String>& filters)
	{
		SizeType size = 0;
		for (const auto& filter : filters)
		{
			size += ( 1 + 1 ) * 2 + filter.GetCount() * 2;
		}

		Span<Char16> span( size + 1 );
		SetNullForRawString(span);

		SizeType writeCursor = 0;
		for (const auto& filter : filters)
		{
			span[ writeCursor++ ] = L'(';
			for (SizeType index = 0; index < filter.GetCount(); index++) span[ writeCursor++ ] = filter[index];
			span[ writeCursor++ ] = L')';
			span[ writeCursor++ ] = L'\0';
			for (SizeType index = 0; index < filter.GetCount(); index++) span[ writeCursor++ ] = filter[index];
			span[ writeCursor++ ] = L'\0';
		}

		return span;
	}

	static Nullable<U16String> OpenDialog(const DynamicArray<U16String>& filters, const U16String& initialDirectory, const U16String& title, Void* owner, Callback Fn)
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
			return Null();
	}


	Nullable<U16String> FileDialog::Open(const DynamicArray<U16String>& filters, const U16String& initialDirectory, const U16String& title, Void* owner)
	{
		return OpenDialog(filters, initialDirectory, title, owner, GetOpenFileNameW);
	}

	Nullable<U16String> FileDialog::Save(const DynamicArray<U16String>& filters, const U16String& initialDirectory, const U16String& title, Void* owner)
	{
		return OpenDialog(filters, initialDirectory, title, owner, GetSaveFileNameW);
	}
}
