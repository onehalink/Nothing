#pragma once

#include "../Type.h"



namespace Engine
{
	template<typename Return, typename ...Parameters>
	using Function	= Return(*)(Parameters ...);

	template<typename ...Parameters>
	using Action	= Function<Void, Parameters ...>;
}
