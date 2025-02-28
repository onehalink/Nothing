#pragma once

#include "Vector.h"



namespace Engine::Private
{
	template<SizeType, typename T>
	struct MatrixBase;


	template<typename T>
	struct MatrixBase<2, T>
	{
		T	m00, m01,
			m10, m11;
	};


	template<typename T>
	struct MatrixBase<3, T>
	{
		T	m00, m01, m02,
			m10, m11, m12,
			m20, m21, m22;
	};


	template<typename T>
	struct MatrixBase<4, T>
	{
		T	m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33;
	};


	template<SizeType, typename Self>
	struct MatrixConstants;


	template<typename Self>
	struct MatrixConstants<2, Self>
	{
		static const Self Identity;
	};


	template<typename Self>
	struct MatrixConstants<3, Self>
	{
		static const Self Identity;
	};


	template<typename Self>
	struct MatrixConstants<4, Self>
	{
		static const Self Identity;
	};


	template<typename Self> const Self MatrixConstants<2, Self>::Identity =
	{
		1, 0,
		0, 1,
	};

	template<typename Self> const Self MatrixConstants<3, Self>::Identity =
	{
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
	};

	template<typename Self> const Self MatrixConstants<4, Self>::Identity =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
}


namespace Engine
{
	// Row major matrix, and apply to a vector should use left-multiplication
	template<SizeType N, typename T>
	struct Matrix : Private::MatrixBase<N, T>, Private::MatrixConstants<N, Matrix<N, T>>
	{
		static_assert( IsBetween(N, 2, 4) );
		static_assert( IsFloatPoint<T>::Value );


		Matrix();
		template<typename ...Parameters>
		Matrix(Parameters... parameters);
		Matrix(const Matrix<N, T>& other);
		Matrix<N, T>& operator=(const Matrix<N, T>& other);


		Void SetRow(SizeType index, const Vector<N, T>& vector);
		const Vector<N, T>& GetRow(SizeType index) const;

		Void SetColumn(SizeType index, const Vector<N, T>& vector);
		Vector<N, T> GetColumn(SizeType index) const;


		Vector<N, T>& operator[](SizeType index);
		const Vector<N, T>& operator[](SizeType index) const;


	private:
		// For Visual Studio's natvis file
		#if defined(COMPILER_MSVC) && defined(DEBUG)
		static constexpr SizeType D = N;
		#endif
	};


	template<SizeType N, typename T> T Determinant(const Matrix<N, T>& matrix);
	/**
	* @remark
	* A-1: matrix's inverse
	* |A|: matrix's determinant
	* A* : adjoint matrix
	*
	* A-1 = 1 / |A| * A*
	*/
	template<SizeType N, typename T> Matrix<N, T> Inverse(const Matrix<N, T>& matrix);
	template<SizeType N, typename T> Matrix<N, T> Transpose(const Matrix<N, T>& matrix);


	template<SizeType N, typename T> Matrix<N, T> operator*(const Matrix<N, T>& L, const Matrix<N, T>& R);
	template<SizeType N, typename T> Vector<N, T> operator*(const Matrix<N, T>& matrix, const Vector<N, T>& vector);
	template<SizeType N, typename T, typename U> Matrix<N, T> operator*(U scalar, const Matrix<N, T>& matrix);
	template<SizeType N, typename T, typename U> Matrix<N, T> operator*(const Matrix<N, T>& matrix, U scalar);
	template<SizeType N, typename T, typename U> Matrix<N, T> operator/(const Matrix<N, T>& matrix, U scalar);

	template<SizeType N, typename T> Matrix<N, T>& operator*=(Matrix<N, T>& L, const Matrix<N, T>& R);
	template<SizeType N, typename T, typename U> Matrix<N, T>& operator*=(Matrix<N, T>& matrix, U scalar);
	template<SizeType N, typename T, typename U> Matrix<N, T>& operator/=(Matrix<N, T>& matrix, U scalar);

