#include "Application.h"

#include <Windows.h>



static Runtime* runtime;
static InputSystem* inputSystem;

static Serface serface;

static UI::Window uiWindow;

Void AppInit(Void* userParameter)
{
    runtime = reinterpret_cast<Runtime*>(userParameter);
    inputSystem = &runtime->inputSystem;

    {
        SizeType lineHeight = 16;
        SizeType contentOffsetX = 16;

        Vector2Int penPosition = Vector2Int::Zero;
        penPosition.y -= uiWindow.titleBarHeight;

        // Tooltip
        {
            auto tip = new UI::Tooltip;
            tip->cursorHeight = GetSystemMetrics(SM_CYCURSOR) * 0.66;
            uiWindow.Add(tip);
        }

        // Text
        {
            //penPosition.y -= lineHeight;
            {
                auto tip = new UI::Text;
                tip->alignment = UI::Alignment::LeftTop;
                tip->SetText(U32String("[Text]"));
                tip->relativePosition = penPosition;

                uiWindow.Add(tip);
            }

            penPosition.y -= lineHeight;
            {
                auto ui = new UI::Text;
                ui->alignment = UI::Alignment::LeftTop;
                ui->SetText(U32String("The Quick Brown Jumps The Lazy Dog"));
                ui->relativePosition = penPosition + Vector2Int::Right * contentOffsetX;

                uiWindow.Add(ui);
            }
        }

        // InputField
        {
            penPosition.y -= lineHeight * 1.5;
            {
                auto tip = new UI::Text;
                tip->alignment = UI::Alignment::LeftTop;
                tip->SetText(U32String("[InputField]"));
                tip->relativePosition = penPosition;

                uiWindow.Add(tip);
            }

            penPosition.y -= lineHeight;
            {
                auto ui = new UI::InputField;
                ui->alignment = UI::Alignment::LeftTop;
                ui->relativePosition = penPosition + Vector2Int::Right * contentOffsetX;
                ui->size = { 150, 30 };

                {
                    penPosition.y -= lineHeight * 2.5;

                    auto text = new UI::Text;
                    text->alignment = UI::Alignment::LeftTop;
                    text->relativePosition = penPosition + Vector2Int::Right * contentOffsetX;
                    
                    text->SetText(U32String("Result(Simple Arithmetic Expression From InputField):"));

                    uiWindow.Add(text);

                    ui->OnType = [text](U32StringView view)
                        {
                            auto result = SimpleArithmeticExpression::Evaluate<Int64>(view.GetBuffer());

                            if (result)
                                text->SetText(U32String(Format<Char8>("Result(Simple Arithmetic Expression From InputField): {}", result.GetValue())));
                            else
                                text->SetText(U32String(Format<Char8>("Error(Simple Arithmetic Expression From InputField): {}", result.GetError())));
                        };
                }

                uiWindow.Add(ui);
            }
        }
    }
}

Void AppResize(SizeType width, SizeType height)
{
    serface = { width, height };

    uiWindow.containerSize = Vector2Int(width, height);
    uiWindow.OnResize();
}

Void AppQuit()
{
    runtime->wantToQuit = true;
}

Void OnUpdate(RealType deltaTime)
{
    uiWindow.Update(*inputSystem, deltaTime);
}

Void OnRender(Void* renderTarget)
{
    serface.Clear();

    {
        uiWindow.Render(&serface);
    }

    serface.CopyTo(renderTarget);
}
