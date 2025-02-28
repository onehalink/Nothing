#pragma once

#include "IBehaviour.h"



namespace Engine::IMUI
{
	struct ENGINE_API ScrollBar : IBehaviour
	{
		struct Grab
		{
			RectangleInt rectangle;

			Color normal;
			Color hover;
			Color highlighted;
			Color currentColor;

			Color border;

			Bool holded;
			Vector2Int lastPosition;
			Vector2Int beginDrag;

			RealType renderSize; // the size of ScrollBar grab where 1 means it fills the entire ScrollBar

			RectangleInt moveLimit;
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


		ScrollBar();
		ScrollBar(const Vector2Int& position, const Vector2Int& size, Direction direction = Direction::LeftToRight, Action<RealType> OnValueChange = nullptr);


		Void Update(const EventSystem& eventSystem) override;
		Void Render(IDrawable* interface) override;
	public:
		Void SetPosition(const Vector2Int& position);
		Void SetSize(const Vector2Int& size);
		Void SetDirection(Direction direction);
		Void SetGrabRenderSize(RealType renderSize);
	private:
		Void UpdateInternal();
	private:
		Bool isDirty;
		SizeType axisIndex;
		Bool reverseValue;
	};
}