	template<SizeType N, typename T> Bool operator==(const Matrix<N, T>& L, const Matrix<N, T>& R);
	template<SizeType N, typename T> Bool operator!=(const Matrix<N, T>& L, const Matrix<N, T>& R);


#pragma region Details

	template<SizeType N, typename T>
	Matrix<N, T>::Matrix()
	{

	}

	template<SizeType N, typename T>
	template<typename ...Parameters>
	Matrix<N, T>::Matrix(Parameters ...parameters)
	{
		static_assert( sizeof...(parameters) <= N * N );
		static_assert( And<IsConvertible<Parameters, T> ...>::Value );


		ParameterPack::CopyTo( reinterpret_cast<T*>(this), Forward<Parameters>(parameters)... );
	}

	template<SizeType N, typename T>
	Matrix<N, T>::Matrix(const Matrix<N, T>& other)
	{
		MemoryCopy( this, &other );
	}

	template<SizeType N, typename T>
	Matrix<N, T>& Matrix<N, T>::operator=(const Matrix<N, T>& other)
	{
		MemoryCopy( this, &other );

		return *this;
	}

	template<SizeType N, typename T>
	Void Matrix<N, T>::SetRow(SizeType index, const Vector<N, T>& vector)
	{
		( *this )[index] = vector;
	}

	template<SizeType N, typename T>
	const Vector<N, T>& Matrix<N, T>::GetRow(SizeType index) const
	{
		return ( *this )[index];
	}

	template<SizeType N, typename T>
	Void Matrix<N, T>::SetColumn(SizeType index, const Vector<N, T>& vector)
	{
		for (SizeType iteration = 0; iteration < N; ++iteration)
			( *this )[iteration][index] = vector[iteration];
	}

	template<SizeType N, typename T>
	Vector<N, T> Matrix<N, T>::GetColumn(SizeType index) const
	{
		Vector<N, T> result;
		for (SizeType iteration = 0; iteration < N; ++iteration)
			result[iteration] = ( *this )[iteration][index];

		return result;
	}

	template<SizeType N, typename T>
	Vector<N, T>& Matrix<N, T>::operator[](SizeType index)
	{
		return reinterpret_cast<Vector<N, T>*>(this)[index];
	}

	template<SizeType N, typename T>
	const Vector<N, T>& Matrix<N, T>::operator[](SizeType index) const
	{
		return const_cast<Matrix<N, T>*>(this)->operator[](index);
	}

	template<SizeType N, typename T>
	T Determinant(const Matrix<N, T>& matrix)
	{
		auto& M = matrix;

		if constexpr ( N == 2 )
			// 2 terms(2!)
			return M[0][0] * M[1][1] - M[0][1] * M[1][0];

		if constexpr ( N == 3 )
			// 6 terms(3!)
			return
			M[0][0] * M[1][1] * M[2][2] + M[0][1] * M[1][2] * M[2][0] + M[0][2] * M[1][0] * M[2][1] -
			M[0][2] * M[1][1] * M[2][0] - M[0][1] * M[1][0] * M[2][2] - M[0][0] * M[1][2] * M[2][1];

		if constexpr ( N == 4 )
		{
			Matrix<3, T> M0 =
			{
				M[1][1], M[1][2], M[1][3],
				M[2][1], M[2][2], M[2][3],
				M[3][1], M[3][2], M[3][3],
			};

			Matrix<3, T> M1 =
			{
				M[1][0], M[1][2], M[1][3],
				M[2][0], M[2][2], M[2][3],
				M[3][0], M[3][2], M[3][3],
			};

			Matrix<3, T> M2 =
			{
				M[1][0], M[1][1], M[1][3],
				M[2][0], M[2][1], M[2][3],
				M[3][0], M[3][1], M[3][3],
			};

			Matrix<3, T> M3 =
			{
				M[1][0], M[1][1], M[1][2],
				M[2][0], M[2][1], M[2][2],
				M[3][0], M[3][1], M[3][2],
			};

			auto A0 = Power( -1, ( 1 + 1 ) ) * M[0][0] * Determinant(M0);
			auto A1 = Power( -1, ( 1 + 2 ) ) * M[0][1] * Determinant(M1);
			auto A2 = Power( -1, ( 1 + 3 ) ) * M[0][2] * Determinant(M2);
			auto A3 = Power( -1, ( 1 + 4 ) ) * M[0][3] * Determinant(M3);

			return A0 + A1 + A2 + A3;
		}
	}

