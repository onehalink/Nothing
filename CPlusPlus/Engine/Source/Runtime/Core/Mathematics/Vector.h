#pragma once

#include "../CoreMinimal.h"



namespace Engine::Private
{
	template<SizeType, typename T> struct VectorBase;
	template<typename T> struct VectorBase<2, T> { T x, y; };
	template<typename T> struct VectorBase<3, T> { T x, y, z; };
	template<typename T> struct VectorBase<4, T>
	{
		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};
	};


	template<SizeType, typename Self>
	struct VectorConstants;


	template<typename Self>
	struct VectorConstants<2, Self>
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


	template<typename Self>
	struct VectorConstants<3, Self>
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


	template<typename Self>
	struct VectorConstants<4, Self>
	{
		static const Self Zero;
		static const Self One;

		static const Self Black;
		static const Self White;

		static const Self Red;
		static const Self Green;
		static const Self Blue;
		static const Self Yellow;
		static const Self Cyan;
		static const Self Magenta;
	};


	template<typename Self> const Self VectorConstants<2, Self>::Zero			= {  0,  0 };
	template<typename Self> const Self VectorConstants<2, Self>::One			= {  1,  1 };
	template<typename Self> const Self VectorConstants<2, Self>::Left			= { -1,  0 };
	template<typename Self> const Self VectorConstants<2, Self>::Right			= {  1,  0 };
	template<typename Self> const Self VectorConstants<2, Self>::Bottom			= {  0, -1 };
	template<typename Self> const Self VectorConstants<2, Self>::Top			= {  0,  1 };

	template<typename Self> const Self VectorConstants<2, Self>::LeftBottom		= { -1, -1 };
	template<typename Self> const Self VectorConstants<2, Self>::LeftTop		= { -1,  1 };
	template<typename Self> const Self VectorConstants<2, Self>::RightBottom	= {  1, -1 };
	template<typename Self> const Self VectorConstants<2, Self>::RightTop		= {  1,  1 };


	template<typename Self> const Self VectorConstants<3, Self>::Zero			= {  0,  0,  0 };
	template<typename Self> const Self VectorConstants<3, Self>::One			= {  1,  1,  1 };
	template<typename Self> const Self VectorConstants<3, Self>::Left			= { -1,  0,  0 };
	template<typename Self> const Self VectorConstants<3, Self>::Right			= {  1,  0,  0 };
	template<typename Self> const Self VectorConstants<3, Self>::Down			= {  0, -1,  0 };
	template<typename Self> const Self VectorConstants<3, Self>::Up				= {  0,  1,  0 };
	template<typename Self> const Self VectorConstants<3, Self>::Back			= {  0,  0, -1 };
	template<typename Self> const Self VectorConstants<3, Self>::Forward		= {  0,  0,  1 };


	template<typename Self> const Self VectorConstants<4, Self>::Zero			= { 0, 0, 0, 0 };
	template<typename Self> const Self VectorConstants<4, Self>::One			= { 1, 1, 1, 1 };

	template<typename Self> const Self VectorConstants<4, Self>::Black			= { 0, 0, 0, 1 };
	template<typename Self> const Self VectorConstants<4, Self>::White			= { 1, 1, 1, 1 };

	template<typename Self> const Self VectorConstants<4, Self>::Red			= { 1, 0, 0, 1 };
	template<typename Self> const Self VectorConstants<4, Self>::Green			= { 0, 1, 0, 1 };
	template<typename Self> const Self VectorConstants<4, Self>::Blue			= { 0, 0, 1, 1 };
	template<typename Self> const Self VectorConstants<4, Self>::Yellow			= { 1, 1, 0, 1 };
	template<typename Self> const Self VectorConstants<4, Self>::Cyan			= { 0, 1, 1, 1 };
	template<typename Self> const Self VectorConstants<4, Self>::Magenta		= { 1, 0, 1, 1 };
}


