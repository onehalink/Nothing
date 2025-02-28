#include "ProcessBar.h"



namespace Engine::UI
{
	Void ProcessBar(IDrawable* interface, const Vector2Int& position, const Vector2Int& size, RealType processValue, const Color& background, const Color& foreground, const Color& border, Direction direction)
	{
        processValue = Clamp01(processValue);

        RectangleInt rectangle = { position, position + size };

        Vector2Int filledMinimum = rectangle.minimum;
        Vector2Int filledMaximum = rectangle.maximum;
        {
            Bool reverseValue =
                direction == Direction::RightToLeft ||
                direction == Direction::TopToBottom;
            SizeType axisIndex = static_cast<EnumUnderlyingType<Axis>>(Private::AxisFromDirection(direction));

            if (reverseValue)
                filledMinimum[axisIndex] += size[axisIndex] * (1 - processValue);
            else
                filledMaximum[axisIndex] = filledMinimum[axisIndex] + size[axisIndex] * processValue;
        }

        DrawRectangleFilled(interface, rectangle, background);
        DrawRectangleFilled(interface, filledMinimum, filledMaximum, foreground);
        DrawRectangle(interface, rectangle, border);
	}
}
