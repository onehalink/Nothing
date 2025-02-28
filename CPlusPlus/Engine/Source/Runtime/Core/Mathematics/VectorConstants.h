#pragma once

#include "VectorBase.h"



namespace Engine::Private
{
	template<Dimension, typename T, typename Self>
	struct VectorConstants;


	template<typename T, typename Self>
	struct VectorConstants<2, T, Self>
	{
		static const Self Zero;
		static const Self One;
		static const Self Left;
		static const Self Right;
		static const Self Bottom;
		static const Self Top;

		static const Self LeftBottom;
		static const Self LeftTop;
		static const Self RightBottom;
		static const Self RightTop;
	};


	template<typename T, typename Self>
	struct VectorConstants<3, T, Self>
	{
		static const Self Zero;
		static const Self One;
		static const Self Left;
		static const Self Right;
		static const Self Down;
		static const Self Up;
		static const Self Back;
		static const Self Forward;
	};


	template<typename T, typename Self>
	struct VectorConstants<4, T, Self>
	{
		static const Self Zero;
		static const Self One;

		static const Self Red;
		static const Self Green;
		static const Self Blue;
		static const Self Yellow;
		static const Self Cyan;
		static const Self Magenta;
		static const Self Black;
		static const Self White;
	};


	template<typename T, typename Self> const Self VectorConstants<2, T, Self>::Zero		= {  0,  0 };
	template<typename T, typename Self> const Self VectorConstants<2, T, Self>::One			= {  1,  1 };
	template<typename T, typename Self> const Self VectorConstants<2, T, Self>::Left		= { -1,  0 };
	template<typename T, typename Self> const Self VectorConstants<2, T, Self>::Right		= {  1,  0 };
	template<typename T, typename Self> const Self VectorConstants<2, T, Self>::Bottom		= {  0, -1 };
	template<typename T, typename Self> const Self VectorConstants<2, T, Self>::Top			= {  0,  1 };

	template<typename T, typename Self> const Self VectorConstants<2, T, Self>::LeftBottom	= { -1, -1 };
	template<typename T, typename Self> const Self VectorConstants<2, T, Self>::LeftTop		= { -1,  1 };
	template<typename T, typename Self> const Self VectorConstants<2, T, Self>::RightBottom	= {  1, -1 };
	template<typename T, typename Self> const Self VectorConstants<2, T, Self>::RightTop	= {  1,  1 };


	template<typename T, typename Self> const Self VectorConstants<3, T, Self>::Zero		= {  0,  0,  0 };
	template<typename T, typename Self> const Self VectorConstants<3, T, Self>::One			= {  1,  1,  1 };
	template<typename T, typename Self> const Self VectorConstants<3, T, Self>::Left		= { -1,  0,  0 };
	template<typename T, typename Self> const Self VectorConstants<3, T, Self>::Right		= {  1,  0,  0 };
	template<typename T, typename Self> const Self VectorConstants<3, T, Self>::Down		= {  0, -1,  0 };
	template<typename T, typename Self> const Self VectorConstants<3, T, Self>::Up			= {  0,  1,  0 };
	template<typename T, typename Self> const Self VectorConstants<3, T, Self>::Back		= {  0,  0, -1 };
	template<typename T, typename Self> const Self VectorConstants<3, T, Self>::Forward		= {  0,  0,  1 };


	template<typename T, typename Self> const Self VectorConstants<4, T, Self>::Zero		= { 0, 0, 0, 0 };
	template<typename T, typename Self> const Self VectorConstants<4, T, Self>::One			= { 1, 1, 1, 1 };

	template<typename T, typename Self> const Self VectorConstants<4, T, Self>::Red			= { 1, 0, 0, 1 };
	template<typename T, typename Self> const Self VectorConstants<4, T, Self>::Green		= { 0, 1, 0, 1 };
	template<typename T, typename Self> const Self VectorConstants<4, T, Self>::Blue		= { 0, 0, 1, 1 };
	template<typename T, typename Self> const Self VectorConstants<4, T, Self>::Yellow		= { 1, 1, 0, 1 };
	template<typename T, typename Self> const Self VectorConstants<4, T, Self>::Cyan		= { 0, 1, 1, 1 };
	template<typename T, typename Self> const Self VectorConstants<4, T, Self>::Magenta		= { 1, 0, 1, 1 };
	template<typename T, typename Self> const Self VectorConstants<4, T, Self>::Black		= { 0, 0, 0, 1 };
	template<typename T, typename Self> const Self VectorConstants<4, T, Self>::White		= { 1, 1, 1, 1 };
}