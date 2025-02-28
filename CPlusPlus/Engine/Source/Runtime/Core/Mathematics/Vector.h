#pragma once

#include "../Memory.h"
#include "../Template.h"

#include "NumericCalculation.h"
#include "VectorConstants.h"



namespace Engine
{
	template<Dimension, typename T> struct Vector;

	using Vector2Int = Vector<2, Int32>;
	using Vector3Int = Vector<3, Int32>;
	using Vector4Int = Vector<4, Int32>;

	using Vector2 = Vector<2, RealType>;
	using Vector3 = Vector<3, RealType>;
	using Vector4 = Vector<4, RealType>;


	template<Dimension D, typename T>
	struct Vector : VectorBase<D, T>, VectorConstants<D, T, Vector<D, T>>
	{
		static_assert( D >= 2 && D <= 4 );


		Vector();
		template<typename ...Parameters> Vector(Parameters... parameters);
		Vector(const Vector<D, T>& other);
		// Constructed from a vector and some scalars(optional)
		template<Dimension E, typename U, typename ...Parameters> Vector(const Vector<E, U>& other, Parameters... parameters);


		Vector<D, T>& operator=(const Vector<D, T>& other);

		T& operator[](SizeType index);
		const T& operator[](SizeType index) const;
	};


	template<Dimension D, typename T> Vector<D, T> Clamp(const Vector<D, T>& vector, const Vector<D, T>& minimum, const Vector<D, T>& maximum);
	template<Dimension D, typename T> typename EnableIf<IsFloatPoint<T>::Value, Vector<D, T>>::Type Lerp(const Vector<D, T>& from, const Vector<D, T>& to, T amount);

	template<Dimension D, typename T> typename EnableIf<D == 2 || D == 3, typename SelectNthFromParameterPack<D - 2, T, Vector<3, T>>::Type>::Type Cross(const Vector<D, T>& L, const Vector<D, T>& R);
	template<Dimension D, typename T> T Dot(const Vector<D, T>& L, const Vector<D, T>& R);
	template<Dimension D, typename T> T Magnitude(const Vector<D, T>& vector);
	template<Dimension D, typename T> Vector<D, T> Normalize(const Vector<D, T>& vector);


	template<Dimension D, typename T> Vector<D, T> operator-(const Vector<D, T>& vector);

	template<Dimension D, typename T> Vector<D, T> operator+(const Vector<D, T>& L, const Vector<D, T>& R);
	template<Dimension D, typename T> Vector<D, T> operator-(const Vector<D, T>& L, const Vector<D, T>& R);
	template<Dimension D, typename T> Vector<D, T> operator*(const Vector<D, T>& L, const Vector<D, T>& R);

	template<Dimension D, typename T> Vector<D, T> operator*(const Vector<D, T>& vector, T scalar);
	template<Dimension D, typename T> Vector<D, T> operator*(T scalar, const Vector<D, T>& vector);
	template<Dimension D, typename T> Vector<D, T> operator/(const Vector<D, T>& vector, T scalar);

	template<Dimension D, typename T> Vector<D, T>& operator+=(Vector<D, T>& L, const Vector<D, T>& R);
	template<Dimension D, typename T> Vector<D, T>& operator-=(Vector<D, T>& L, const Vector<D, T>& R);
	template<Dimension D, typename T> Vector<D, T>& operator*=(Vector<D, T>& L, const Vector<D, T>& R);

	template<Dimension D, typename T> Vector<D, T>& operator*=(Vector<D, T>& vector, T scalar);
	template<Dimension D, typename T> Vector<D, T>& operator/=(Vector<D, T>& vector, T scalar);

	template<Dimension D, typename T> typename EnableIf<IsInteger<T>::Value, Bool>::Type operator==(const Vector<D, T>& L, const Vector<D, T>& R);
	template<Dimension D, typename T> typename EnableIf<IsInteger<T>::Value, Bool>::Type operator!=(const Vector<D, T>& L, const Vector<D, T>& R);


	template<Dimension D, typename T, typename Scalar> typename EnableIf<IsConvertible<Scalar, T>::Value, Vector<D, T>>::Type operator*(const Vector<D, T>& vector, Scalar scalar);
	template<Dimension D, typename T, typename Scalar> typename EnableIf<IsConvertible<Scalar, T>::Value, Vector<D, T>>::Type operator*(Scalar scalar, const Vector<D, T>& vector);
	template<Dimension D, typename T, typename Scalar> typename EnableIf<IsConvertible<Scalar, T>::Value, Vector<D, T>>::Type operator/(const Vector<D, T>& vector, Scalar scalar);

