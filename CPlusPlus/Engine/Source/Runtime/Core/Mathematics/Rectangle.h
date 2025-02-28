#pragma once

#include "Vector.h"



namespace Engine
{
	template<typename T> struct Rectangle;

	using RectangleInt = Rectangle<Int32>;


	template<typename T>
	struct Rectangle
	{
		static_assert( IsIntegral<T>::Value || IsFloatPoint<T>::Value );


		union
		{
			struct
			{
				Vector<2, T> minimum;
				Vector<2, T> maximum;
			};
			struct
			{
				T left;
				T bottom;
				T right;
				T top;
			};
		};


		Rectangle();
		Rectangle(const Vector<2, T>& minimum, const Vector<2, T>& maximum);
		Rectangle(T left, T bottom, T right, T top);
		Rectangle(const Rectangle<T>& other);


		Void SetPosition(const Vector<2, T>& position);
		Void SetSize(const Vector<2, T>& size);

		Vector<2, T> Center() const;
		Vector<2, T> Size() const;

		Vector<2, T> LeftTop() const;
		Vector<2, T> RightBottom() const;

		Bool IsValid() const;


		Rectangle<T>& operator=(const Rectangle<T>& other);
	};


	template<typename T> Bool Intersect(const Rectangle<T>& L, const Rectangle<T>& R);
	template<typename T> Bool IsInside(const Rectangle<T>& rectangle, const Vector<2, T>& point);
	template<typename T> Rectangle<T> Overlap(const Rectangle<T>& L, const Rectangle<T>& R);


#pragma region Details

	template<typename T>
	Rectangle<T>::Rectangle()
	{

	}

	template<typename T>
	Rectangle<T>::Rectangle(const Vector<2, T>& minimum, const Vector<2, T>& maximum)
		: minimum(minimum), maximum(maximum)
	{

	}

	template<typename T>
	Rectangle<T>::Rectangle(T left, T bottom, T right, T top)
		: left(left), bottom(bottom), right(right), top(top)
	{

	}

	template<typename T>
	Rectangle<T>::Rectangle(const Rectangle<T>& other)
		: minimum( other.minimum ), maximum( other.maximum )
	{

	}

	template<typename T>
	Void Rectangle<T>::SetPosition(const Vector<2, T>& position)
	{
		Vector<2, T> size = Size();

		minimum = position;
		maximum = position + size;
	}

	template<typename T>
	Void Rectangle<T>::SetSize(const Vector<2, T>& size)
	{
		maximum = minimum + size;
	}

	template<typename T>
	Vector<2, T> Rectangle<T>::Center() const
	{
		return minimum + Size() / 2;
	}

	template<typename T>
	Vector<2, T> Rectangle<T>::Size() const
	{
		return maximum - minimum;
	}

	template<typename T>
	Vector<2, T> Rectangle<T>::LeftTop() const
	{
		return Vector<2, T>(left, top);
	}

	template<typename T>
	Vector<2, T> Rectangle<T>::RightBottom() const
	{
		return Vector<2, T>(right, bottom);
	}

	template<typename T>
	Bool Rectangle<T>::IsValid() const
	{
		return left < right && bottom < top;
	}

	template<typename T>
	Rectangle<T>& Rectangle<T>::operator=(const Rectangle<T>& other)
	{
		MemoryOp::Copy( &other, this, sizeof(other) );

		return *this;
	}

	template<typename T>
	Bool Intersect(const Rectangle<T>& L, const Rectangle<T>& R)
	{
		if constexpr ( IsIntegral<T>::Value )
		{
			if (
				IsBetween<T, true, false>( L.left,		R.left, R.right ) ||
				IsBetween<T, true, false>( L.right - 1,	R.left, R.right )
				)
				return
				IsBetween<T, true, false>( L.bottom,	R.bottom, R.top ) ||
				IsBetween<T, true, false>( L.top - 1,	R.bottom, R.top );
		}
		else
		{
			if (
				IsBetween( L.left,	R.left, R.right ) ||
				IsBetween( L.right,	R.left, R.right )
				)
				return
				IsBetween( L.bottom,	R.bottom, R.top ) ||
				IsBetween( L.top,		R.bottom, R.top );
		}

		return false;
	}

	template<typename T>
	Bool IsInside(const Rectangle<T>& rectangle, const Vector<2, T>& point)
	{
		if constexpr ( IsIntegral<T>::Value )
		{
			if (
				IsBetween<T, false, false>( point.x, rectangle.left,	rectangle.right	- 1	) &&
				IsBetween<T, false, false>( point.y, rectangle.bottom,	rectangle.top	- 1	)
				)
				return true;
		}
		else
		{
			if (
				IsBetween<T, false, false>( point.x, rectangle.left,	rectangle.right	) &&
				IsBetween<T, false, false>( point.y, rectangle.bottom,	rectangle.top	)
				)
				return true;
		}

		return false;
	}

	template<typename T>
	Rectangle<T> Overlap(const Rectangle<T>& L, const Rectangle<T>& R)
	{
		return Rectangle<T>
		{
			Maximum( L.left,	R.left		),
			Maximum( L.bottom,	R.bottom	),
			Minimum( L.right,	R.right		),
			Minimum( L.top,		R.top		),
		};
	}

#pragma endregion
}
