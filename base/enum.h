#pragma once

#include <cstdint>

enum class FuncOpenType : uint8_t
{
    NONE_0 = 0U,
    TICE_1 = 1U,
    BTN_2 = 2U,
    VOICE_3 = 3U,
    APP_4 = 4U,
    KEY_5 = 5U,
    PAD_6 = 6U,
    AUTO_7 = 7U,
    MAX = 8U
};

enum class FuncActvType : uint8_t
{
    NONE_0 = 0U,
    TICE_1 = 1U,
    BTN_2 = 2U,
    VOICE_3 = 3U,
    APP_4 = 4U,
    KEY_5 = 5U,
    PAD_6 = 6U,
    AUTO_7 = 7U,
    MAX = 8U
};