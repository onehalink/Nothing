#pragma once

#include "../../../Core.h"



namespace Engine
{
	struct ENGINE_API Keyboard
	{
	public:
		enum class Key
		{
			Unknown,


			// Function keys
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,


			// Control keys
			Escape,
			BackSpace,
			Tabulation,
			CapitalsLock,
			Enter,
			SpaceBar,

			Insert,
			Delete,
			Home,
			End,
			PageUp,
			PageDown,

			LeftArrow,
			RightArrow,
			DownArrow,
			UpArrow,


			// Modifier keys
			Shift,
			Control,
			Window,
			Alternate,


			// Punctuation keys
			GraveAccent,		// `~
			Minus,				// -_
			Equal,				// =+
			LeftSquareBracket,	// [{
			RightSquareBracket,	// ]}
			BackSlash,			// \|
			Semicolon,			// ;:
			Apostrophe,			// '"
			Comma,				// ,<
			Period,				// .>
			Slash,				// /?


			// 0 - 9 keys
			Zero,
			One,
			Two,
			Tree,
			Four,
			Five,
			Six,
			Seven,
			Eight,
			Nine,


			// A - Z keys
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			y,
			Z,


			Count,
		};


		enum class State
		{
			Press	= 1 << 0,
			Release	= 1 << 1,

			Click	= Press | Release,
		};
		CLASS_ENUMCLASS_FLAGS(State);


		static constexpr SizeType KeyCount = static_cast<EnumUnderlyingType<Key>>( Key::Count );


		State keys[KeyCount];


		Keyboard();


		Void UpdateKeyState(Key key, State state);

		Bool KeyPressed(Key key) const;
		Bool KeyReleased(Key key) const;
		Bool KeyClicked(Key key) const;

		Void Reset();


		static Char8 GetKeyContent(Key key, Bool shiftDown);
		static Key KeyMap(Int32 keyCode);
	};
}