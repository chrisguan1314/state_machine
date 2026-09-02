#pragma once
#include <cstdint>

namespace function
{
    enum class SystemMode : std::uint8_t
    {
        MANUL_0 = 0,
        PILOT_1,
        PARKING_2,
        ACTIVE_SAFETY_3
    };

    enum class SystemSubMode : std::uint8_t
    {
        // Manual sub-modes start from 0
        MANUL_LOW_0 = 0,
        MANUL_HIGH_1,
        // Pilot sub-modes start from 10 to avoid overlap with manual sub-modes
        PILOT_ACC_10 = 10,
        PILOT_LCC_11,
        // Parking sub-modes start from 30 to avoid overlap with other sub-modes
        PARKING_APA_30 = 30,
        PARKING_APO_31,
        PARKING_AVM_32,
        PARKING_AVP_MAPPING_33,
        PARKING_AVP_CRUISING_34 = 34,
        // Active Safety sub-modes start from 50 to avoid overlap with other sub-modes
        AS_AEB_50 = 50,
        AS_AES_51,
        AS_MEB_52,
        AS_BSD_53
    };
}