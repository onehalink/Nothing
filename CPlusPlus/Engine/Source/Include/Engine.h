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
#include "../Runtime/Asset/Texture.h"

#include "../Runtime/Codec/Bitmap.h"
#include "../Runtime/Codec/Wave.h"

#include "../Runtime/Function/ImmediateModeUI/Alignment.h"
#include "../Runtime/Function/ImmediateModeUI/Axis.h"
#include "../Runtime/Function/ImmediateModeUI/Button.h"
#include "../Runtime/Function/ImmediateModeUI/CircleProcessBar.h"
#include "../Runtime/Function/ImmediateModeUI/Constants.h"
#include "../Runtime/Function/ImmediateModeUI/Direction.h"
#include "../Runtime/Function/ImmediateModeUI/Helper.h"
#include "../Runtime/Function/ImmediateModeUI/IBehaviour.h"
#include "../Runtime/Function/ImmediateModeUI/ProcessBar.h"
#include "../Runtime/Function/ImmediateModeUI/ScrollBar.h"
#include "../Runtime/Function/ImmediateModeUI/ScrollView.h"
#include "../Runtime/Function/ImmediateModeUI/Text.h"
#include "../Runtime/Function/Render/2DGeometry.h"
#include "../Runtime/Function/Render/FrameBuffer.h"
#include "../Runtime/Function/Render/IDrawable.h"
#include "../Runtime/Function/Render/Serface.h"

#include "../Runtime/Platform/HAL/Keyboard.h"
#include "../Runtime/Platform/HAL/Mouse.h"
#include "../Runtime/Platform/Windows/Clipboard.h"
#include "../Runtime/Platform/Windows/Cursor.h"
#include "../Runtime/Platform/Windows/DirectSound.h"
#include "../Runtime/Platform/Windows/FileDialog.h"
#include "../Runtime/Platform/Windows/GraphicDeviceInterface.h"
#include "../Runtime/Platform/Windows/Icon.h"
#include "../Runtime/Platform/Windows/Window.h"
//#include "../Runtime/Platform/Windows/Windows.h"
#include "../Runtime/Platform/SAL/EventSystem/EventSystem.h"
#include "../Runtime/Platform/SAL/FileSystem/Directory.h"
#include "../Runtime/Platform/SAL/FileSystem/File.h"
#include "../Runtime/Platform/SAL/FileSystem/Path.h"

