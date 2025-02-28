#pragma once

#include "Vector.h"



namespace Engine
{
	template<typename T> struct Rectangle;

	using RectangleInt = Rectangle<Int32>;


	template<typename T>
	struct Rectangle
	{
		static_assert( IsArithmetic<T>::Value );


		union
		{
			struct
			{
				T left;
				T bottom;
				T right;
				T top;
			};
			struct
			{
				Vector<2, T> minimum;
				Vector<2, T> maximum;
			};
		};


		Rectangle();
		Rectangle(T left, T bottom, T right, T top);
		Rectangle(const Vector<2, T>& minimum, const Vector<2, T>& maximum);
		template<typename U>
		Rectangle(const Rectangle<U>& other);
		Rectangle(const Rectangle<T>& other);


		Bool Intersect(const Rectangle<T>& other) const;
		template<Bool EdgeIncluded = false>
		Bool IsInside(const Vector<2, T>& point) const;
		Rectangle<T> Overlap(const Rectangle<T>& other) const;


		Void SetPosition(const Vector<2, T>& position);
		Void SetSize(const Vector<2, T>& size);


		Vector<2, T> Size() const;
		Bool IsValid() const;
		Vector<2, T> LeftTop() const;
		Vector<2, T> RightBottom() const;


		Rectangle<T>& operator=(const Rectangle<T>& other);
	};


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
	template<typename U>
	Rectangle<T>::Rectangle(const Rectangle<U>& other)
		: minimum( other.minimum ), maximum( other.maximum )
	{

	}

	template<typename T>
	Rectangle<T>::Rectangle(const Rectangle<T>& other)
	{
		MemoryCopy( &other, this, sizeof(other) );
	}

	template<typename T>
	Bool Rectangle<T>::Intersect(const Rectangle<T>& other) const
	{
		auto Fn = !IsIntegral<T>::Value ? IsBetween<true, true, T, T> : IsBetween<true, false, T, T>;

		return
			( Fn( left,		other.left,		other.right	)	|| Fn( IsIntegral<T>::Value ? right - 1	: right,	other.left,		other.right	) ) &&
			( Fn( bottom,	other.bottom,	other.top	)	|| Fn( IsIntegral<T>::Value ? top - 1	: top,		other.bottom,	other.top	) );
	}

	template<typename T>
	template<Bool EdgeIncluded>
	Bool Rectangle<T>::IsInside(const Vector<2, T>& point) const
	{
		auto Fn = EdgeIncluded ? IsBetween<true, true, T, T> : IsBetween<false, false, T, T>;

		return
			Fn( point.x, left,		IsIntegral<T>::Value ? right - 1	: right	) &&
			Fn( point.y, bottom,	IsIntegral<T>::Value ? top - 1		: top	);
	}

	template<typename T>
	Rectangle<T> Rectangle<T>::Overlap(const Rectangle<T>& other) const
	{
		return Rectangle<T>
		{
			Maximum( left,		other.left		),
			Maximum( bottom,	other.bottom	),
			Minimum( right,		other.right		),
			Minimum( top,		other.top		),
		};
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
	Vector<2, T> Rectangle<T>::Size() const
	{
		return maximum - minimum;
	}

	template<typename T>
	Bool Rectangle<T>::IsValid() const
	{
		return left < right && bottom < top;
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
		MemoryCopy( &other, this, sizeof(other) );

		return *this;
	}

#pragma endregion
}