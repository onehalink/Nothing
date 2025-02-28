#pragma once

#include "Vector.h"



namespace Engine
{
	template<typename T> struct Rectangle;

	using RectangleInt	= Rectangle<Int32>;
	using RectangleReal	= Rectangle<RealType>;


	template<typename T>
	struct Rectangle
	{
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
			struct
			{
				T x0, y0;
				T x1, y1;
			};
		};


		Rectangle();
		Rectangle(T left, T bottom, T right, T top);
		Rectangle(const Vector<2, T>& minimum, const Vector<2, T>& maximum);
		Rectangle(const Rectangle<T>& other);
		template<typename U> Rectangle(const Rectangle<U>& other);


		Bool IsValid() const;

		Void SetPosition(const Vector<2, T>& position);
		Void SetSize(const Vector<2, T>& size);
		Void SetPositionAndSize(const Vector<2, T>& position, const Vector<2, T>& size);


		Vector<2, T> Size() const;
		Vector<2, T> Center() const;

		Vector<2, T> LeftTop() const;
		Vector<2, T> RightBottom() const;


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
	Rectangle<T>::Rectangle(T left, T bottom, T right, T top)
		: left(left), bottom(bottom), right(right), top(top)
	{
	
	}

	template<typename T>
	Rectangle<T>::Rectangle(const Vector<2, T>& minimum, const Vector<2, T>& maximum)
		: minimum(minimum), maximum(maximum)
	{
	
	}

	template<typename T>
	Rectangle<T>::Rectangle(const Rectangle<T>& other)
	{
		Memory::Copy( &other, this, sizeof(other) );
	}

	template<typename T>
	template<typename U>
	Rectangle<T>::Rectangle(const Rectangle<U>& other)
		: minimum(minimum), maximum(maximum)
	{

	}

	template<typename T>
	Bool Rectangle<T>::IsValid() const
	{
		return left < right && bottom < top;
	}

	template<typename T>
	Void Rectangle<T>::SetPosition(const Vector<2, T>& position)
	{
		auto size = Size();

		minimum = position;
		maximum = position + size;
	}

	template<typename T>
	Void Rectangle<T>::SetSize(const Vector<2, T>& size)
	{
		maximum = minimum + size;
	}

	template<typename T>
	Void Rectangle<T>::SetPositionAndSize(const Vector<2, T>& position, const Vector<2, T>& size)
	{
		minimum = position;
		maximum = position + size;
	}

	template<typename T>
	Vector<2, T> Rectangle<T>::Size() const
	{
		return maximum - minimum;
	}

	template<typename T>
	Vector<2, T> Rectangle<T>::Center() const
	{
		return minimum + Size() / 2;
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
			IsBetweenOpened( R.left,	L.left, L.right ) ||
			IsBetweenOpened( R.right,	L.left, L.right )
			)
			return
			IsBetweenOpened( R.bottom,	L.bottom, L.top ) ||
			IsBetweenOpened( R.top,		L.bottom, L.top );

		return false;
	}

	template<typename T>
	Bool IsInside(const Rectangle<T>& rectangle, const Vector<2, T>& point)
	{
		return
			IsBetweenOpened( point.x, rectangle.left,	rectangle.right	) &&
			IsBetweenOpened( point.y, rectangle.bottom,	rectangle.top	);
	}

	template<typename T>
	Rectangle<T> Overlap(const Rectangle<T>& L, const Rectangle<T>& R)
	{
		return Rectangle<T>(
			Maximum( L.left,	R.left		),
			Maximum( L.bottom,	R.bottom	),
			Minimum( L.right,	R.right		),
			Minimum( L.top,		R.top		)
		);
	}

#pragma endregion
}