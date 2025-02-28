#pragma once



/**
* [Include]
*
* Path(Visual Studio Macro): $(SolutionDir)CPlusPlus/PluginForEngine/FontGlyphExtractor/Source/Include
*/


/**
* [Link]
*
* Path(Visual Studio Macro): $(SolutionDir)Binary/CPlusPlus/$(Configuration)/$(Platform)
*/
#pragma comment(lib, "FontGlyphExtractor")


/**
* Import plugin
*/
#if !defined(ENGINE_PLUGIN_API_IMPORTS)
#define ENGINE_PLUGIN_API_IMPORTS
#endif


#include "../API/API.h"