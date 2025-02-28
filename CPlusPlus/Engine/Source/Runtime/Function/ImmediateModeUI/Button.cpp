#include "Button.h"



namespace Engine::UI
{
    Button::Button(const Vector2Int& position, const Vector2Int size, const U8String& text, Action<> OnClick, Action<> OnPress)
    {
        this->OnClick = OnClick;
        this->OnPress = OnPress;

        rectangle   = { position, position + size };
        visual      = { Color_ButtonNormal, Color_ButtonHover, Color_ButtonActive };
        state       = { true, true };
        border      = Color_Border;

        this->text      = text;
        textColor       = Color_Text;
        textAlignment   = Alignment::Center;
    }

    Void Button::Update(const EventSystem& eventSystem)
    {
        if ( !state.active )
            return;

        Bool hover = IsInside( rectangle, eventSystem.mousePosition );
        Bool press = eventSystem.MouseButtonPressed( MouseButton::Left );
        Bool click = eventSystem.MouseButtonClicked( MouseButton::Left );

        if (hover)
        {
            visual.color = visual.hover;

            if (press)
            {
                if (OnPress)
                    OnPress();

                visual.color = visual.active;
            }

            if (click)
            {
                if (OnClick)
                    OnClick();

                visual.color = visual.active;
            }
        }
        else
            visual.color = visual.normal;
    }

    Void Button::Render(IDrawable* interface)
    {
        if ( !state.visible )
            return;

        if ( NoEnoughDisplaySpace(interface->SafeArea(), rectangle) )
            return;

        DrawRectangleFilled(
            interface,
            rectangle.minimum,
            rectangle.maximum,
            visual.color
        );
        DrawRectangle(
            interface,
            rectangle.minimum,
            rectangle.maximum,
            border
        );

        auto textSize = FontSizeInPixel * Vector2Int{ text.GetCount(), 1 };
        Text( interface, CalculateRectangleAlignment(textAlignment, textSize, rectangle), text, textColor );
    }
}
