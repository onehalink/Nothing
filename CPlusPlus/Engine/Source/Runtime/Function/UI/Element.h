#pragma once

#include "../../Platform/Service/Input/InputSystem.h"

#include "../Interface/IRenderable.h"

#include "../Render/Render.h"

#include "Alignment.h"



namespace Engine::UI
{
	struct ENGINE_API Element
	{
		Element* parent;
		DynamicArray<Element*> children;
		Vector2Int relativePosition;
		Vector2Int size;
		Alignment alignment;
		Vector2Int paddingRightTop;
		Bool isActive;
		Bool isVisible;


		Element();
		virtual ~Element();


		virtual Void Update(const InputSystem& inputSystem, RealType deltaTime);
		virtual Void Render(IRenderable* interface);


		Void Add(Element* child);
		Void Clear();


		Vector2Int GetAbsolutePosition() const;
	};
}