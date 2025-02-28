#pragma once

#include "APISet.h"



inline Void Test_Core_Base64()
{
	std::fstream output("Test_Core_Base64.log", std::ios::out | std::ios::trunc);

	U8String text = "Base64";

	auto encodeData = Base64::Encode(text.GetBuffer(), text.GetCount());
	auto decodeData = Base64::Decode(encodeData.GetBuffer(), encodeData.GetCount());

	U8String format =
		"{Op}\n"
		"Input:{}\n"
		"Output:{}\n";

	U8String encodeText;
	{
		Span<Char8> temp(encodeData.GetCount() + 1);
		SetNullTerminatorForRawString(temp);

		Memory::Copy(encodeData.GetBuffer(), temp.GetBuffer(), encodeData.GetCount());

		encodeText = Move(temp);
	}

	U8String decodeText;
	{
		Span<Char8> temp(decodeData.GetCount() + 1);
		SetNullTerminatorForRawString(temp);

		Memory::Copy(decodeData.GetBuffer(), temp.GetBuffer(), decodeData.GetCount());

		decodeText = Move(temp);
	}

	output << Format(format, "Encode", text, encodeText);
	output << "\n";

	output << Format(format, "Decode", encodeText, decodeText);
	output << "\n";
}