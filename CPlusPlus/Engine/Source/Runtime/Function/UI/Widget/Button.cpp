#include "Button.h"



namespace Engine::UI
{
    Button::Button(const Vector2Int& position, const Vector2Int& size, const U8String& text, Action<> OnClick, Action<> OnPress)
    {
        this->OnClick = OnClick;
        this->OnPress = OnPress;

        rectangle = { position, position + size };

        normal = Color_ButtonNormal;
        hover = Color_ButtonHover;
        highlighted = Color_ButtonHighlighted;
        currentColor = normal;

        border = Color_Border;

        active = true;
        visible = true;

        this->text = text;
        textColor = Color_Text;
        alignment = Alignment::Center;
    }

    Void Button::Update(const InputSystem& inputSystem)
    {
        if (!active)
            return;

        Bool isHover = IsInside(rectangle, inputSystem.mouse.position);
        Bool isPress = inputSystem.mouse.ButtonPressed(Mouse::Button::Left);

        if (isHover)
        {
            currentColor = hover;

            if (isPress)
            {
                currentColor = highlighted;

                if (OnPress)
                    OnPress();
            }
        }
        else
        {
            currentColor = normal;
        }

        if (isHover && inputSystem.mouse.ButtonClicked(Mouse::Button::Left))
        {
            if (OnClick)
                OnClick();
        }
    }

    Void Button::Render(IDrawable* interface)
    {
        if (!visible)
            return;

        DrawRectangleFilled(
            interface,
            rectangle.minimum + Vector2Int::One,
            rectangle.maximum - Vector2Int::One,
            currentColor
        );
        DrawRectangle(interface, rectangle.minimum, rectangle.maximum, border);

        Vector2Int size = DefaultFontSizeInPixel * Vector2Int(text.GetCount(), 1);
        Text(interface, Private::CalculateRectangleAlignment(alignment, rectangle, size), text, textColor);
    }
}