	template<SizeType N, typename T>
	Matrix<N, T> Inverse(const Matrix<N, T>& matrix)
	{
		auto& M = matrix;

		if constexpr ( N == 2 )
		{
			auto A00 = Power( -1, ( 1 + 1 ) ) * M[1][1];
			auto A01 = Power( -1, ( 1 + 2 ) ) * M[1][0];
			auto A10 = Power( -1, ( 2 + 1 ) ) * M[0][1];
			auto A11 = Power( -1, ( 2 + 2 ) ) * M[0][0];

			return 1 / Determinant(M) *
				Transpose(
					Matrix<2, T>(
						A00, A01,
						A10, A11
					)
				);
		}

		if constexpr ( N == 3 )
		{
			// row0
			Matrix<2, T> M00 =
			{
				M[1][1], M[1][2],
				M[2][1], M[2][2],
			};

			Matrix<2, T> M01 =
			{
				M[1][0], M[1][2],
				M[2][0], M[2][2],
			};

			Matrix<2, T> M02 =
			{
				M[1][0], M[1][1],
				M[2][0], M[2][1],
			};

			// row1
			Matrix<2, T> M10 =
			{
				M[0][1], M[0][2],
				M[2][1], M[2][2],
			};

			Matrix<2, T> M11 =
			{
				M[0][0], M[0][2],
				M[2][0], M[2][2],
			};

			Matrix<2, T> M12 =
			{
				M[0][0], M[0][1],
				M[2][0], M[2][1],
			};

			// row2
			Matrix<2, T> M20 =
			{
				M[0][1], M[0][2],
				M[1][1], M[1][2],
			};

			Matrix<2, T> M21 =
			{
				M[0][0], M[0][2],
				M[1][0], M[1][2],
			};

			Matrix<2, T> M22 =
			{
				M[0][0], M[0][1],
				M[1][0], M[1][1],
			};

			auto A00 = Power( -1, ( 1 + 1 ) ) * Determinant(M00);
			auto A01 = Power( -1, ( 1 + 2 ) ) * Determinant(M01);
			auto A02 = Power( -1, ( 1 + 3 ) ) * Determinant(M02);
			auto A10 = Power( -1, ( 2 + 1 ) ) * Determinant(M10);
			auto A11 = Power( -1, ( 2 + 2 ) ) * Determinant(M11);
			auto A12 = Power( -1, ( 2 + 3 ) ) * Determinant(M12);
			auto A20 = Power( -1, ( 3 + 1 ) ) * Determinant(M20);
			auto A21 = Power( -1, ( 3 + 2 ) ) * Determinant(M21);
			auto A22 = Power( -1, ( 3 + 3 ) ) * Determinant(M22);

			return 1 / Determinant(M) *
				Transpose(
					Matrix<3, T>(
						A00, A01, A02,
						A10, A11, A12,
						A20, A21, A22
					)
				);
		}

		if constexpr ( N == 4 )
		{
			// row0
			Matrix<3, T> M00 =
			{
				M[1][1], M[1][2], M[1][3],
				M[2][1], M[2][2], M[2][3],
				M[3][1], M[3][2], M[3][3],
			};

			Matrix<3, T> M01 =
			{
				M[1][0], M[1][2], M[1][3],
				M[2][0], M[2][2], M[2][3],
				M[3][0], M[3][2], M[3][3],
			};

			Matrix<3, T> M02 =
			{
				M[1][0], M[1][1], M[1][3],
				M[2][0], M[2][1], M[2][3],
				M[3][0], M[3][1], M[3][3],
			};

			Matrix<3, T> M03 =
			{
				M[1][0], M[1][1], M[1][2],
				M[2][0], M[2][1], M[2][2],
				M[3][0], M[3][1], M[3][2],
			};

			// row1
			Matrix<3, T> M10 =
			{
				M[0][1], M[0][2], M[0][3],
				M[2][1], M[2][2], M[2][3],
				M[3][1], M[3][2], M[3][3],
			};

			Matrix<3, T> M11 =
			{
				M[0][0], M[0][2], M[0][3],
				M[2][0], M[2][2], M[2][3],
				M[3][0], M[3][2], M[3][3],
			};

			Matrix<3, T> M12 =
			{
				M[0][0], M[0][1], M[0][3],
				M[2][0], M[2][1], M[2][3],
				M[3][0], M[3][1], M[3][3],
			};

			Matrix<3, T> M13 =
			{
				M[0][0], M[0][1], M[0][2],
				M[2][0], M[2][1], M[2][2],
				M[3][0], M[3][1], M[3][2],
			};

			// row2
			Matrix<3, T> M20 =
			{
				M[0][1], M[0][2], M[0][3],
				M[1][1], M[1][2], M[1][3],
				M[3][1], M[3][2], M[3][3],
			};

			Matrix<3, T> M21 =
			{
				M[0][0], M[0][2], M[0][3],
				M[1][0], M[1][2], M[1][3],
				M[3][0], M[3][2], M[3][3],
			};

			Matrix<3, T> M22 =
			{
				M[0][0], M[0][1], M[0][3],
				M[1][0], M[1][1], M[1][3],
				M[3][0], M[3][1], M[3][3],
			};

			Matrix<3, T> M23 =
			{
				M[0][0], M[0][1], M[0][2],
				M[1][0], M[1][1], M[1][2],
				M[3][0], M[3][1], M[3][2],
			};

			// row3
			Matrix<3, T> M30 =
			{
				M[0][1], M[0][2], M[0][3],
				M[1][1], M[1][2], M[1][3],
				M[2][1], M[2][2], M[2][3],
			};

			Matrix<3, T> M31 =
			{
				M[0][0], M[0][2], M[0][3],
				M[1][0], M[1][2], M[1][3],
				M[2][0], M[2][2], M[2][3],
			};

			Matrix<3, T> M32 =
			{
				M[0][0], M[0][1], M[0][3],
				M[1][0], M[1][1], M[1][3],
				M[2][0], M[2][1], M[2][3],
			};

			Matrix<3, T> M33 =
			{
				M[0][0], M[0][1], M[0][2],
				M[1][0], M[1][1], M[1][2],
				M[2][0], M[2][1], M[2][2],
			};

			auto A00 = Power( -1, ( 1 + 1 ) ) * Determinant(M00);
			auto A01 = Power( -1, ( 1 + 2 ) ) * Determinant(M01);
			auto A02 = Power( -1, ( 1 + 3 ) ) * Determinant(M02);
			auto A03 = Power( -1, ( 1 + 4 ) ) * Determinant(M03);

			auto A10 = Power( -1, ( 2 + 1 ) ) * Determinant(M10);
			auto A11 = Power( -1, ( 2 + 2 ) ) * Determinant(M11);
			auto A12 = Power( -1, ( 2 + 3 ) ) * Determinant(M12);
			auto A13 = Power( -1, ( 2 + 4 ) ) * Determinant(M13);

			auto A20 = Power( -1, ( 3 + 1 ) ) * Determinant(M20);
			auto A21 = Power( -1, ( 3 + 2 ) ) * Determinant(M21);
			auto A22 = Power( -1, ( 3 + 3 ) ) * Determinant(M22);
			auto A23 = Power( -1, ( 3 + 4 ) ) * Determinant(M23);

			auto A30 = Power( -1, ( 4 + 1 ) ) * Determinant(M30);
			auto A31 = Power( -1, ( 4 + 2 ) ) * Determinant(M31);
			auto A32 = Power( -1, ( 4 + 3 ) ) * Determinant(M32);
			auto A33 = Power( -1, ( 4 + 4 ) ) * Determinant(M33);

			return 1 / Determinant(M) *
				Transpose(
					Matrix<4, T>(
						A00, A01, A02, A03,
						A10, A11, A12, A13,
						A20, A21, A22, A23,
						A30, A31, A32, A33
					)
				);
		}
	}

