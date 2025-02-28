#include "../TestFramework.h"



static U8String GetVector3String(const Vector3& vector)
{
	return Format("{}, {}, {}", vector[0], vector[1], vector[2]);
}

static U8String GetMatrix3String(const Matrix3& matrix)
{
	U8String ret;
	for (SizeType index = 0; index < 3; index++)
		ret += Format("{}, {}, {}\n", matrix[index][0], matrix[index][1], matrix[index][2]);

	return ret;
}

static Void UnitTest_Core_Mathematics_Matrix()
{
	U8String output;
	BUILD_OUTPUT_FILENAME(output);
	File file(output, File::Mode::Write);

	{
		Matrix3 value =
		{
			2, 2, 2,
			2, 2, 2,
			2, 2, 2,
		};

		RealType multiplier = 0.5;

		Matrix3 result = value * multiplier;

		WriteFormatString(file, "Op(Multiply - Scalar)\nInitial:\n{}Multiplier = {}\nResult:\n{}\n", GetMatrix3String(value), multiplier, GetMatrix3String(result));
	}

	{
		Matrix3 M = Translate(Vector2{ 10, 10 });

		Vector3 multiplier = { 1, 1, 0 };

		WriteFormatString(file, "Op(Multiply - Vector)\nInitial:\n{}Multiplier = {}\nResult = {}\n\n", GetMatrix3String(M), GetVector3String(multiplier), GetVector3String(M * multiplier));
	}

	{
		Matrix3 M = Translate(Vector2{ 10, 10 });

		Vector3 multiplier = { 1, 1, 1 };

		WriteFormatString(file, "Op(Multiply - Point)\nInitial:\n{}Multiplier = {}\nResult = {}\n\n", GetMatrix3String(M), GetVector3String(multiplier), GetVector3String(M * multiplier));
	}

	{
		WriteString(file, "---\n\n");

		Matrix3 initial = Rotate(Pi<RealType> *2 / 3);

		Matrix3 I = Inverse(initial);

		Matrix3 T = Transpose(initial);

		WriteFormatString(file, "Initial:\n{}\n", GetMatrix3String(initial));

		WriteFormatString(file, "Op(Inverse):\n{}\n", GetMatrix3String(I));

		WriteFormatString(file, "Op(Transpose):\n{}\n", GetMatrix3String(T));

		WriteFormatString(file, "Result(initial * I):\n{}\n", GetMatrix3String(initial * I));

		WriteFormatString(file, "Result(initial * T):\n{}\n", GetMatrix3String(initial * T));
	}

}


EXEC_ONCE(UnitTest_Core_Mathematics_Matrix);

