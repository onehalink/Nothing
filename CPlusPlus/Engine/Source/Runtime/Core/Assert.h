#pragma once

#include "Build.h"



#if defined(DEBUG)
	#if defined(COMPILER_MSVC)
	#define ASSERT(condition, ...) if ( !(condition) ) __debugbreak()
	#else
	#error ASSERT is undefined
	#endif
#else
	#define ASSERT(condition, ...) /** do nothing here */
#endif