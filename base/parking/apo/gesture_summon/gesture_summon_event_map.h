#pragma once

#include <map>
#include <string>

#include "gesture_summon_event_enum.h"

namespace structure
{
    namespace function
    {
        namespace parking
        {

            inline const std::map<GestureSummonActvType, std::string> gesture_summon_actv_strmap = {
                {GestureSummonActvType::NONE_0, "NONE[0]"},
                {GestureSummonActvType::BTN_1, "BTN[1]"},
                {GestureSummonActvType::KEY_2, "KEY[2]"},
                {GestureSummonActvType::APP_3, "APP[3]"},
                {GestureSummonActvType::AUTO_4, "AUTO[4]"},
            };
            inline const std::map<GestureSummonActvIhbtType, std::string> gesture_summon_actv_ihbt_strmap = {
                {GestureSummonActvIhbtType::NONE_0, "NONE[0]"},
                {GestureSummonActvIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {GestureSummonActvIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<GestureSummonGuidanceType, std::string> gesture_summon_guidance_strmap = {
                {GestureSummonGuidanceType::NONE_0, "NONE[0]"},
                {GestureSummonGuidanceType::ACTIVE_1, "ACTIVE[1]"},
            };
            inline const std::map<GestureSummonGuidanceIhbtType, std::string> gesture_summon_guidance_ihbt_strmap = {
                {GestureSummonGuidanceIhbtType::NONE_0, "NONE[0]"},
                {GestureSummonGuidanceIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {GestureSummonGuidanceIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<GestureSummonPauseType, std::string> gesture_summon_pause_strmap = {
                {GestureSummonPauseType::NONE_0, "NONE[0]"},
                {GestureSummonPauseType::USER_REQ_1, "USER_REQ[1]"},
                {GestureSummonPauseType::SYS_FAULT_2, "SYS_FAULT[2]"},
                {GestureSummonPauseType::VEH_COND_3, "VEH_COND[3]"},
                {GestureSummonPauseType::SENSOR_UNAVAIL_4, "SENSOR_UNAVAIL[4]"},
            };
            inline const std::map<GestureSummonSuccessType, std::string> gesture_summon_success_strmap = {
                {GestureSummonSuccessType::NONE_0, "NONE[0]"},
                {GestureSummonSuccessType::DATA_VALID_1, "DATA_VALID[1]"},
                {GestureSummonSuccessType::RESULT_SAVED_2, "RESULT_SAVED[2]"},
            };
            inline const std::map<GestureSummonFailType, std::string> gesture_summon_fail_strmap = {
                {GestureSummonFailType::NONE_0, "NONE[0]"},
                {GestureSummonFailType::SYS_FAULT_1, "SYS_FAULT[1]"},
                {GestureSummonFailType::SENSOR_FAIL_2, "SENSOR_FAIL[2]"},
                {GestureSummonFailType::INVALID_DATA_3, "INVALID_DATA[3]"},
                {GestureSummonFailType::STORAGE_FAIL_4, "STORAGE_FAIL[4]"},
                {GestureSummonFailType::USER_CANCEL_5, "USER_CANCEL[5]"},
                {GestureSummonFailType::TIMEOUT_6, "TIMEOUT[6]"},
            };
            inline const std::map<GestureSummonExitType, std::string> gesture_summon_exit_strmap = {
                {GestureSummonExitType::NONE_0, "NONE[0]"},
                {GestureSummonExitType::SUCCESS_1, "SUCCESS[1]"},
                {GestureSummonExitType::FAILURE_2, "FAILURE[2]"},
                {GestureSummonExitType::USER_REQ_3, "USER_REQ[3]"},
                {GestureSummonExitType::SYS_FAULT_4, "SYS_FAULT[4]"},
                {GestureSummonExitType::VEH_COND_5, "VEH_COND[5]"},
            };

        } // namespace parking
    } // namespace function
} // namespace structure
