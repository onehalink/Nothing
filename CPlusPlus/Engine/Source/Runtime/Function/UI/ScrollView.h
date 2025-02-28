#pragma once

#include "../Render/Serface.h"

#include "ScrollBar.h"



namespace Engine::UI
{
	struct ENGINE_API ScrollView
	{
		struct Content
		{
			Vector2Int position;
			Vector2Int origin;
			Alignment alignment;

			Serface serface;
		};


		RectangleInt rectangle;
		Color background;
		Color border;

		RectangleInt viewport;
		Content content;
		Vector2Int contentTargetPosition; // when horizontalScrollBar.value == 1 && verticalScrollBar.value == 1

		ScrollBar horizontalScrollBar;
		ScrollBar verticalScrollBar;
		// The height/width in pixels of horizontal/vertical ScrollBar
		Int32 scrollBarSize;
		VerticalLocation horizontalScrollBarLocation;
		HorizontalLocation verticalScrollBarLocation;

		Bool active;
		Bool visible;

		Bool isDirty;


		ScrollView();
		ScrollView(const Vector2Int& position, const Vector2Int& size, const Vector2Int& contentSize, Alignment contentAlignment = Alignment::RightTop);


		Void Update(const InputSystem& inputSystem);
		Void Render(IDrawable* interface);
	private:
		Void InitInternal();
		Void AdjustViewport();
		Void AdjustScrollBar();
		Void AdjustContent();

		Void UpdateInternal();
	};
}