	template<SizeType N, typename T>
	Matrix<N, T> Transpose(const Matrix<N, T>& matrix)
	{
		Matrix<N, T> result;
		for (SizeType y = 0; y < N; ++y)
			for (SizeType x = 0; x < N; ++x)
				result[x][y] = matrix[y][x];

		return result;
	}

	template<SizeType N, typename T>
	Matrix<N, T> operator*(const Matrix<N, T>& L, const Matrix<N, T>& R)
	{
		Matrix<N, T> result;
		for (SizeType y = 0; y < N; ++y)
		{
			Vector<N, T> column = R.GetColumn(y);
			for (SizeType x = 0; x < N; ++x)
				result[x][y] = Dot( L[x], column );
		}

		return result;
	}

	template<SizeType N, typename T>
	Vector<N, T> operator*(const Matrix<N, T>& matrix, const Vector<N, T>& vector)
	{
		Vector<N, T> result;
		for (SizeType index = 0; index < N; ++index)
			result[index] = Dot( matrix[index], vector );

		return result;
	}

	template<SizeType N, typename T, typename U>
	Matrix<N, T> operator*(U scalar, const Matrix<N, T>& matrix)
	{
		static_assert( IsArithmetic<U>::Value );


		Matrix<N, T> result;
		for (SizeType index = 0; index < N * N; ++index)
			reinterpret_cast<T*>( &result )[index] = scalar * reinterpret_cast<const T*>( &matrix )[index];

		return result;
	}

