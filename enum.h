#pragma once

#include <stdint.h>

enum class ApaStateType : uint8_t
{
    IDLE_0,
    STANDBY_1,
    SEARCHING_2,
    SEARCHED_3,
    PREPARED_4,
    RPA_PREPARED_5,
    PARKING_6,
    SUSPEND_7,
    OVERRIDE_8,
    SUCCESS_9,
    FAILED_10,
    TERMINATE_11,
};

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
    SUCCESS_8,
    FAILED_9,
    SUSPEND_10,
    TERMINATE_11
};

enum class AvpMappingStateType : uint8_t
{
    IDLE_0,
    STANDBY_1,
    ONLINE_LEARNING_2,
    OFFLINE_LEARNING_3,
    PARKING_4,
    SUCCESS_5,
    FAILED_6,
    TERMINATE_7,
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