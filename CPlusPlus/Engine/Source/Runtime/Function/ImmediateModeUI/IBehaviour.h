#pragma once

#include "../../Platform/SoftwareAbstractLayer/EventSystem.h"

#include "../Render/IDrawable.h"



namespace Engine::UI
{
	struct IBehaviour
	{
		virtual Void Update(const EventSystem&) = 0;
		virtual Void Render(IDrawable*) = 0;
	};
}