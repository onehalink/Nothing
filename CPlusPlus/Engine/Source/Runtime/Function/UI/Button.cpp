#include "Button.h"



namespace Engine::UI
{
    Button::Button()
    {
        InitInternal();
    }

    Button::Button(const Vector2Int& position, const Vector2Int& size, const U32String& text, Action<> OnClick, Action<> OnPress)
    {
        InitInternal();

        this->OnClick = OnClick;
        this->OnPress = OnPress;

        rectangle = { position, position + size };

        this->text = text;
    }

    Void Button::Update(const InputSystem& inputSystem)
    {
        if ( !active )
            return;

        Bool isHover = rectangle.IsInside( inputSystem.mousePosition );
        Bool isPress = inputSystem.MouseButtonPressed( MouseButton::Left );

        if (isHover)
        {
            if (isPress)
            {
                currentColor = highlighted;

                if (OnPress)
                    OnPress();
            }
            else
                currentColor = hover;
        }
        else
            currentColor = normal;

        if ( isHover && inputSystem.MouseButtonClicked( MouseButton::Left ) )
            if (OnClick)
                OnClick();
    }

    Void Button::Render(IDrawable* interface)
    {
        if ( !visible )
            return;

        DrawRectangleFilled(interface, rectangle, currentColor);
        DrawRectangle(interface, rectangle, border);

        Private::RenderAlignedText(interface, textAlignment, rectangle, text, textColor);
    }

    Void Button::InitInternal()
    {
        MemoryClear(this);

        normal      = Color_ButtonNormal;
        hover       = Color_ButtonHover;
        highlighted = Color_ButtonHighlighted;

        border = Color_Border;

        active  = true;
        visible = true;

        textColor       = Color_Text;
        textAlignment   = Alignment::Center;
    }
}