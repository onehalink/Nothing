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


#pragma region Symbol export/import

#if defined(COMPILER_MSVC)
#define _DLL_EXPORT __declspec(dllexport)
#define _DLL_IMPORT __declspec(dllimport)
#else
#error _DLL_EXPORT and _DLL_IMPORT are undefined
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