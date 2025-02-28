#include "Element.h"

#include "_Helper.h"



namespace Engine::UI
{
	Element::Element()
	{
		parent = nullptr;
		children = {};
		relativePosition = Vector2Int::Zero;
		size = Vector2Int::Zero;
		alignment = Alignment::LeftBottom;
		paddingRightTop = Vector2Int::Zero;
		isActive = true;
		isVisible = true;
	}

	Element::~Element()
	{
		Clear();
	}

	Void Element::Update(const InputSystem& inputSystem, RealType deltaTime)
	{
		for (auto child : children)
			if(child->isActive)
				child->Update(inputSystem, deltaTime);
	}

	Void Element::Render(IRenderable* interface)
	{
		for (auto child : children)
			if(child->isVisible)
				child->Render(interface);
	}

	Void Element::Add(Element* child)
	{
		child->parent = this;

		children.Add(child);
	}

	Void Element::Clear()
	{
		for (auto child : children)
			delete child;

		children.Clear();
	}

	Vector2Int Element::GetAbsolutePosition() const
	{
		if (!parent)
			return relativePosition;

		return parent->GetAbsolutePosition() + relativePosition + Private::CalculateRectangleAlignment(alignment, parent->size, size, paddingRightTop);
	}
}