	template<SizeType N, typename T, typename U>
	Matrix<N, T> operator*(const Matrix<N, T>& matrix, U scalar)
	{
		return scalar * matrix;
	}

	template<SizeType N, typename T, typename U>
	Matrix<N, T> operator/(const Matrix<N, T>& matrix, U scalar)
	{
		static_assert( IsArithmetic<U>::Value );


		Matrix<N, T> result;
		for (SizeType index = 0; index < N * N; ++index)
			reinterpret_cast<T*>( &result )[index] = reinterpret_cast<const T*>( &matrix )[index] / scalar;

		return result;
	}

	template<SizeType N, typename T>
	Matrix<N, T>& operator*=(Matrix<N, T>& L, const Matrix<N, T>& R)
	{
		return L = L * R;
	}

	template<SizeType N, typename T, typename U>
	Matrix<N, T>& operator*=(Matrix<N, T>& matrix, U scalar)
	{
		return matrix = matrix * scalar;
	}

	template<SizeType N, typename T, typename U>
	Matrix<N, T>& operator/=(Matrix<N, T>& matrix, U scalar)
	{
		return matrix = matrix / scalar;
	}

	template<SizeType N, typename T>
	Bool operator==(const Matrix<N, T>& L, const Matrix<N, T>& R)
	{
		Bool result = true;
		for(SizeType index = 0; index < N * N; ++index)
			result &= IsIntegral<T>::Value ? *reinterpret_cast<const T*>( &L ) == *reinterpret_cast<const T*>( &R ) :
			Approximate( *reinterpret_cast<const T*>( &L ), *reinterpret_cast<const T*>( &R ) );

		return result;
	}

	template<SizeType N, typename T>
	Bool operator!=(const Matrix<N, T>& L, const Matrix<N, T>& R)
	{
		return !operator==(L, R);
	}

#pragma endregion
}