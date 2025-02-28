#include "ScrollBar.h"



namespace Engine::UI
{
    ScrollBar::ScrollBar()
    {
        InitInternal();
    }

    ScrollBar::ScrollBar(const Vector2Int& position, const Vector2Int& size, Direction direction, Action<RealType> OnValueChange)
    {
        InitInternal();

        this->OnValueChange = OnValueChange;

        rectangle = { position, position + size };

        this->direction = direction;
    }

    Void ScrollBar::Update(const InputSystem& inputSystem)
    {
        if (!active)
            return;

        if (isDirty)
        {
            isDirty = false;

            UpdateInternal();
        }

        if (grab.renderSize > 1 || Approximate(grab.renderSize, 1))
            return;

        Bool isHover = grab.rectangle.IsInside(inputSystem.mousePosition);
        Bool isPress = inputSystem.MouseButtonPressed(MouseButton::Left);

        if (isHover && isPress && !grab.holded)
        {
            grab.holded = true;

            grab.lastPosition = grab.rectangle.minimum;
            grab.beginDrag = inputSystem.mousePosition;

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
                Vector2Int offset = inputSystem.mousePosition - grab.beginDrag;

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

    Void ScrollBar::Render(IDrawable* interface)
    {
        if (!visible)
            return;

        DrawRectangleFilled(interface, rectangle, background);
        DrawRectangle(interface, rectangle, border);

        DrawRectangleFilled(interface, grab.rectangle, grab.currentColor);
        DrawRectangle(interface, grab.rectangle, grab.border);
    }

    Void ScrollBar::InitInternal()
    {
        MemoryClear(this);

        background = Color_ScrollBarBackground;
        border = Color_Border;

        {
            grab.normal = Color_ScrollBarGrabNormal;
            grab.hover = Color_ScrollBarGrabHover;
            grab.highlighted = Color_ScrollBarGrabHighlighted;
            grab.currentColor = grab.normal;

            grab.border = Color_Border;

            grab.renderSize = ScrollBarDefaultGrabRenderSize;
        }

        {
            active = true;
            visible = true;

            isDirty = true;
        }
    }

    Void ScrollBar::UpdateInternal()
    {
        axisIndex = static_cast<EnumUnderlyingType<Axis>>(Private::AxisFromDirection(direction));
        reverseValue =
            direction == Direction::RightToLeft ||
            direction == Direction::TopToBottom;

        RealType total = 1 - grab.renderSize;
        Vector2Int scrollbarSize = rectangle.Size();

        {
            RealType movement = total * value;

            Vector2Int offset = Vector2Int::Zero;
            offset[axisIndex] = scrollbarSize[axisIndex] * (!reverseValue ? movement : total - movement);

            Vector2Int size = scrollbarSize;
            size[axisIndex] *= grab.renderSize;

            grab.rectangle.minimum = rectangle.minimum + offset;
            grab.rectangle.maximum = grab.rectangle.minimum + size;
        }

        {
            grab.moveLimit.minimum = rectangle.minimum;

            grab.moveLimit.maximum = scrollbarSize;
            grab.moveLimit.maximum[axisIndex] *= total;
            grab.moveLimit.maximum += grab.moveLimit.minimum;
        }
    }
}
