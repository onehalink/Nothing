#pragma once

/**
* Used by the other C++ project
* 
* Note:
* Build this project as a dynamic link library
*/



/**
* For Visual Studio(Configuration Properties/General)
* 
* Output Directory:			$(SolutionDir)Binary/CPlusPlus/$(Configuration)/$(Platform)
* Intermediate Directory:	$(SolutionDir)Binary/CPlusPlus/$(Configuration)/$(Platform)/$(ProjectName)
*/


/**
* [Include]
* 
* Path(Visual Studio Macro): $(SolutionDir)CPlusPlus/Engine/Source/Include
*/


/**
* [Link]
* 
* Path(Visual Studio Macro): $(SolutionDir)Binary/CPlusPlus/$(Configuration)/$(Platform)
*/
#pragma comment(lib, "Engine")


/**
* Import engine
* 
* Note:
* As a flag to define ENGINE_API(default is DLL_EXPORT and used by this project) as DLL_IMPORT
*/
#if !defined(ENGINE_API_IMPORTS)
#define ENGINE_API_IMPORTS
#endif


/**
* API set
*/
#include "../Runtime/Core.h"

#include "../Runtime/Asset/Texture.h"

#include "../Runtime/Codec/Bitmap.h"

#include "../Runtime/Platform/HardwareAbstractLayer/Keyboard.h"
#include "../Runtime/Platform/HardwareAbstractLayer/Mouse.h"
#include "../Runtime/Platform/SoftwareAbstractLayer/Directory.h"
#include "../Runtime/Platform/SoftwareAbstractLayer/EventSystem.h"
#include "../Runtime/Platform/SoftwareAbstractLayer/File.h"
#include "../Runtime/Platform/SoftwareAbstractLayer/Path.h"
#include "../Runtime/Platform/Windows/Clipboard.h"
#include "../Runtime/Platform/Windows/FileDialog.h"
#include "../Runtime/Platform/Windows/GraphicDeviceInterface.h"
#include "../Runtime/Platform/Windows/Window.h"
//#include "../Runtime/Platform/Windows/Windows.h"