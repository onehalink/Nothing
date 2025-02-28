#include "Text.h"


#include "../DefaultValue.h"
#include "../_Helper.h"



namespace Engine::UI
{
	Text::Text()
	{
		text.color = Colors::Text;
		text.alignment = Alignment::LeftBottom;

		SetText(LITERAL(Char32, "Text"));
	}

	Void Text::Render(IRenderable* interface)
	{
		text.Render(interface, GetAbsolutePosition(), size);
	}

	Void Text::SetText(U32StringView view)
	{
		text.text = view;
		size = Attachment::Text::CalculateTextRenderSize(text.text) + Vector2Int(text.padding.left + text.padding.right, text.padding.bottom + text.padding.top);
	}
}