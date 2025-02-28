#pragma once

#include "../../TestFramework.h"



static Void Run()
{
	using namespace Unicode;


	U8StringView u8TestText = LITERAL(Char8, "测试文本");
	U16StringView u16TestText = LITERAL(Char16, "测试文本");
	U32StringView u32TestText = LITERAL(Char32, "测试文本");

	ASSERT(
		GetEncodedLength<Encoding::UTF8>(u8TestText.GetBuffer(), u8TestText.GetCount()) ==
		u32TestText.GetCount()
	);
	ASSERT(
		GetEncodedLength<Encoding::UTF16>(u16TestText.GetBuffer(), u16TestText.GetCount()) ==
		u32TestText.GetCount()
	);
	ASSERT(
		GetDecodedLength<Encoding::UTF8>(u32TestText.GetBuffer(), u32TestText.GetCount()) ==
		u8TestText.GetCount()
	);
	ASSERT(
		GetDecodedLength<Encoding::UTF16>(u32TestText.GetBuffer(), u32TestText.GetCount()) ==
		u16TestText.GetCount()
	);

	ASSERT(
		(U32StringView)U32String(u8TestText) ==
		u32TestText);
	ASSERT(
		(U32StringView)U32String(u16TestText) ==
		u32TestText);
	ASSERT(
		(U8StringView)U8String(u32TestText) ==
		u8TestText);
	ASSERT(
		(U16StringView)U16String(u32TestText) ==
		u16TestText);

	//ASSERT(false);
}


EXEC_ONCE(Run);