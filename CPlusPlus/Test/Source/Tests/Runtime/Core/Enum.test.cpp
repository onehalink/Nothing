#pragma once

#include "../../TestFramework.h"



enum EnumType
{
	A = 1,
	B = 2,
	C = 4,

	AB = A | B,
	BC = B | C,
	AC = A | C,

	All = A | B | C,
};


static Void Run()
{
	static_assert(Enum::And(EnumType::All, EnumType::A, EnumType::B, EnumType::C) == EnumType());
	static_assert(Enum::Or(EnumType::A, EnumType::B, EnumType::C) == EnumType::All);
	static_assert(Enum::XOr(EnumType::A, EnumType::B) == Enum::Or(EnumType::A, EnumType::B));
	static_assert(
		Enum::HasAll(
			Enum::And(Enum::Complement(EnumType::A), EnumType::All),
			EnumType::B,
			EnumType::C
		));

	EnumType enumValue0 = EnumType();
	Enum::Add(enumValue0, EnumType::A, EnumType::C);
	ASSERT(Enum::HasAll(enumValue0, EnumType::A, EnumType::C));
	ASSERT(!Enum::HasAny(enumValue0, EnumType::B));
	ASSERT(Enum::HasAll(enumValue0, EnumType::C));

	EnumType enumValue1 = EnumType::All;
	Enum::Remove(enumValue1, EnumType::A, EnumType::B, EnumType::C);
	ASSERT(enumValue1 == EnumType());

	//ASSERT(false);
}


EXEC_ONCE(Run);