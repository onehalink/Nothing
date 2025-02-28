#include "InnerWindow.h"

#include "../DefaultAsset.h"
#include "../DefaultValue.h"

#include "../Mask.h"



namespace Engine::UI
{
	Window::Window()
	{
		{
			size = Values::WindowSize;
		}

		collapseButton.OnClick =
			[&]()
			{
				isCollapsed = !isCollapsed;
			};
		closeButton.OnClick = 
			[&]()
			{
				isActive = false;
				isVisible = false;
			};

		bottomArrow.texture = DefaultAsset::GetBottomArrowSDFShape();
		rightArrow.texture = DefaultAsset::GetRightArrowSDFShape();
		cross.texture = DefaultAsset::GetCrossSDFShape();
		titleBarText.text = "Default Window";
		titleBarText.color = Colors::Text;
		titleBarText.padding = {};
		titleBarText.alignment = Alignment::LeftMiddle;

		titleBarHeight = Values::TitleBarHeight;
		titleBarBackground = Colors::TitleBar;
		titleBarBackgroundCollapsed = Colors::TitleBarCollapsed;
		titleBarArrowColor = titleBarText.color;
		titleBarCrossColor = titleBarText.color;

		sizing.testWidth = Values::WindowSizingWidth;
		sizing.edgeColor = Color::Red;

		sizing.minimumSize = { titleBarHeight * 2, titleBarHeight };

		borderColor = Colors::Border;

		isCollapsed = false;
	}

	Void Window::Update(const InputSystem& inputSystem, RealType deltaTime)
	{
		if (!isActive)
			return;

		{
			auto position = GetAbsolutePosition();

			RectangleInt hitBox;
			hitBox.minimum = position + Vector2Int(titleBarHeight, size.y - titleBarHeight);
			hitBox.maximum = hitBox.minimum + Vector2Int(size.x - titleBarHeight * 2, titleBarHeight);

			draggable.Update(inputSystem, this, hitBox);
		}

		if(!isCollapsed)
		{
			sizing.Update(inputSystem, this);

			if (sizing.isHeld)
				OnResize();
		}

		if(!sizing.isHeld)
		{
			auto titleBarRectangle = CalculateTitleBarRectangle(GetAbsolutePosition());
			Vector2Int square = { titleBarHeight, titleBarHeight };

			collapseButton.hitBox = { titleBarRectangle.minimum, titleBarRectangle.minimum + square };
			closeButton.hitBox = { titleBarRectangle.maximum - square, titleBarRectangle.maximum };

			collapseButton.Update(inputSystem);
			closeButton.Update(inputSystem);
		}

		if(!isCollapsed)
			Element::Update(inputSystem, deltaTime);
	}

	Void Window::OnResize()
	{
		draggable.moveLimit =
		{
			Vector2Int(titleBarHeight * 2, titleBarHeight) - size,
			Vector2Int(containerSize.x - titleBarHeight * 2, containerSize.y - size.y)
		};
	}

	RectangleInt Window::CalculateTitleBarRectangle(Vector2Int absolutePosition) const
	{
		Vector2Int titleBarMinimum = { absolutePosition.x, absolutePosition.y + size.y - titleBarHeight };

		return { titleBarMinimum, titleBarMinimum + Vector2Int(size.x, titleBarHeight) };
	}

	Void Window::Render(IRenderable* interface)
	{
		if (!isVisible)
			return;

		auto position = GetAbsolutePosition();
		auto titleBarRectangle = CalculateTitleBarRectangle(position);
		Vector2Int square = { titleBarHeight, titleBarHeight };

		Mask mask(interface, { position, position + size });

		if(!isCollapsed)
			Element::Render(interface);

		Render::SolidRectangle(interface, titleBarRectangle, !isCollapsed ? titleBarBackground : titleBarBackgroundCollapsed);
		if (isCollapsed)
			Render::Rectangle(interface, titleBarRectangle, borderColor);
		else
			Render::Rectangle(interface, position, titleBarRectangle.maximum, borderColor);

		if (!sizing.isHeld)
		{
			if (collapseButton.isHover)
				Render::Rectangle(interface, collapseButton.hitBox, titleBarArrowColor);

			if (closeButton.isHover)
				Render::Rectangle(interface, closeButton.hitBox, titleBarCrossColor);
		}

		auto& arrow = !isCollapsed ? bottomArrow : rightArrow;
		arrow.Render(interface, titleBarRectangle.minimum + (square - Vector2Int(arrow.texture->width, arrow.texture->height)) / 2, titleBarArrowColor);

		cross.Render(interface, titleBarRectangle.maximum - square + (square - Vector2Int(cross.texture->width, cross.texture->height)) / 2, titleBarCrossColor);

		titleBarText.Render(interface, titleBarRectangle.minimum + Vector2Int::Right * square.x, Vector2Int(size.x - square.x * 2, titleBarHeight));

		sizing.Render(interface);
	}
}