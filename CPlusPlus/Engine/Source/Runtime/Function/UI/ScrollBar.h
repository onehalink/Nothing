#pragma once

#include "UI.h"



namespace Engine::UI
{
	struct ENGINE_API ScrollBar
	{
		struct Grab
		{
			RectangleInt rectangle;
			RectangleInt moveLimit;

			Color normal;
			Color hover;
			Color highlighted;
			Color currentColor;

			Color border;

			Bool holded;
			Vector2Int lastPosition;
			Vector2Int beginDrag;

			RealType renderSize; // the size of ScrollBar grab where 1 means it fills the entire ScrollBar
		};


		Action<RealType> OnValueChange;

		RectangleInt rectangle;

		Color background;
		Color border;

		Bool active;
		Bool visible;

		Direction direction;
		RealType value; // between [0, 1]
		RealType lastValue;

		Grab grab;
		SizeType axisIndex;
		Bool reverseValue;

		Bool isDirty;


		ScrollBar();
		ScrollBar(const Vector2Int& position, const Vector2Int& size, Direction direction = Direction::LeftToRight, Action<RealType> OnValueChange = nullptr);


		Void Update(const InputSystem& inputSystem);
		Void Render(IDrawable* interface);
	private:
		Void InitInternal();
		Void UpdateInternal();
	};
}