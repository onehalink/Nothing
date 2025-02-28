#pragma once

#include "UI.h"



namespace Engine::UI
{
	struct ENGINE_API ScrollBar : IBehaviour
	{
		struct Grab
		{
			Vector2Int	position;
			Vector2Int	size;
			Visual		visual;

			Bool		isHolded;
			Vector2Int	lastPosition;
			Vector2Int	beginDrag;

			RealType renderSize; // The size of the scrollbar handle where 1 means it fills the entire scrollbar

			// move limit
			Vector2Int minimum;
			Vector2Int maximum;
		};

		
		Action<RealType> OnValueChange;

		RectangleInt	rectangle;
		Color			background;
		Color			border;

		State		state;
		Bool		isDirty;
		RealType	value; // between [0, 1]
		RealType	lastValue;

		Direction	direction;
		Axis		axis;
		SizeType	index;
		Bool		reverseValue;

		Grab grab;


		ScrollBar();
		ScrollBar(const Vector2& position, const Vector2& size = { 150, 30 }, Direction direction = Direction::LeftToRight, Action<RealType> OnValueChange = nullptr);


		Void Update(const EventSystem& eventSystem) override;
		Void Render(IDrawable* interface) override;


		Void SetPosition(const Vector2Int& position);
		Void SetSize(const Vector2Int& size);
		Void SetDirection(Direction direction);
		Void SetGrabRenderSize(RealType renderSize);
	private:
		Void UpdateInternal();
	};
}