namespace Engine
{
	template<SizeType, typename T> struct Vector;

	using Vector2Int = Vector<2, Int32>;
	using Vector3Int = Vector<3, Int32>;
	using Vector4Int = Vector<4, Int32>;

	using Vector2 = Vector<2, RealType>;
	using Vector3 = Vector<3, RealType>;
	using Vector4 = Vector<4, RealType>;


	template<SizeType N, typename T>
	struct Vector : Private::VectorBase<N, T>, Private::VectorConstants<N, Vector<N, T>>
	{
		static_assert( N >= 2 && N <= 4 && IsArithmetic<T>::Value );


		Vector();
		// Constructed from some scalars
		template<typename ...Parameters>
		Vector(Parameters... parameters);
		// Constructed from a vector and some scalars(optional)
		template<SizeType O, typename U, typename ...Parameters>
		Vector(const Vector<O, U>& other, Parameters... parameters);
		Vector(const Vector<N, T>& other);


		template<SizeType ...Indices>
		typename SelectNthFromParameterPack<sizeof...(Indices) - 1, T, Vector<2, T>, Vector<3, T>, Vector<4, T>>::Type Swizzle() const;


		Vector<N, T>& operator=(const Vector<N, T>& other);

		T& operator[](SizeType index);
		const T& operator[](SizeType index) const;
	};


	template<SizeType N, typename T> Vector<N, T> Clamp(const Vector<N, T>& vector, const Vector<N, T>& minimum, const Vector<N, T>& maximum);
	template<SizeType N, typename T> Vector<N, T> Clamp01(const Vector<N, T>& vector);
	template<SizeType N, typename T, typename U> Vector<N, T> Lerp(const Vector<N, T>& from, const Vector<N, T>& to, U amount);

	template<SizeType N, typename T> typename Conditional<N == 2, T, Vector<3, T>>::Type Cross(const Vector<N, T>& L, const Vector<N, T>& R);
	template<SizeType N, typename T> T Dot(const Vector<N, T>& L, const Vector<N, T>& R);
	template<SizeType N, typename T> T Magnitude(const Vector<N, T>& vector);
	template<SizeType N, typename T> Vector<N, T> Normalize(const Vector<N, T>& vector);


	template<SizeType N, typename T> Vector<N, T> operator-(const Vector<N, T>& vector);

	template<SizeType N, typename T> Vector<N, T> operator+(const Vector<N, T>& L, const Vector<N, T>& R);
	template<SizeType N, typename T> Vector<N, T> operator-(const Vector<N, T>& L, const Vector<N, T>& R);
	template<SizeType N, typename T> Vector<N, T> operator*(const Vector<N, T>& L, const Vector<N, T>& R);
	template<SizeType N, typename T, typename U> Vector<N, T> operator*(const Vector<N, T>& vector, U scalar);
	template<SizeType N, typename T, typename U> Vector<N, T> operator*(U scalar, const Vector<N, T>& vector);
	template<SizeType N, typename T, typename U> Vector<N, T> operator/(const Vector<N, T>& vector, U scalar);

	template<SizeType N, typename T> Vector<N, T>& operator+=(Vector<N, T>& L, const Vector<N, T>& R);
	template<SizeType N, typename T> Vector<N, T>& operator-=(Vector<N, T>& L, const Vector<N, T>& R);
	template<SizeType N, typename T> Vector<N, T>& operator*=(Vector<N, T>& L, const Vector<N, T>& R);
	template<SizeType N, typename T, typename U> Vector<N, T>& operator*=(Vector<N, T>& vector, U scalar);
	template<SizeType N, typename T, typename U> Vector<N, T>& operator/=(Vector<N, T>& vector, U scalar);

	template<SizeType N, typename T> Bool operator==(const Vector<N, T>& L, const Vector<N, T>& R);
	template<SizeType N, typename T> Bool operator!=(const Vector<N, T>& L, const Vector<N, T>& R);


#pragma region Details

