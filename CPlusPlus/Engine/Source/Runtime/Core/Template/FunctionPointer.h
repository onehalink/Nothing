#pragma once

#include "../Base.h"



namespace Engine
{
	// With return value
	template<typename Return, typename ...Parameters>
	using Function = Return(*)(Parameters ...);


	// No return value
	template<typename ...Parameters>
	using Action = Function<Void, Parameters ...>;
}