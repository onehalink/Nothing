#include "TextInput.h"



namespace Engine::UI
{
    TextInput::TextInput()
    {
        InitInternal();
    }

    TextInput::TextInput(const Vector2Int& position, const Vector2Int& size, const Padding& padding)
    {
        InitInternal();

        rectangle = { position, position + size };
        this->padding = padding;
    }

    Void TextInput::Update(const InputSystem& inputSystem)
    {
        if (!active)
            return;

        Bool isHover = rectangle.IsInside(inputSystem.mousePosition);

        if (inputSystem.MouseButtonClicked(MouseButton::Left))
        {
            if (isHover)
                selected = true;
            else
                selected = false;
        }

        if (selected)
        {
            if (inputSystem.KeyClicked(Key::BackSpace))
            {
                auto count = value.GetCount();
                if (count != 0)
                    value = Substring(value, 0, count - 1);
            }

            if (inputSystem.inputChar32WritePosition != 0)
            {
                value += inputSystem.inputChar32s;

                if (OnType)
                    OnType(value);
            }

            currentBorderColor = selectedBorderColor;
        }
        else
            currentBorderColor = normalBorderColor;
    }

    Void TextInput::Render(IDrawable* interface)
    {
        if (!visible)
            return;

        DrawRectangleFilled(interface, rectangle, background);
        DrawRectangle(interface, rectangle, currentBorderColor);

        {
            Vector2Int minimum = rectangle.minimum + Vector2Int(padding.left, padding.bottom);
            Vector2Int maximum = rectangle.maximum - Vector2Int(padding.right, padding.top);
            Private::RenderAlignedText(interface, Alignment::LeftMiddle, { minimum, maximum }, !value ? InputTextPlaceholder : value, textColor);

            if (value)
            {
                Vector2Int caretMinimum = rectangle.minimum + Vector2Int(padding.left, padding.bottom) + Vector2Int::Right * Private::CalcualteTextRenderSize(value).x;
                Vector2Int caretMaximum = { caretMinimum.x, rectangle.maximum.y - padding.top };

                DrawSegment(interface, caretMinimum, caretMaximum, caretColor);
            }
        }
    }

    Void TextInput::InitInternal()
    {
        MemoryClear(this);

        background = Color_TextInputBackground;

        normalBorderColor = Color_Border;
        selectedBorderColor = Color_TextInputBorderSelected;

        textColor = Color_Text;
        caretColor = Color_TextInputCaret;

        active = true;
        visible = true;
    }
}