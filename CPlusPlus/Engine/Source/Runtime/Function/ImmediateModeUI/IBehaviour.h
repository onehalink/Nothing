#pragma once

#include "../../Platform/SAL/EventSystem/EventSystem.h"

#include "../Render/2DGeometry.h"

#include "Alignment.h"
#include "Axis.h"
#include "Constants.h"
#include "Direction.h"
#include "Helper.h"



namespace Engine::IMUI
{
	struct IBehaviour
	{
		virtual Void Update(const EventSystem&) = 0;
		virtual Void Render(IDrawable*) = 0;
	};
}