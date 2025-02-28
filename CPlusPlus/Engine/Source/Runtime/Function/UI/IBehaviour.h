#pragma once

#include "../../Platform/SAL/InputSystem/InputSystem.h"

#include "../Render/2DGeometry.h"

#include "_Helper.h"
#include "Alignment.h"
#include "Axis.h"
#include "Constants.h"
#include "Direction.h"



namespace Engine::UI
{
	struct IBehaviour
	{
		virtual Void Update(const InputSystem&) = 0;
		virtual Void Render(IDrawable*) = 0;
	};
}