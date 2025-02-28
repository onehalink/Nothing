#pragma once



/**
* Compiler
* 
* Support:
* 1.Microsoft C++ compiler
*/
#if defined(_MSC_VER)
#define COMPILER_MSVC
#else
#error Unknown C++ compiler
#endif


/**
* Standard
* 
* Require:
* C++17 or later
*/
#if defined(COMPILER_MSVC) && (_MSVC_LANG < 201703)
#error C++17 required
#endif


/**
* Platform
* 
* Support:
* 1.Windows 64-bit
*/
#if defined(COMPILER_MSVC) && defined(_WIN64)
#define PLATFORM_WINDOWS
#else
#error Current platform is not supported
#endif


#pragma region Export/Import dynamic link library

#if defined(COMPILER_MSVC)
#define _DLL_EXPORT __declspec(dllexport)
#define _DLL_IMPORT __declspec(dllimport)
#endif


#if !defined(ENGINE_API_IMPORTS)
#define ENGINE_API	_DLL_EXPORT
#else
#define ENGINE_API	_DLL_IMPORT
#endif

#pragma endregion


#if defined(COMPILER_MSVC) && defined(_DEBUG)
	#if !defined(DEBUG)
	#define DEBUG
	#endif
#endif


// Check runtime error
#if defined(DEBUG)
#define ASSERT(condition, ...)	if( !(condition) ) *reinterpret_cast<char*>(0) = 0 /** Throw access violation exception */
#else
#define ASSERT(condition, ...) // do nothing
#endif


#pragma region Enable bitwise operators(&, |, ^ and ~) for (nested)enum class

#define _ENUMCLASS_OP_UNARY(EnumClass, Op)									\
constexpr EnumClass operator##Op(EnumClass E)								\
{																			\
	return EnumClass( Op##static_cast<__underlying_type(EnumClass)>(E) );	\
}


#define _ENUMCLASS_OP_BINARY(EnumClass, Op)																					\
constexpr EnumClass operator##Op(EnumClass L, EnumClass R)																	\
{																															\
	return EnumClass( static_cast<__underlying_type(EnumClass)>(L) ## Op ## static_cast<__underlying_type(EnumClass)>(R) );	\
}


#define _ENUMCLASS_OP_BINARY_ASSIGNMENT(EnumClass, Op)	inline EnumClass& operator##Op##=(EnumClass& L, EnumClass R) { return L = L ## Op ## R; }


#define _ENUMCLASS_OP_BINARY_PACKED(EnumClass, Op)	\
_ENUMCLASS_OP_BINARY(EnumClass, Op)					\
_ENUMCLASS_OP_BINARY_ASSIGNMENT(EnumClass, Op)


#define _CLASS_ENUMCLASS_OP_BINARY_PACKED(EnumClass, Op)	\
friend _ENUMCLASS_OP_BINARY(EnumClass, Op)					\
friend _ENUMCLASS_OP_BINARY_ASSIGNMENT(EnumClass, Op)


#define ENUMCLASS_FLAGS(EnumClass)			\
_ENUMCLASS_OP_BINARY_PACKED(EnumClass, &)	\
_ENUMCLASS_OP_BINARY_PACKED(EnumClass, |)	\
_ENUMCLASS_OP_BINARY_PACKED(EnumClass, ^)	\
_ENUMCLASS_OP_UNARY(EnumClass, ~)


#define CLASS_ENUMCLASS_FLAGS(EnumClass)			\
_CLASS_ENUMCLASS_OP_BINARY_PACKED(EnumClass, &)		\
_CLASS_ENUMCLASS_OP_BINARY_PACKED(EnumClass, |)		\
_CLASS_ENUMCLASS_OP_BINARY_PACKED(EnumClass, ^)		\
friend _ENUMCLASS_OP_UNARY(EnumClass, ~)

#pragma endregion