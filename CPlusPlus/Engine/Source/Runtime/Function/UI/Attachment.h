#pragma once

#include "../../Asset/Texture.h"

#include "../../Platform/Service/Input/InputSystem.h"

#include "../Interface/IRenderable.h"

#include "Alignment.h"
#include "Padding.h"



namespace Engine::UI
{
	struct Element;


	namespace Attachment
	{
		struct ENGINE_API Text
		{
			U32String text;
			Color color;
			Padding padding;
			Alignment alignment;


			Void Render(IRenderable* interface, Vector2Int position, Vector2Int size);
			Void Render(IRenderable* interface, Vector2Int position, Vector2Int size, Vector2Int textRenderSize);
			static Vector2Int CalculateTextRenderSize(U32StringView view);
		};


		struct ENGINE_API Shape
		{
			const Texture* texture; // sdf representation


			Void Render(IRenderable* interface, Vector2Int position, Color color, RealType sharpness = 40);
		};


		struct ENGINE_API Button
		{
			Action<> OnClick;

			RectangleInt hitBox;
			Bool isHover;


			Void Update(const InputSystem& inputSystem);
		};


		struct ENGINE_API Draggable
		{
			Bool isHeld;
			Vector2Int beginDragPosition;
			Vector2Int lastPosition;
			RectangleInt moveLimit;


			Void Update(const InputSystem& inputSystem, Element* attachTo, const RectangleInt& hitBox);
		};


		struct ENGINE_API Sizing
		{
			enum class Edge
			{
				Unknown,

				Left,
				Right,
				Bottom,
				Top,

				LeftBottom,
				LeftTop,
				RightBottom,
				RightTop,
			};


			RectangleInt edgeLeftHitBox;
			RectangleInt edgeRightHitBox;
			RectangleInt edgeBottomHitBox;
			RectangleInt edgeTopHitBox;
			Edge edge;
			Color edgeColor;
			SizeType testWidth;

			Bool isHeld;
			Vector2Int beginDragPosition;
			Vector2Int lastPosition;
			Vector2Int lastSize;

			Vector2Int minimumSize;


			Void Update(const InputSystem& inputSystem, Element* attachTo);
			Void Render(IRenderable* interface);
		};
	}
}