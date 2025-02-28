#pragma once

#include "../Render/Serface.h"

#include "ScrollBar.h"



namespace Engine::IMUI
{
	struct ENGINE_API ScrollView : IBehaviour
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
		ScrollBar horizontal;
		ScrollBar vertical;
		/**
		* The height of horizontal scrollbar
		* The width of vertical scrollbar
		* 
		* Unit is pixel
		*/
		Int32 scrollBarSize;
		Vector2Int contentAndViewportOffset;

		Bool active;
		Bool visible;


		ScrollView(const Vector2Int& position, const Vector2Int& size, const Vector2Int& contentSize, Alignment contentAlignment = Alignment::LeftTop);


		Void Update(const EventSystem& eventSystem) override;
		Void Render(IDrawable* interface) override;
	public:
		Void SetPosition(const Vector2Int& position);
		Void SetSize(const Vector2Int& size);
		Void SetContentSize(const Vector2Int& contentSize);
		Void SetScrollBarSize(Int32 scrollBarSize);
	private:
		Void UpdateInternal();
	private:
		Bool isDirty;
	};
}