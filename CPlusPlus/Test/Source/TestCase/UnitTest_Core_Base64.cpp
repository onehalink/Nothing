#include "../TestFramework.h"



static Void UnitTest_Core_Base64()
{

	U8String output;
	BUILD_OUTPUT_FILENAME(output);
	File file(output, File::Mode::Write);

	U8String input = "Base64";

	auto encoded = Base64::Encode(input, input.GetCount());
	auto decoded = Base64::Decode(encoded.GetBuffer(), encoded.GetCount());

	U8String encodedText;
	{
		Span<Char8> span(encoded.GetCount() + 1);
		SetNullTerminatorForRawString(span);

		Memory::Copy(encoded.GetBuffer(), span.GetBuffer(), encoded.GetCount());

		encodedText = span;
	}

	U8String decodedText;
	{
		Span<Char8> span(decoded.GetCount() + 1);
		SetNullTerminatorForRawString(span);

		Memory::Copy(decoded.GetBuffer(), span.GetBuffer(), decoded.GetCount());

		decodedText = span;
	}

	WriteFormatString(file, "Encode\nInput = {}\nOutput = {}\n\n", input, encodedText);

	WriteFormatString(file, "Decode\nInput = {}\nOutput = {}\n\n", encodedText, decodedText);
}


EXEC_ONCE(UnitTest_Core_Base64);