#pragma once

#include "Engine.h"



using namespace Engine;



struct ExecOnceHelper
{
	template<typename Callback>
	ExecOnceHelper(Callback Fn)
	{
		Fn();
	}
};
#define EXEC_ONCE(Fn, ...)	static ExecOnceHelper _ = { Fn };