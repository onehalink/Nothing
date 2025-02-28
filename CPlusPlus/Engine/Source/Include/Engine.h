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

#include "../Runtime/Asset/AudioClip.h"
#include "../Runtime/Asset/Font.h"
#include "../Runtime/Asset/FontSDFAtlas.h"
#include "../Runtime/Asset/Texture.h"

#include "../Runtime/Codec/Base64.h"
#include "../Runtime/Codec/Bitmap.h"
#include "../Runtime/Codec/Wave.h"

#include "../Runtime/Function/Render/2DGeometry.h"
#include "../Runtime/Function/Render/IDrawable.h"
#include "../Runtime/Function/Render/Serface.h"
#include "../Runtime/Function/UI/Button.h"
#include "../Runtime/Function/UI/CheckBox.h"
#include "../Runtime/Function/UI/CombineBox.h"
#include "../Runtime/Function/UI/ProcessBar.h"
#include "../Runtime/Function/UI/ScrollBar.h"
#include "../Runtime/Function/UI/ScrollView.h"
#include "../Runtime/Function/UI/Text.h"
#include "../Runtime/Function/UI/TextInput.h"
#include "../Runtime/Function/UI/UI.h"

#include "../Runtime/Platform/Windows/Clipboard.h"
#include "../Runtime/Platform/Windows/DirectSound.h"
#include "../Runtime/Platform/Windows/FileDialog.h"
#include "../Runtime/Platform/Windows/GraphicDeviceInterface.h"
#include "../Runtime/Platform/Windows/Icon.h"
#include "../Runtime/Platform/Windows/Window.h"
#include "../Runtime/Platform/Service/Diagnostics/Debug.h"
#include "../Runtime/Platform/Service/Diagnostics/Timer.h"
#include "../Runtime/Platform/Service/FileSystem/Directory.h"
#include "../Runtime/Platform/Service/FileSystem/File.h"
#include "../Runtime/Platform/Service/FileSystem/Path.h"
#include "../Runtime/Platform/Service/Input/InputSystem.h"
#include "../Runtime/Platform/Service/Input/Keyboard.h"
#include "../Runtime/Platform/Service/Input/Mouse.h"

