#pragma once

#include "..\base\point6d.h"
#include "..\base\timestamp.h"

namespace structure
{
using UUID = uint64_t;

template <typename T>
using PathPoint = Point6D<T>;

template <typename T>
using Postion3D = Point3D<T>;

template <typename T>
using Vertex3D = Point3D<T>;
} // namespace structure
