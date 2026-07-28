#pragma once

#include <stdint.h>
#include <string>
#include <unordered_map>

// 作用域内枚举
enum class AvpCruisingStateType : uint8_t
{
    IDLE_0,
    STANDBY_1,
    LOCATING_2,
    LOCATED_3,
    PREPARED_4,
    CRUISING_5,
    PARKING_6,
    OVERRIDE_7,
    SUSPEND_8,
    TERMINATE_9,
    SUCCESS_10,
    FAILED_11,
};

enum class AvpCruisingRecoverableInterruption : uint8_t
{
    NONE_0,
};

enum class AvpCruisingUnrecoverableInterruption : uint8_t
{
    NONE_0,
};

enum class AvpCruisingPrompt : uint8_t
{
    NONE_0,
    BG_LOCATED_RECOMMEND_1
};

enum class BtnStateType : uint8_t
{
    UNDISPLAY_0,
    GRAY_1,
    HIGHLIGHT_2
};