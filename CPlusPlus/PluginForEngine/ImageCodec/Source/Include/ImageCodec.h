#pragma once



/**
* [Include]
*
* Path(Visual Studio Macro): $(SolutionDir)CPlusPlus/PluginForEngine/ImageCodec/Source/Include
*/


/**
* [Link]
*
* Path(Visual Studio Macro): $(SolutionDir)Binary/CPlusPlus/$(Configuration)/$(Platform)
*/
#pragma comment(lib, "ImageCodec")


/**
* Import plugin
*/
#if !defined(ENGINE_PLUGIN_API_IMPORTS)
#define ENGINE_PLUGIN_API_IMPORTS
#endif


#include "../API/Image.h"