#pragma once

/**
* Predefined Macros
*/



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


#pragma region Macro helper

#if defined(COMPILER_MSVC) && defined(_DEBUG)
	#if !defined(DEBUG)
	#define DEBUG
	#endif
#endif

#pragma endregion


#pragma region Export/Import dynamic link library

#if defined(COMPILER_MSVC)
#define DLL_EXPORT	__declspec(dllexport)
#define DLL_IMPORT	__declspec(dllimport)
#else
#error DLL_EXPORT and DLL_IMPORT are undefined
#endif


#if !defined(ENGINE_API_IMPORTS)
#define ENGINE_API	DLL_EXPORT
#else
#define ENGINE_API	DLL_IMPORT
#endif


#if !defined(ENGINE_PLUGIN_API_IMPORTS)
#define ENGINE_PLUGIN_API	DLL_EXPORT
#else
#define ENGINE_PLUGIN_API	DLL_IMPORT
#endif

#pragma endregion


// Check runtime error
#if defined(DEBUG)
#define ASSERT(condition, ...)	if( !(condition) ) *reinterpret_cast<char*>(0) = 0 /** throw access violation exception */
#else
#define ASSERT(condition, ...) /** do nothing */
#endif


#pragma region Enable bitwise operators(&, |, ^ and ~) for nested enum class

#define _CLASS_ENUMCLASS_OP_UNARY(EnumClass, Op)							\
friend constexpr EnumClass operator##Op(EnumClass E)						\
{																			\
	return EnumClass( Op##static_cast<__underlying_type(EnumClass)>(E) );	\
}


#define _CLASS_ENUMCLASS_OP_BINARY(EnumClass, Op)																			\
friend constexpr EnumClass operator##Op(EnumClass L, EnumClass R)															\
{																															\
	return EnumClass( static_cast<__underlying_type(EnumClass)>(L) ## Op ## static_cast<__underlying_type(EnumClass)>(R) );	\
}																															\
																															\
friend EnumClass& operator##Op##=(EnumClass& L, EnumClass R)																\
{																															\
	return L = L ## Op ## R;																								\
}


#define CLASS_ENUMCLASS_FLAGS(EnumClass)	\
_CLASS_ENUMCLASS_OP_BINARY(EnumClass, &)	\
_CLASS_ENUMCLASS_OP_BINARY(EnumClass, |)	\
_CLASS_ENUMCLASS_OP_BINARY(EnumClass, ^)	\
_CLASS_ENUMCLASS_OP_UNARY(EnumClass, ~)

#pragma endregion


// Disable class's copy/move constructors and copy/move assignment operators
#define NONCOPYABLE(Type)					\
		Type(const Type&)		= delete;	\
		Type(Type&&)			= delete;	\
Type&	operator=(const Type&)	= delete;	\
Type&	operator=(Type&&)		= delete