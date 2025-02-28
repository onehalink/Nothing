#pragma once

#include "../../TestFramework.h"



static Void Run()
{
	U8StringView Input = "Base64";
	U8StringView EncodedInput = "QmFzZTY0";

	Memory<Byte> encodedBuffer(Base64::GetEncodedLength(Input.GetCount()));
	ASSERT(encodedBuffer.GetCount() == EncodedInput.GetCount());
	Base64::Encode({ (Char8*)encodedBuffer.GetBuffer(), encodedBuffer.GetCount() }, { (Byte*)Input.GetBuffer(), Input.GetCount() });
	ASSERT(MemoryEqual(EncodedInput.GetBuffer(), encodedBuffer.GetBuffer(), encodedBuffer.GetCount()));

	Memory<Byte> decodedBuffer(Base64::GetDecodedLength(EncodedInput.GetCount()));
	ASSERT(decodedBuffer.GetCount() == Input.GetCount());
	Base64::Decode({ (Byte*)decodedBuffer.GetBuffer(), decodedBuffer.GetCount() }, { (Char8*)EncodedInput.GetBuffer(), EncodedInput.GetCount() });
	ASSERT(MemoryEqual(Input.GetBuffer(), decodedBuffer.GetBuffer(), decodedBuffer.GetCount()));

	//ASSERT(false);
}


EXEC_ONCE(Run);