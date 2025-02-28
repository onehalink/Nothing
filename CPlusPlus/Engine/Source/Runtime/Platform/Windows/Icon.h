#pragma once

#include "../../Asset/Texture.h"



namespace Engine::Windows
{
	struct Icon;
	using Cursor = Icon;


	struct ENGINE_API Icon : NonCopyable
	{
		/**
		* Reference from https://learn.microsoft.com/en-us/windows/win32/menurc/about-cursors
		*
		* @remark
		* Windows system cursor
		*/
		static const Cursor Arrow;
		static const Cursor Ibeam;
		static const Cursor Wait;
		static const Cursor Cross;
		static const Cursor UpArrow;
		static const Cursor SizeNWSE;
		static const Cursor SizeNESW;
		static const Cursor SizeWE;
		static const Cursor SizeNS;
		static const Cursor SizeAll;
		static const Cursor No;
		static const Cursor Hand;
		static const Cursor AppStarting;
		static const Cursor Help;
		static const Cursor Pin;
		static const Cursor Persion;


		Void* handle;


		Icon(Void* handle);
		/**
		* @remark
		* xHotspot and yHotspot are ignored if !asSystemCursor
		*/
		Icon(const Texture& texture, Bool asSystemCursor = false, SizeType xHotspot = 0, SizeType yHotspot = 0);
		Icon(const U8String& executableFilePath);
		~Icon();


		Void AttachToWindow(Void* windowHandle) const;
		Void SetAsSystemCursor() const;

		Texture Extract() const;
	};
}