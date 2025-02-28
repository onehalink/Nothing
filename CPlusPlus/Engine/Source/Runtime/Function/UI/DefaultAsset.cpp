#include "DefaultAsset.h"

#include "DefaultValue.h"



namespace Engine::UI::DefaultAsset
{
	template<typename Function, typename ...Parameter>
	Texture BuildSDFShape(SizeType width, SizeType height, Function Callable, Parameter&&... parameters)
	{
		Texture result(width, height, Texture::PixelFormat::R8);

		for (SizeType y = 0; y < height; y++)
			for (SizeType x = 0; x < width; x++)
			{
				RealType distance = Callable(
					Forward<Parameter>(parameters)...,
					Vector2(
						Remap01(x, 0, width - 1),
						Remap01(y, 0, height - 1)
					)
				);

				Byte value = (-distance + 1) / 2 * 255;

				result.storage[width * y + x] = value;
			}

		return result;
	}


	enum ArrowIndex
	{
		LeftArrow,
		BottomArrow,
		RightArrow,
		TopArrow,

		ArrowCount,
	};


	struct Shapes
	{
		Texture arrows[ArrowCount];
		Texture cross;


		Shapes()
		{
			{
				SizeType width = Values::TitleBarArrowTriangleSideLength;
				SizeType height = width * Sine(Pi<RealType> / 3);

				arrows[LeftArrow] = BuildSDFShape(height, width, SDF::Triangle, Vector2(1, 0), Vector2(1, 1), Vector2(0, 0.5));
				arrows[BottomArrow] = BuildSDFShape(width, height, SDF::Triangle, Vector2(1, 1), Vector2(0, 1), Vector2(0.5, 0));
				arrows[RightArrow] = BuildSDFShape(height, width, SDF::Triangle, Vector2(0, 1), Vector2(0, 0), Vector2(1, 0.5));
				arrows[LeftArrow] = BuildSDFShape(width, height, SDF::Triangle, Vector2(0, 0), Vector2(1, 0), Vector2(0.5, 1));
			}

			{
				SizeType size = Values::TitleBarHeight / 2;
				RealType lineWidth = Values::TitleBarCrossLineWidth;

				cross = BuildSDFShape(size, size, SDF::Cross, lineWidth);
			}
		}
	};


	static Shapes shapes;


	const Texture* GetLeftArrowSDFShape()
	{
		return &shapes.arrows[LeftArrow];
	}

	const Texture* GetBottomArrowSDFShape()
	{
		return &shapes.arrows[BottomArrow];
	}

	const Texture* GetRightArrowSDFShape()
	{
		return &shapes.arrows[RightArrow];
	}

	const Texture* GetTopArrowSDFShape()
	{
		return &shapes.arrows[TopArrow];
	}

	const Texture* GetCrossSDFShape()
	{
		return &shapes.cross;
	}
}