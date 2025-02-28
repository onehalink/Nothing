#pragma once

#include "VectorBase.h"



namespace Engine::Private
{
	template<Dimension, typename T, typename Self>
	struct MatrixConstants;


	template<typename T, typename Self>
	struct MatrixConstants<2, T, Self>
	{
		static const Self Identity;
	};


	template<typename T, typename Self>
	struct MatrixConstants<3, T, Self>
	{
		static const Self Identity;
	};


	template<typename T, typename Self>
	struct MatrixConstants<4, T, Self>
	{
		static const Self Identity;
	};


	template<typename T, typename Self> const Self MatrixConstants<2, T, Self>::Identity =
	{
		1, 0,
		0, 1,
	};

	template<typename T, typename Self> const Self MatrixConstants<3, T, Self>::Identity =
	{
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
	};

	template<typename T, typename Self> const Self MatrixConstants<4, T, Self>::Identity =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
}