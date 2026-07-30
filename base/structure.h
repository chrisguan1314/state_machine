#pragma once

#include "enum.h"

namespace ads
{
using namespace gear;
struct GearRqst
{
GearRqstType gear_rqst_{GearRqstType::NONE_0};
GearRqstVldType gear_rqst_vld_{GearRqstVldType::INVALID_0};
GearCtrlEnableType gear_ctrl_enable_{GearCtrlEnableType::DISABLE_0};
};
};

namespace driver
{
using namespace gear;
struct GearShriftlvrInfo
{
GearShriftlvrType gear_shriftlvr_{GearShriftlvrType::CENTER_0};
ParkBrakeStsType park_brake_sts_{ParkBrakeStsType::NOT_PRESSED_0};
};
};

namespace vcu
{
using namespace gear;
struct GearInfo
{
GearPositionType gear_position_{GearPositionType::P_0};
GearVldType gear_vld_{GearVldType::INVALID_0};
GearShriftAvlType gear_shrift_avl_{GearShriftAvlType::NOT_AVAILABLE_0};
DriverGearOverrideType driver_gear_override_{DriverGearOverrideType::NOT_OVERRIDE_0};
};
};
