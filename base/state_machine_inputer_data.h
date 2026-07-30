#pragma once

#include "structure.h"

#include <vector>
#include <array>

constexpr size_t DataNum = 2;

struct StateMachineInputerData
{
    std::array<vcu::GearInfo, DataNum> gear_info_;
};