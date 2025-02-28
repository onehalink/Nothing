#pragma once

#include "Engine.h"



namespace Engine::Plugin
{
	struct JointPhotographicExpertsGroup
	{
		static Bool IsValid(const Void* buffer, SizeType byteCount);

		static Memory<Byte> Encode(const Texture& texture);
		static Texture Decode(const Void* buffer, SizeType byteCount);
	};
}