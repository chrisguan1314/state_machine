#pragma once

#include "..\common.h"

#include <array>
#include <stdint.h>

namespace structure
{
namespace perception
{
enum class ParkingSlotGeometryType : uint8_t
{
    UNKNOWN_0,
    PERPENDICULAR_1,
    PARALLEL_2,
    DIAGONAL_3
};
enum class ParkingSlotPhysicalType : uint8_t
{
    UNKNOWN_0,
    COMMON_1,
    SPACE_2,
    MECHANICAL_3
};

template <typename T>
class ParkingSlot
{
public:
    using PakringSlotVertics = std::array<Vertex3D<T>, 4>;
    using PakringSlotCenter = Postion3D<T>;
private:
    Timestamp timestamp_;
    UUID id_{0};
    ParkingSlotGeometryType geometry_type_{ParkingSlotGeometryType::UNKNOWN_0};
    ParkingSlotPhysicalType physical_type_{ParkingSlotPhysicalType::UNKNOWN_0};
    PakringSlotCenter center_;
    PakringSlotVertics vertices_; 
};
};
};

