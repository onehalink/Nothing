#pragma once



// Avoids that function is redefined from vcruntime_new.h header file at line 162
#if defined(COMPILER_MSVC)
	#if !defined(__PLACEMENT_NEW_INLINE)
	#define __PLACEMENT_NEW_INLINE
	#endif
#endif


constexpr void* operator new(decltype(sizeof(void*)) size, void* address)
{
	return address;
}