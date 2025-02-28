#include "ScrollBar.h"



namespace Engine::IMUI
{
    ScrollBar::ScrollBar()
    {

    }

    ScrollBar::ScrollBar(const Vector2Int& position, const Vector2Int& size, Direction direction, Action<RealType> OnValueChange)
    {
        this->OnValueChange = OnValueChange;

        rectangle = { position, position + size };
        background = Color_ScrollBarBackground;
        border = Color_Border;

        active = true;
        visible = true;

        this->direction = direction;
        value = 0;
        lastValue = value;

        {
            grab.normal = Color_ScrollBarGrabNormal;
            grab.hover = Color_ScrollBarGrabHover;
            grab.highlighted = Color_ScrollBarGrabHighlighted;
            grab.currentColor = grab.normal;

            grab.border = Color_Border;

            grab.holded = false;

            grab.renderSize = ScrollBarDefaultGrabRenderSize;
        }

        {
            isDirty = true;
        }
    }

    Void ScrollBar::Update(const EventSystem& eventSystem)
    {
        if (!active)
            return;

        if (isDirty)
        {
            isDirty = false;

            UpdateInternal();
        }

        Bool isHover = IsInside(grab.rectangle, eventSystem.mousePosition);
        Bool isPress = eventSystem.MouseButtonPressed(MouseButton::Left);

        if (isHover && isPress && !grab.holded)
        {
            grab.holded = true;

            grab.lastPosition = grab.rectangle.minimum;
            grab.beginDrag = eventSystem.mousePosition;

            lastValue = value;
        }

        if (isHover)
            grab.currentColor = grab.hover;
        else
            grab.currentColor = grab.normal;

        if (isPress && grab.holded)
        {
            grab.currentColor = grab.highlighted;

            {
                Vector2Int offset = eventSystem.mousePosition - grab.beginDrag;

                Vector2Int position = grab.lastPosition;
                position[axisIndex] += offset[axisIndex];

                grab.rectangle.SetPosition(Clamp(position, grab.moveLimit.minimum, grab.moveLimit.maximum));
            }

            {
                Int32 distance = grab.rectangle.minimum[axisIndex] - rectangle.minimum[axisIndex];

                RealType temporary = distance / (rectangle.Size()[axisIndex] * (1 - grab.renderSize));
                value = !reverseValue ? temporary : 1 - temporary;
            }
        }
        else
        {
            if (grab.holded)
            {
                grab.holded = false;

                if (!Approximate(value, lastValue))
                {
                    if (OnValueChange)
                        OnValueChange(value);
                }
            }
        }
    }

    Void ScrollBar::SetPosition(const Vector2Int& position)
    {
        isDirty = true;

        rectangle.SetPosition(position);
    }

    Void ScrollBar::SetSize(const Vector2Int& size)
    {
        isDirty = true;

        rectangle.SetSize(size);
    }

    Void ScrollBar::SetDirection(Direction direction)
    {
        isDirty = true;

        this->direction = direction;
    }

    Void ScrollBar::SetGrabRenderSize(RealType renderSize)
    {
        isDirty = true;

        grab.renderSize = renderSize;
    }

    Void ScrollBar::Render(IDrawable* interface)
    {
        if (!visible)
            return;

        DrawRectangleFilled(
            interface,
            rectangle.minimum + Vector2Int::One,
            rectangle.maximum - Vector2Int::One,
            background
        );
        DrawRectangle(
            interface,
            rectangle.minimum,
            rectangle.maximum,
            border
        );

        DrawRectangleFilled(
            interface,
            grab.rectangle.minimum + Vector2Int::One,
            grab.rectangle.maximum - Vector2Int::One,
            grab.currentColor
        );
        DrawRectangle(
            interface,
            grab.rectangle.minimum,
            grab.rectangle.maximum,
            grab.border
        );
    }

    Void ScrollBar::UpdateInternal()
    {
        axisIndex = static_cast<EnumUnderlyingType<Axis>>(Private::AxisFromDirection(direction));
        reverseValue =
            direction == Direction::RightToLeft ||
            direction == Direction::TopToBottom;

        RealType total = 1 - grab.renderSize;
        Vector2Int scrollbarSize = rectangle.Size();

        Vector2Int grabPosition;
        {
            RealType movement = total * value;

            grabPosition = rectangle.minimum;
            if (reverseValue)
                grabPosition[axisIndex] += scrollbarSize[axisIndex] * (total - movement);
            else
                grabPosition[axisIndex] += scrollbarSize[axisIndex] * movement;
        }

        Vector2Int grabSize;
        {
            grabSize = scrollbarSize;

            grabSize[axisIndex] *= grab.renderSize;
        }

        grab.rectangle = { grabPosition, grabPosition + grabSize };

        {
            grab.moveLimit.minimum = rectangle.minimum;

            grab.moveLimit.maximum = scrollbarSize;
            grab.moveLimit.maximum[axisIndex] *= total;
            grab.moveLimit.maximum += grab.moveLimit.minimum;
        }
    }
}
