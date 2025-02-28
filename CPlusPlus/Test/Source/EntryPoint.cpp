#include "TestFramework.h"


#include <type_traits>


int main(int count, char** parameters)
{
	if (!Directory::Exist(OutputDirectory))
		Directory::Create(OutputDirectory);

	return 0;
}