	template<Dimension D, typename T, typename Scalar> typename EnableIf<IsConvertible<Scalar, T>::Value, Vector<D, T>>::Type& operator*=(Vector<D, T>& vector, Scalar scalar);
	template<Dimension D, typename T, typename Scalar> typename EnableIf<IsConvertible<Scalar, T>::Value, Vector<D, T>>::Type& operator/=(Vector<D, T>& vector, Scalar scalar);


#pragma region Details

	template<Dimension D, typename T>
	Vector<D, T>::Vector()
	{

	}

	template<Dimension D, typename T>
	template<typename ...Parameters>
	Vector<D, T>::Vector(Parameters ...parameters)
	{
		static_assert( sizeof...(parameters) <= D );


		ParameterPackHelper::CopyTo( reinterpret_cast<T*>(this), Forward<Parameters>(parameters)... );
	}

	template<Dimension D, typename T>
	Vector<D, T>::Vector(const Vector<D, T>& other)
	{
		Memory::Copy( &other, this, sizeof(T) * D );
	}

	template<Dimension D, typename T>
	template<Dimension E, typename U, typename ...Parameters>
	Vector<D, T>::Vector(const Vector<E, U>& other, Parameters ...parameters)
	{
		static_assert( IsConvertible<U, T>::Value );
		static_assert( sizeof...(parameters) <= Absolute( D - E ) );


		for (SizeType index = 0; index < Minimum(D, E); index++)
			( *this )[index] = static_cast<T>( other[index] );

		if constexpr ( sizeof...(parameters) > 0 )
			ParameterPackHelper::CopyTo( reinterpret_cast<T*>(this) + E, Forward<Parameters>(parameters)... );
	}

	template<Dimension D, typename T>
	Vector<D, T>& Vector<D, T>::operator=(const Vector<D, T>& other)
	{
		Memory::Copy( &other, this, sizeof(T) * D );

		return *this;
	}

	template<Dimension D, typename T>
	T& Vector<D, T>::operator[](SizeType index)
	{
		return reinterpret_cast<T*>(this)[index];
	}

	template<Dimension D, typename T>
	const T& Vector<D, T>::operator[](SizeType index) const
	{
		return reinterpret_cast<const T*>(this)[index];
	}

	template<Dimension D, typename T>
	Vector<D, T> Clamp(const Vector<D, T>& vector, const Vector<D, T>& minimum, const Vector<D, T>& maximum)
	{
		Vector<D, T> ret;
		for (SizeType index = 0; index < D; index++)
			ret[index] = Clamp( vector[index], minimum[index], maximum[index] );

		return ret;
	}

	template<Dimension D, typename T>
	typename EnableIf<IsFloatPoint<T>::Value, Vector<D, T>>::Type Lerp(const Vector<D, T>& from, const Vector<D, T>& to, T amount)
	{
		Vector ret;
		for (SizeType index = 0; index < D; index++)
			ret = Lerp( from[index], to[index], amount );

		return ret;
	}

	template<Dimension D, typename T>
	typename EnableIf<D == 2 || D == 3, typename SelectNthFromParameterPack<D - 2, T, Vector<3, T>>::Type>::Type Cross(const Vector<D, T>& L, const Vector<D, T>& R)
	{
		if constexpr ( D == 2 )
			return L[0] * R[1] - L[1] * R[0]; // x * y - y * x

		if constexpr ( D == 3 )
			return
			Vector<3, T>{
				L[1] * R[2] - L[2] * R[1], // y * z - z * y
				L[2] * R[0] - L[0] * R[2], // z * x - x * z
				L[0] * R[1] - L[1] * R[0], // x * y - y * x
			};
	}

	template<Dimension D, typename T>
	T Dot(const Vector<D, T>& L, const Vector<D, T>& R)
	{
		T ret = T();
		for (SizeType index = 0; index < D; index++)
			ret += L[index] * R[index];

		return ret;
	}

	template<Dimension D, typename T>
	T Magnitude(const Vector<D, T>& vector)
	{
		return SquareRoot( Dot(vector, vector) );
	}

	template<Dimension D, typename T>
	Vector<D, T> Normalize(const Vector<D, T>& vector)
	{
		return vector / Magnitude(vector);
	}

	template<Dimension D, typename T>
	Vector<D, T> operator-(const Vector<D, T>& vector)
	{
		Vector<D, T> ret;
		for (SizeType index = 0; index < D; index++)
			ret[index] = -vector[index];

		return ret;
	}

