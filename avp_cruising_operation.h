#pragma once

#include "structure.h"

#include <stdint.h>
#include <vector>

enum class AvpCruisingOperationType : uint8_t
{
    NONE_0,
    OPEN_1,
    SET_DESTINATION_2,
    ACTIVE_3,
    EXIT_4
};

enum class AvpMapOperationType : uint8_t
{
    NONE_0,
    DELETE_1,
    RENAME_2
};

enum class AvpCruisingDestinationType : uint8_t
{
    UNKOWN_0,
    PARKING_SLOT_1,
    POI_2
};

enum class AvpCruisingPoiType : uint8_t
{
    UNKOWN_0,
    PARKINGLOT_ENTRANCE_1,
    PARKINGLOT_EXIT_2,
    ELEVATOR_3,
    TILOT_4
};

template <typename T>
class AvpCruisingDestination
{
public:
    using DestinationID = uint32_t;
    using PakringSlotVertics = std::array<Point3D<T>, 4>;
    using PakringSlotCenter = Point3D<T>;
private:
    DestinationID id_{0};
    AvpCruisingDestinationType dstn_type_{AvpCruisingDestinationType::UNKOWN_0};
    AvpCruisingPoiType poi_type_{AvpCruisingPoiType::UNKOWN_0};
    PakringSlotVertics vertices_;
    PakringSlotCenter center_;
};

class AvpCruisingOperation
{
private:
    AvpCruisingOperationType operation_{AvpCruisingOperationType::NONE_0};
    AvpCruisingDestination<float> destination_;
};

using MapID = uint64_t;
class AvpMapOperation
{
private:
    AvpMapOperationType type_{AvpMapOperationType::NONE_0};
    std::vector<MapID> map_ips;
};