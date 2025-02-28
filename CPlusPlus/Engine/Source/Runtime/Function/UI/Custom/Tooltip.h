#pragma once

#include "../Attachment.h"
#include "../Element.h"



namespace Engine::UI
{
	struct ENGINE_API Tooltip : Element
	{
		Attachment::Text text;
		Color background;
		Color border;

		Bool isHover;
		RealType timeElapsed;
		RealType timeThreshold;

		Bool isShow;
		Vector2Int showPosition;
		SizeType cursorHeight;


		Tooltip();


		virtual Void Update(const InputSystem& inputSystem, RealType deltaTime) override;
		virtual Void Render(IRenderable* interface) override;


		Void SetText(U32StringView view);
	};
}