#pragma once

#include "Text.h"



namespace Engine::UI
{
	struct ENGINE_API CombineBox
	{
		struct Item
		{
			U32String text;
		};


		Action<Int32> OnValueChange;

		RectangleInt rectangle;

		Color normal;
		Color hover;
		Color current;

		Color border;

		Color textColor;

		Int32 arrowSize;
		Color arrowColor;

		Bool collapsed;
		Int32 value;
		DynamicArray<Item> items;
		Int32 itemHoverIndex;

		Bool active;
		Bool visible;


		CombineBox();
		CombineBox(const Vector2Int& position, const Vector2Int& size, Action<Int32> OnValueChange = nullptr);


		Void Update(const InputSystem& inputSystem);
		Void Render(IDrawable* interface);
	private:
		Void InitInternal();

		RectangleInt CalculateRectangleForItem(SizeType index);
	};
}