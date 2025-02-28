#include "../TestFramework.h"



static Void UnitTest_Core_Container_LinkedList()
{
	using List = LinkedList<Int32>;
	using Node = typename List::Node;


	constexpr SizeType RequiredSize = 8;

	constexpr Int32 Min = 0;
	constexpr Int32 Max = 50;


	U8String output;
	BUILD_OUTPUT_FILENAME(output);
	File file(output, File::Mode::Write);

	List list;
	for (SizeType index = 0; index < RequiredSize; index++)
	{
		auto node = Node::Create();
		node->element = Random(Min, Max);

		list.Add(node);
	}

	WriteFormatString(file, "Initial\nCount = {} Elements: {}\n\n", list.GetCount(), GetLinkedListString(list));

	{
		auto node = Node::Create();
		node->element = Random(Min, Max);

		Int32 index = 0;

		list.InsertAt(index, node);
		WriteFormatString(file, "Op(InsertAt)\nIndex: {}\nValue(Node): {}\nCount = {} Elements: {}\n\n", index, node->element, list.GetCount(), GetLinkedListString(list));
	}

	{
		Int32 index = 1;

		list.RemoveAt(index);
		WriteFormatString(file, "Op(RemoveAt)\nIndex: {}\nCount = {} Elements: {}\n\n", index, list.GetCount(), GetLinkedListString(list));
	}

	{
		list.Clear();
		WriteFormatString(file, "Op(Clear)\nCount = {} Elements: {}\n\n", list.GetCount(), GetLinkedListString(list));
	}
}


EXEC_ONCE(UnitTest_Core_Container_LinkedList);