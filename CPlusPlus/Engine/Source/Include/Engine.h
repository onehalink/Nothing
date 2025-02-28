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

#include "../Runtime/Function/Interface/IRenderable.h"
#include "../Runtime/Function/Render/Render.h"
#include "../Runtime/Function/Render/Serface.h"
#include "../Runtime/Function/UI/Alignment.h"
#include "../Runtime/Function/UI/Attachment.h"
#include "../Runtime/Function/UI/DefaultAsset.h"
#include "../Runtime/Function/UI/DefaultValue.h"
#include "../Runtime/Function/UI/Element.h"
#include "../Runtime/Function/UI/Location.h"
#include "../Runtime/Function/UI/Padding.h"
#include "../Runtime/Function/UI/Custom/InnerWindow.h"
#include "../Runtime/Function/UI/Custom/InputField.h"
#include "../Runtime/Function/UI/Custom/Text.h"
#include "../Runtime/Function/UI/Custom/Tooltip.h"

#include "../Runtime/Platform/Windows/Clipboard.h"
#include "../Runtime/Platform/Windows/FileDialog.h"
#include "../Runtime/Platform/Windows/GraphicsDeviceInterface.h"
#include "../Runtime/Platform/Windows/Window.h"
#include "../Runtime/Platform/Service/Diagnostics/Debug.h"
#include "../Runtime/Platform/Service/Diagnostics/Timer.h"
#include "../Runtime/Platform/Service/FileSystem/Directory.h"
#include "../Runtime/Platform/Service/FileSystem/File.h"
#include "../Runtime/Platform/Service/FileSystem/Path.h"
#include "../Runtime/Platform/Service/Input/InputSystem.h"
#include "../Runtime/Platform/Service/Input/Keyboard.h"
#include "../Runtime/Platform/Service/Input/Mouse.h"

