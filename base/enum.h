#pragma once

#include <cstdint>

namespace ads
{
namespace gear
{
enum class GearRqstType : uint8_t
{
    NONE_0,
    P_1,
    R_2,
    N_3,
    D_4
};
enum class GearRqstVldType : uint8_t
{
    INVALID_0,
    VALID_1
};
enum class GearCtrlEnableType : uint8_t
{
    DISABLE_0,
    ENABLE_1    
};
};

namespace eps
{
enum class SteerAglEnbType : uint8_t
{
    DISABLE_0,
    ENABLE_1
};
enum class SteerAglVldType : uint8_t
{
    INVALID_0,
    VALID_1
};
};
};

namespace driver
{
namespace gear
{
enum class GearShriftlvrType : uint8_t
{
    CENTER_0,
    LIGHT_UP_1,
    LIGHT_DOWN_2,
    HEAVY_UP_3,
    HEAVY_DOWN_4,
    INVALID_15 = 15
};
enum class ParkBrakeStsType : uint8_t
{
    NOT_PRESSED_0,
    PRESSED_1,
    FAULT_2,
};
};
};

namespace vcu
{
namespace gear
{
enum class GearPositionType : uint8_t
{
    P_0,
    R_1,
    N_2,
    D_3
};
enum class GearVldType : uint8_t
{
    INVALID_0,
    VALID_1
};
enum class GearShriftAvlType : uint8_t
{
    NOT_AVAILABLE_0,
    AVAILABLE_1
};   
enum class DriverGearOverrideType : uint8_t
{
    NOT_OVERRIDE_0,
    OVERRIDE_1
};
};

namespace eps
{
    enum class AglCtrlAvlType : uint8_t
    {
        NOT_AVAILABLE_0,
        AVAILABLE_1,
        AVAILABLE_DEGRADED_2,
        CRITICAL_DEGRADED_3
    };
    enum class AglCtrlStsType : uint8_t
    {
        NOT_ACTIVE_0,
        ACTIVE_1,
        ACTIVE_WITH_ERROR_2
    };
    enum class EpsRqstErrType : uint8_t
    {
        NO_ERROR_0,
        TORQUE_INVALID_OR_TIMEOUT_1,
        TORQUE_OUT_OF_LIMIT_2,
        ANGLE_INVALID_OR_TIMEOUT_3,
        ANGLE_SPEED_OUT_OF_LIMIT_4,
        ANGLE_OUT_OF_LIMIT_5,
        E2E_ERROR_6,
        OTHER_ERROR_7
    };
};
};
