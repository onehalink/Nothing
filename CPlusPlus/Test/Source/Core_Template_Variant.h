#pragma once

#include "APISet.h"



inline Void Test_Core_Template_Variant()
{
	struct A {};
	struct B {};
	struct C {};
	struct D {};
	struct E {};
	struct F {};
	struct G {};


	Variant<A, B, C, D, E, F, G> variant;


	using T0 = typename RemoveReference<decltype(Visit<0>(variant))>::Type;
	using T1 = typename RemoveReference<decltype(Visit<1>(variant))>::Type;
	using T2 = typename RemoveReference<decltype(Visit<2>(variant))>::Type;
	using T3 = typename RemoveReference<decltype(Visit<3>(variant))>::Type;
	using T4 = typename RemoveReference<decltype(Visit<4>(variant))>::Type;
	using T5 = typename RemoveReference<decltype(Visit<5>(variant))>::Type;
	using T6 = typename RemoveReference<decltype(Visit<6>(variant))>::Type;
}