	template<SizeType N, typename T>
	Vector<N, T>::Vector()
	{

	}

	template<SizeType N, typename T>
	template<typename ...Parameters>
	Vector<N, T>::Vector(Parameters ...parameters)
	{
		static_assert( sizeof...(parameters) <= N );
		static_assert( And<IsConvertible<Parameters, T> ...>::Value );


		ParameterPackHelper::CopyTo( reinterpret_cast<T*>(this), Forward<Parameters>(parameters)... );
	}

	template<SizeType N, typename T>
	template<SizeType O, typename U, typename ...Parameters>
	Vector<N, T>::Vector(const Vector<O, U>& other, Parameters ...parameters)
	{
		static_assert( And<IsConvertible<Parameters, T> ...>::Value );


		for (SizeType index = 0; index < Minimum(N, O); index++)
			(*this)[index] = other[index];

		if constexpr ( sizeof...(parameters) > 0 )
		{
			static_assert( sizeof...(parameters) <= N - O );


			ParameterPackHelper::CopyTo( reinterpret_cast<T*>(this) + O, Forward<Parameters>(parameters)... );
		}
	}

	template<SizeType N, typename T>
	Vector<N, T>::Vector(const Vector<N, T>& other)
	{
		MemoryCopy( &other, this, sizeof(other) );
	}

	template<SizeType N, typename T>
	template<SizeType ...Indices>
	typename SelectNthFromParameterPack<sizeof...(Indices) - 1, T, Vector<2, T>, Vector<3, T>, Vector<4, T>>::Type Vector<N, T>::Swizzle() const
	{
		static_assert( IsBetween( sizeof...(Indices), 1, 4 ) );
		static_assert( ( ( Indices < N ) && ... ) );


		return { (*this)[Indices]... };
	}

	template<SizeType N, typename T>
	Vector<N, T>& Vector<N, T>::operator=(const Vector<N, T>& other)
	{
		MemoryCopy( &other, this, sizeof(other) );

		return *this;
	}

	template<SizeType N, typename T>
	T& Vector<N, T>::operator[](SizeType index)
	{
		return reinterpret_cast<T*>(this)[index];
	}

	template<SizeType N, typename T>
	const T& Vector<N, T>::operator[](SizeType index) const
	{
		return reinterpret_cast<const T*>(this)[index];
	}

	template<SizeType N, typename T>
	Vector<N, T> Clamp(const Vector<N, T>& vector, const Vector<N, T>& minimum, const Vector<N, T>& maximum)
	{
		Vector<N, T> result;
		for (SizeType index = 0; index < N; index++)
			result[index] = Clamp( vector[index], minimum[index], maximum[index] );

		return result;
	}

	template<SizeType N, typename T>
	Vector<N, T> Clamp01(const Vector<N, T>& vector)
	{
		return Clamp( vector, Vector<N, T>::Zero, Vector<N, T>::One );
	}

	template<SizeType N, typename T, typename U>
	Vector<N, T> Lerp(const Vector<N, T>& from, const Vector<N, T>& to, U amount)
	{
		Vector<N, T> result;
		for (SizeType index = 0; index < N; index++)
			result[index] = Lerp( from[index], to[index], amount );

		return result;
	}

	template<SizeType N, typename T>
	typename Conditional<N == 2, T, Vector<3, T>>::Type Cross(const Vector<N, T>& L, const Vector<N, T>& R)
	{
		static_assert( N == 2 || N == 3 );


		if constexpr ( N == 2 )
			return L[0] * R[1] - L[1] * R[0]; // x * y - y * x

		if constexpr ( N == 3 )
			return Vector<3, T> {
				L[1] * R[2] - L[2] * R[1], // y * z - z * y
				L[2] * R[0] - L[0] * R[2], // z * x - x * z
				L[0] * R[1] - L[1] * R[0], // x * y - y * x
			};
	}

