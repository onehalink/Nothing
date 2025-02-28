#pragma once

#include "../../TestFramework.h"



 Void Run()
{
	 Variant<U8String, U16String, U32String> variant;

	 variant = { InPlaceType<U8String>(), "Hello, U8String" };
	 ASSERT(variant.IsType<U8String>());
	 ASSERT((U8StringView)variant.Get<U8String>() == "Hello, U8String"U8SV);

	// ASSERT(false);

	 variant = { InPlaceType<U16String>(), "Hello, U16String" };
	 ASSERT(variant.IsType<U16String>());
	 ASSERT((U16StringView)variant.Get<U16String>() == L"Hello, U16String"U16SV);

	 //ASSERT(false);

	 variant = { InPlaceType<U32String>(), "Hello, U32String" };
	 ASSERT(variant.IsType<U32String>());
	 ASSERT((U32StringView)variant.Get<U32String>() == U"Hello, U32String"U32SV);

	 //ASSERT(false);

	 variant.Emplace<U8String>("EmplaceTest");
	 ASSERT((U8StringView)variant.Get<U8String>() == "EmplaceTest"U8SV);
}


EXEC_ONCE(Run);