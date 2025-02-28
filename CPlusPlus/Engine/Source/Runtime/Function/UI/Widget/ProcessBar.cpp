#include "ProcessBar.h"



namespace Engine::UI
{
    ProcessBar::ProcessBar(const Vector2Int& position, const Vector2Int& size, Direction direction)
    {
        rectangle = { position, position + size };

        background = Color_ProcessBarBackground;
        foreground = Color_ProcessBarForeground;
        border = Color_Border;

        active = true;
        visible = true;

        value = 0;
        this->direction = direction;

        displayText = true;
        textColor = Color_Text;
    }

    Void ProcessBar::Update(const InputSystem& inputSystem)
    {
        if (!active)
            return;
    }

    Void ProcessBar::Render(IDrawable* interface)
    {
        if (!visible)
            return;

        Vector2Int minimum;
        Vector2Int maximum;
        {
            Bool reveseValue =
                direction == Direction::RightToLeft ||
                direction == Direction::TopToBottom;
            SizeType axisIndex = static_cast<EnumUnderlyingType<Axis>>(Private::AxisFromDirection(direction));

            value = Clamp01(value);

            if (reveseValue)
            {
                minimum = rectangle.minimum;
                minimum[axisIndex] += rectangle.Size()[axisIndex] * (1 - value);

                maximum = rectangle.maximum;
            }
            else
            {
                minimum = rectangle.minimum;

                maximum = rectangle.maximum;
                maximum[axisIndex] = minimum[axisIndex] + rectangle.Size()[axisIndex] * value;
            }
        }

        DrawRectangleFilled(
            interface,
            rectangle.minimum,
            rectangle.maximum,
            background
        );

        DrawRectangleFilled(
            interface,
            minimum,
            maximum,
            foreground
        );

        DrawRectangle(
            interface,
            rectangle.minimum,
            rectangle.maximum,
            border
        );

        if(displayText)
        {
            U8String text = Format("{}%", static_cast<Int32>(value * 100));
            Vector2Int size = DefaultFontSizeInPixel * Vector2Int(text.GetCount(), 1);

            switch (direction)
            {
            case Direction::LeftToRight:
                alignment = Alignment::RightMiddle;
                break;
            case Direction::RightToLeft:
                alignment = Alignment::LeftMiddle;
                break;
            case Direction::BottomToTop:
                alignment = Alignment::MiddleTop;
                break;
            case Direction::TopToBottom:
                alignment = Alignment::MiddleBottom;
                break;
            }

            Text(interface, Private::CalculateRectangleAlignment(alignment, { minimum, maximum }, size), text, textColor);
        }
    }
}
