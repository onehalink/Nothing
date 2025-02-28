#pragma once

#include "../../Mathematics/Vector.h"

#include "../../Template/Nullable.h"



namespace Engine
{
	template<typename T> struct Rectangle;

	using RectangleInt = Rectangle<Int32>;


	template<typename T>
	struct Rectangle
	{
		static_assert( IsInteger<T>::Value || IsFloatPoint<T>::Value );


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


		Rectangle<T>& operator=(const Rectangle<T>& other);
	};


	template<typename T> Bool Intersect(const Rectangle<T>& L, const Rectangle<T>& R);
	template<typename T> Bool IsInside(const Rectangle<T>& rectangle, const Vector<2, T>& point);
	template<typename T> Nullable<Rectangle<T>> Overlap(const Rectangle<T>& L, const Rectangle<T>& R);


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
	Rectangle<T>& Rectangle<T>::operator=(const Rectangle<T>& other)
	{
		Memory::Copy( &other, this, sizeof(other) );

		return *this;
	}

	template<typename T>
	Bool Intersect(const Rectangle<T>& L, const Rectangle<T>& R)
	{
		if (
			IsBetween( L.left,	R.left, R.right, false, false) ||
			IsBetween( L.right,	R.left, R.right, false, false)
			)
			return
			IsBetween( L.bottom,	R.bottom, R.top, false, false ) ||
			IsBetween( L.top,		R.bottom, R.top, false, false );

		return false;
	}

	template<typename T>
	Bool IsInside(const Rectangle<T>& rectangle, const Vector<2, T>& point)
	{
		if (
			IsBetween( point.x, rectangle.left,		rectangle.right,	false, false ) &&
			IsBetween( point.y, rectangle.bottom,	rectangle.top,		false, false )
			)
			return true;

		return false;
	}

	template<typename T>
	Nullable<Rectangle<T>> Overlap(const Rectangle<T>& L, const Rectangle<T>& R)
	{
		Rectangle<T> rectangle =
		{
			Maximum( L.left,	R.left		),
			Maximum( L.bottom,	R.bottom	),
			Minimum( L.right,	R.right		),
			Minimum( L.top,		R.top		),
		};

		if ( rectangle.left		> rectangle.right &&
			 rectangle.bottom	> rectangle.top )
			return Null();

		return rectangle;
	}

#pragma endregion
}
