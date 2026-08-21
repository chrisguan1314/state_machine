#pragma once

#include <map>
#include <string>

#include "straight_summon_event_enum.h"

namespace structure
{
    namespace function
    {
        namespace parking
        {

            inline const std::map<StraightSummonActvType, std::string> straight_summon_actv_strmap = {
                {StraightSummonActvType::NONE_0, "NONE[0]"},
                {StraightSummonActvType::BTN_1, "BTN[1]"},
                {StraightSummonActvType::KEY_2, "KEY[2]"},
                {StraightSummonActvType::APP_3, "APP[3]"},
                {StraightSummonActvType::AUTO_4, "AUTO[4]"},
            };
            inline const std::map<StraightSummonActvIhbtType, std::string> straight_summon_actv_ihbt_strmap = {
                {StraightSummonActvIhbtType::NONE_0, "NONE[0]"},
                {StraightSummonActvIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {StraightSummonActvIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<StraightSummonGuidanceType, std::string> straight_summon_guidance_strmap = {
                {StraightSummonGuidanceType::NONE_0, "NONE[0]"},
                {StraightSummonGuidanceType::ACTIVE_1, "ACTIVE[1]"},
            };
            inline const std::map<StraightSummonGuidanceIhbtType, std::string> straight_summon_guidance_ihbt_strmap = {
                {StraightSummonGuidanceIhbtType::NONE_0, "NONE[0]"},
                {StraightSummonGuidanceIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {StraightSummonGuidanceIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<StraightSummonPauseType, std::string> straight_summon_pause_strmap = {
                {StraightSummonPauseType::NONE_0, "NONE[0]"},
                {StraightSummonPauseType::USER_REQ_1, "USER_REQ[1]"},
                {StraightSummonPauseType::SYS_FAULT_2, "SYS_FAULT[2]"},
                {StraightSummonPauseType::VEH_COND_3, "VEH_COND[3]"},
                {StraightSummonPauseType::SENSOR_UNAVAIL_4, "SENSOR_UNAVAIL[4]"},
            };
            inline const std::map<StraightSummonSuccessType, std::string> straight_summon_success_strmap = {
                {StraightSummonSuccessType::NONE_0, "NONE[0]"},
                {StraightSummonSuccessType::DATA_VALID_1, "DATA_VALID[1]"},
                {StraightSummonSuccessType::RESULT_SAVED_2, "RESULT_SAVED[2]"},
            };
            inline const std::map<StraightSummonFailType, std::string> straight_summon_fail_strmap = {
                {StraightSummonFailType::NONE_0, "NONE[0]"},
                {StraightSummonFailType::SYS_FAULT_1, "SYS_FAULT[1]"},
                {StraightSummonFailType::SENSOR_FAIL_2, "SENSOR_FAIL[2]"},
                {StraightSummonFailType::INVALID_DATA_3, "INVALID_DATA[3]"},
                {StraightSummonFailType::STORAGE_FAIL_4, "STORAGE_FAIL[4]"},
                {StraightSummonFailType::USER_CANCEL_5, "USER_CANCEL[5]"},
                {StraightSummonFailType::TIMEOUT_6, "TIMEOUT[6]"},
            };
            inline const std::map<StraightSummonExitType, std::string> straight_summon_exit_strmap = {
                {StraightSummonExitType::NONE_0, "NONE[0]"},
                {StraightSummonExitType::SUCCESS_1, "SUCCESS[1]"},
                {StraightSummonExitType::FAILURE_2, "FAILURE[2]"},
                {StraightSummonExitType::USER_REQ_3, "USER_REQ[3]"},
                {StraightSummonExitType::SYS_FAULT_4, "SYS_FAULT[4]"},
                {StraightSummonExitType::VEH_COND_5, "VEH_COND[5]"},
            };

        } // namespace parking
    } // namespace function
} // namespace structure
