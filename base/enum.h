#pragma once

#include "../enum.h"

#include <cstdint>
#include <concepts>

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

#if defined(__cplusplus) && __cplusplus >= 202002L
template <typename T>
concept StateEnumType = (std::same_as<T, ApaStateType> || 
                        std::same_as<T, ApoStateType> || 
                        std::same_as<T, AvpCruisingStateType> ||
                        std::same_as<T, AvpMappingStateType>);
#endif