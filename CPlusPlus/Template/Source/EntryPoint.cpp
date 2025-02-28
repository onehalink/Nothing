#include "Engine.h"

/**
* App template uses Engine as a library
*/



using namespace Engine;


Int32 EntryPoint()
{
	TRACE("App template uses {Project} as a library\n", "Engine");

	return 0;
}


int main(int count, char** parameters)
{
	return EntryPoint();
}

