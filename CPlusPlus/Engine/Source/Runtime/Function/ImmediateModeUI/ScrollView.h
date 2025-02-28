#pragma once

#include "../../Asset/Texture.h"

#include "ScrollBar.h"



namespace Engine::UI
{
	struct ENGINE_API ScrollView : IBehaviour
	{
		struct Content
		{
			Vector2Int position;
			Vector2Int origin;
			Alignment alignment;

			Texture texture;
		};

		RectangleInt	rectangle;
		Color			background;
		Color			border;

		RectangleInt	viewport;
		Content			content;
		ScrollBar		horizontal;
		ScrollBar		vertical;
		/**
		* The height of horizontal scrollbar
		* The width of vertical scrollbar
		*/
		Int32			scrollBarSize;

		State	state;
		Bool	isDirty;


		ScrollView(const Vector2Int& position, const Vector2Int& size = { 200, 200 });


		Void Update(const EventSystem& eventSystem) override;
		Void Render(IDrawable* interface) override;


		Void SetPosition(const Vector2Int& position);
		Void SetSize(const Vector2Int& size);
		Void SetContentSize(const Vector2Int& contentSize);
		Void SetScrollBarSize(Int32 scrollBarSize);
	private:
		Void UpdateInternal();
	};
}