	template<Dimension D, typename T>
	Vector<D, T> operator+(const Vector<D, T>& L, const Vector<D, T>& R)
	{
		Vector<D, T> ret;
		for (SizeType index = 0; index < D; index++)
			ret[index] = L[index] + R[index];

		return ret;
	}

	template<Dimension D, typename T>
	Vector<D, T> operator-(const Vector<D, T>& L, const Vector<D, T>& R)
	{
		Vector<D, T> ret;
		for (SizeType index = 0; index < D; index++)
			ret[index] = L[index] - R[index];

		return ret;
	}

	template<Dimension D, typename T>
	Vector<D, T> operator*(const Vector<D, T>& L, const Vector<D, T>& R)
	{
		Vector<D, T> ret;
		for (SizeType index = 0; index < D; index++)
			ret[index] = L[index] * R[index];

		return ret;
	}

	template<Dimension D, typename T>
	Vector<D, T> operator*(const Vector<D, T>& vector, T scalar)
	{
		Vector<D, T> ret;
		for (SizeType index = 0; index < D; index++)
			ret[index] = vector[index] * scalar;

		return ret;
	}

	template<Dimension D, typename T>
	Vector<D, T> operator*(T scalar, const Vector<D, T>& vector)
	{
		return vector * scalar;
	}

	template<Dimension D, typename T>
	Vector<D, T> operator/(const Vector<D, T>& vector, T scalar)
	{
		Vector<D, T> ret;
		for (SizeType index = 0; index < D; index++)
			ret[index] = vector[index] / scalar;

		return ret;
	}

	template<Dimension D, typename T>
	Vector<D, T>& operator+=(Vector<D, T>& L, const Vector<D, T>& R)
	{
		return L = L + R;
	}

	template<Dimension D, typename T>
	Vector<D, T>& operator-=(Vector<D, T>& L, const Vector<D, T>& R)
	{
		return L = L - R;
	}

	template<Dimension D, typename T>
	Vector<D, T>& operator*=(Vector<D, T>& L, const Vector<D, T>& R)
	{
		return L = L * R;
	}

	template<Dimension D, typename T>
	Vector<D, T>& operator*=(Vector<D, T>& vector, T scalar)
	{
		return vector = vector * scalar;
	}

	template<Dimension D, typename T>
	Vector<D, T>& operator/=(Vector<D, T>& vector, T scalar)
	{
		return vector = vector / scalar;
	}

	template<Dimension D, typename T>
	typename EnableIf<IsInteger<T>::Value, Bool>::Type operator==(const Vector<D, T>& L, const Vector<D, T>& R)
	{
		Bool ret = true;
		for (SizeType index = 0; index < D; index++)
			ret &= L[index] == R[index];

		return ret;
	}

	template<Dimension D, typename T>
	typename EnableIf<IsInteger<T>::Value, Bool>::Type operator!=(const Vector<D, T>& L, const Vector<D, T>& R)
	{
		return !operator==(L, R);
	}

	template<Dimension D, typename T, typename Scalar>
	typename EnableIf<IsConvertible<Scalar, T>::Value, Vector<D, T>>::Type operator*(const Vector<D, T>& vector, Scalar scalar)
	{
		Vector<D, T> ret;
		for (SizeType index = 0; index < D; index++)
			ret[index] = vector[index] * static_cast<T>(scalar);

		return ret;
	}

	template<Dimension D, typename T, typename Scalar>
	typename EnableIf<IsConvertible<Scalar, T>::Value, Vector<D, T>>::Type operator*(Scalar scalar, const Vector<D, T>& vector)
	{
		return vector * scalar;
	}

	template<Dimension D, typename T, typename Scalar>
	typename EnableIf<IsConvertible<Scalar, T>::Value, Vector<D, T>>::Type operator/(const Vector<D, T>& vector, Scalar scalar)
	{
		Vector<D, T> ret;
		for (SizeType index = 0; index < D; index++)
			ret[index] = vector[index] / static_cast<T>(scalar);

		return ret;
	}

	template<Dimension D, typename T, typename Scalar>
	typename EnableIf<IsConvertible<Scalar, T>::Value, Vector<D, T>>::Type& operator*=(Vector<D, T>& vector, Scalar scalar)
	{
		return vector = vector * scalar;
	}

	template<Dimension D, typename T, typename Scalar>
	typename EnableIf<IsConvertible<Scalar, T>::Value, Vector<D, T>>::Type& operator/=(Vector<D, T>& vector, Scalar scalar)
	{
		return vector = vector / scalar;
	}

#pragma endregion
}