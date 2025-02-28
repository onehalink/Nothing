#pragma once

#include "Keyboard.h"



namespace Engine
{
	struct ENGINE_API Mouse
	{
		enum class Button
		{
			Unknown,

			Left,
			Right,
			Middle,

			Count,
		};


		using State = Keyboard::State;


		static constexpr SizeType ButtonCount = static_cast<EnumUnderlyingType<Button>>( Button::Count );


		State		buttons[ButtonCount];
		Vector2Int	position;
		Int32		wheelValue;


		Mouse();


		Void UpdateButtonState(Button button, State state);

		Bool ButtonPressed(Button button) const;
		Bool ButtonReleased(Button button) const;
		Bool ButtonClicked(Button button) const;

		Void Reset();


		static Button ButtonMap(Int32 buttonCode);
	};
}