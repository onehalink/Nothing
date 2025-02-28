#pragma once

/**
* Note:
* Dont use any predefined values(not compile-time constant) from Engine!!
*/

#include "Engine.h"



using namespace Engine;


#define EXEC_ONCE(Fn, ...) \
struct __##Fn{\
	__##Fn(){ Fn(__VA_ARGS__); }\
} __##Fn##_value{};


#define BUILD_OUTPUT_FILENAME(outputResult) \
{\
	outputResult = Path::Combine(OutputDirectory, U8String(__FUNCTION__) + U8String(".txt"));\
	if (File::Exist(outputResult))\
		File::Delete(outputResult);\
}


const U8String OutputDirectory = "TestResult";


inline Void WriteString(File& file, const U8String& text)
{
	file.Write(text, text.GetCount());
}

template<typename ...Parameters>
Void WriteFormatString(File& file, const U8String& format, Parameters&&... parameters)
{
	WriteString(file, Format(format, Forward<Parameters>(parameters)...));
}

template<typename T>
U8String GetArrayString(const Array<T>& array)
{
	//static_assert(IsInteger<T>::Value || IsFloatPoint<T>::Value || TypesAreSame<T, Bool>::Value);

	U8String ret;
	for (auto& value : array)
		ret += Format("{}, ", value);

	return ret;
}

template<typename T>
Void WriteArray(File& file, const Array<T>& array)
{
	WriteString(file, GetArrayString(array));
}

template<typename T>
Void WriteArrayInfo(File& file, const Array<T>& array)
{
	WriteFormatString(file, "Count = {}, Capacity = {}", array.GetCount(), array.GetCapacity());
}

template<typename T>
U8String GetLinkedListString(const LinkedList<T>& list)
{
	U8String ret;
	for(auto& value : list)
		ret += Format("{}, ", value.element);

	return ret;
}