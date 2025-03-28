#pragma once

#include "Core/Base.h"
#include "Core/Base64.h"
#include "Core/Delay.h"
#include "Core/Endian.h"
#include "Core/Memory.h"
#include "Core/NonCopyable.h"
#include "Core/PixelFormat.h"

#include "Core/Algorithm/BinarySearch.h"
#include "Core/Algorithm/QuickSort.h"

#include "Core/Allocator/DefaultAllocator.h"

#include "Core/Container/DynamicArray.h"
#include "Core/Container/LinkedList.h"
#include "Core/Container/Span.h"
#include "Core/Container/Stack.h"
#include "Core/Container/StaticArray.h"

#include "Core/Diagnostics/LogSystem.h"
#include "Core/Diagnostics/Timer.h"

#include "Core/Geometry/2D/Rectangle.h"
#include "Core/Geometry/2D/Triangle.h"

#include "Core/Mathematics/Color.h"
#include "Core/Mathematics/Matrix.h"
#include "Core/Mathematics/Matrix3.h"
#include "Core/Mathematics/Matrix4.h"
#include "Core/Mathematics/MatrixBase.h"
#include "Core/Mathematics/MatrixConstants.h"
#include "Core/Mathematics/NumericCalculation.h"
#include "Core/Mathematics/NumericLimit.h"
#include "Core/Mathematics/Vector.h"
#include "Core/Mathematics/VectorBase.h"
#include "Core/Mathematics/VectorConstants.h"

#include "Core/String/Contain.h"
#include "Core/String/ConvertAndParse.h"
#include "Core/String/Find.h"
#include "Core/String/Format.h"
#include "Core/String/Insert.h"
#include "Core/String/ParseLines.h"
#include "Core/String/Remove.h"
#include "Core/String/Replace.h"
#include "Core/String/Split.h"
#include "Core/String/StartEndWith.h"
#include "Core/String/String.h"
#include "Core/String/Substring.h"
#include "Core/String/Trim.h"
#include "Core/String/Unicode.h"

#include "Core/Template/Conditional.h"
#include "Core/Template/EnableIf.h"
#include "Core/Template/EnumClass.h"
#include "Core/Template/EnumUnderlyingType.h"
#include "Core/Template/FunctionPointer.h"
#include "Core/Template/IntegralConstant.h"
#include "Core/Template/IsArithmetic.h"
#include "Core/Template/IsChar.h"
#include "Core/Template/IsConstructible.h"
#include "Core/Template/IsConvertible.h"
#include "Core/Template/IsEnum.h"
#include "Core/Template/IsEnumClass.h"
#include "Core/Template/IsFloatPoint.h"
#include "Core/Template/IsInteger.h"
#include "Core/Template/Nullable.h"
#include "Core/Template/ParameterPackHelper.h"
#include "Core/Template/RemoveAllExtents.h"
#include "Core/Template/RemoveAllPointers.h"
#include "Core/Template/RemoveConst.h"
#include "Core/Template/RemoveExtent.h"
#include "Core/Template/RemovePointer.h"
#include "Core/Template/SameAsAny.h"
#include "Core/Template/SelectNthFromParameterPack.h"
#include "Core/Template/TypesAreSame.h"

