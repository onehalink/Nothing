#pragma once

#include "../Attachment.h"
#include "../Element.h"



namespace Engine::UI
{
	struct ENGINE_API Text : Element
	{
		Attachment::Text text;


		Text();


		virtual Void Render(IRenderable* interface) override;


		Void SetText(U32StringView view);
	};
}