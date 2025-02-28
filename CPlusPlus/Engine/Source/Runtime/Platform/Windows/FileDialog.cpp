#include "FileDialog.h"

#include "Windows.h"



namespace Engine::Windows
{
	using Callback = BOOL(APIENTRY*)(OPENFILENAMEW*);


	static U8String CombineFilters(const DynamicArray<U8String>& filters)
	{
		StringBuilder<Char8> ret;
		for (const auto& filter : filters)
			ret.Append("(").Append(filter).Append(")").
			Append("\0", 1).Append(filter).Append("\0", 1);

		return ret.ToString();
	}

	static Optional<U8String> OpenDialog(const DynamicArray<U8String>& filters, const U8String& initialDirectory, const U8String& title, Void* owner, Callback Fn)
	{
		constexpr SizeType size = 512;
		Char16 buffer[512];
		MemoryOp::Clear( buffer, sizeof(Char16) * size );

		U16String u16CombinedFilter		= static_cast<U16String>( CombineFilters(filters) );
		U16String u16InitialDirectory	= static_cast<U16String>(initialDirectory);
		U16String u16Title				= static_cast<U16String>(title);

		OPENFILENAMEW descriptor;
		MemoryOp::Clear( &descriptor );
		descriptor.lStructSize		= sizeof(descriptor);
		descriptor.hwndOwner		= reinterpret_cast<HWND>(owner);
		descriptor.lpstrFilter		= u16CombinedFilter;
		descriptor.lpstrFile		= buffer;
		descriptor.nMaxFile			= size;
		descriptor.lpstrInitialDir	= u16InitialDirectory;
		descriptor.lpstrTitle		= u16Title;
		descriptor.Flags			= OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if( Fn( &descriptor ) )
			return static_cast<U8String>( U16String(buffer) );
		else
			return NullOptional();
	}


	Optional<U8String> FileDialog::Open(const DynamicArray<U8String>& filters, const U8String& initialDirectory, const U8String& title, Void* owner)
	{
		return OpenDialog(filters, initialDirectory, title, owner, GetOpenFileNameW);
	}

	Optional<U8String> FileDialog::Save(const DynamicArray<U8String>& filters, const U8String& initialDirectory, const U8String& title, Void* owner)
	{
		return OpenDialog(filters, initialDirectory, title, owner, GetSaveFileNameW);
	}
}