	template<SizeType N, typename T>
	T Dot(const Vector<N, T>& L, const Vector<N, T>& R)
	{
		T result = T();
		for (SizeType index = 0; index < N; index++)
			result += L[index] * R[index];

		return result;
	}

	template<SizeType N, typename T>
	T Magnitude(const Vector<N, T>& vector)
	{
		return SquareRoot( Dot(vector, vector) );
	}

	template<SizeType N, typename T>
	Vector<N, T> Normalize(const Vector<N, T>& vector)
	{
		return vector / Magnitude(vector);
	}

	template<SizeType N, typename T>
	Vector<N, T> operator-(const Vector<N, T>& vector)
	{
		Vector<N, T> result;
		for (SizeType index = 0; index < N; index++)
			result[index] = -vector[index];

		return result;
	}

	template<SizeType N, typename T>
	Vector<N, T> operator+(const Vector<N, T>& L, const Vector<N, T>& R)
	{
		Vector<N, T> result;
		for (SizeType index = 0; index < N; index++)
			result[index] = L[index] + R[index];

		return result;
	}

	template<SizeType N, typename T>
	Vector<N, T> operator-(const Vector<N, T>& L, const Vector<N, T>& R)
	{
		Vector<N, T> result;
		for (SizeType index = 0; index < N; index++)
			result[index] = L[index] - R[index];

		return result;
	}

	template<SizeType N, typename T>
	Vector<N, T> operator*(const Vector<N, T>& L, const Vector<N, T>& R)
	{
		Vector<N, T> result;
		for (SizeType index = 0; index < N; index++)
			result[index] = L[index] * R[index];

		return result;
	}

	template<SizeType N, typename T, typename U>
	Vector<N, T> operator*(const Vector<N, T>& vector, U scalar)
	{
		static_assert( IsArithmetic<U>::Value );


		Vector<N, T> result;
		for (SizeType index = 0; index < N; index++)
			result[index] = vector[index] * scalar;

		return result;
	}

	template<SizeType N, typename T, typename U>
	Vector<N, T> operator*(U scalar, const Vector<N, T>& vector)
	{
		return vector * scalar;
	}

	template<SizeType N, typename T, typename U>
	Vector<N, T> operator/(const Vector<N, T>& vector, U scalar)
	{
		static_assert( IsArithmetic<U>::Value );


		Vector<N, T> result;
		for (SizeType index = 0; index < N; index++)
			result[index] = vector[index] / scalar;

		return result;
	}

	template<SizeType N, typename T>
	Vector<N, T>& operator+=(Vector<N, T>& L, const Vector<N, T>& R)
	{
		return L = L + R;
	}

	template<SizeType N, typename T>
	Vector<N, T>& operator-=(Vector<N, T>& L, const Vector<N, T>& R)
	{
		return L = L - R;
	}

	template<SizeType N, typename T>
	Vector<N, T>& operator*=(Vector<N, T>& L, const Vector<N, T>& R)
	{
		return L = L * R;
	}

	template<SizeType N, typename T, typename U>
	Vector<N, T>& operator*=(Vector<N, T>& vector, U scalar)
	{
		return vector = vector * scalar;
	}

	template<SizeType N, typename T, typename U>
	Vector<N, T>& operator/=(Vector<N, T>& vector, U scalar)
	{
		return vector = vector / scalar;
	}

	template<SizeType N, typename T>
	Bool operator==(const Vector<N, T>& L, const Vector<N, T>& R)
	{
		Bool result = true;
		for (SizeType index = 0; index < N; index++)
			result &= IsIntegral<T>::Value ?
				L[index] == R[index] :
				Approximate( L[index], R[index] );

		return result;
	}

	template<SizeType N, typename T>
	Bool operator!=(const Vector<N, T>& L, const Vector<N, T>& R)
	{
		return !operator==(L, R);
	}

#pragma endregion
}