#pragma once

#include <map>
#include <string>

#include "avp_mapping_event_enum.h"

namespace structure
{
    namespace function
    {
        namespace parking
        {

            inline const std::map<AvpmActvType, std::string> avpm_actv_strmap = {
                {AvpmActvType::NONE_0, "NONE[0]"},
                {AvpmActvType::BTN_1, "BTN[1]"},
                {AvpmActvType::KEY_2, "KEY[2]"},
                {AvpmActvType::APP_3, "APP[3]"},
                {AvpmActvType::AUTO_4, "AUTO[4]"},
            };
            inline const std::map<AvpmActvIhbtType, std::string> avpm_actv_ihbt_strmap = {
                {AvpmActvIhbtType::NONE_0, "NONE[0]"},
                {AvpmActvIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {AvpmActvIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<AvpmGuidanceType, std::string> avpm_guidance_strmap = {
                {AvpmGuidanceType::NONE_0, "NONE[0]"},
                {AvpmGuidanceType::ACTIVE_1, "ACTIVE[1]"},
            };
            inline const std::map<AvpmGuidanceIhbtType, std::string> avpm_guidance_ihbt_strmap = {
                {AvpmGuidanceIhbtType::NONE_0, "NONE[0]"},
                {AvpmGuidanceIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {AvpmGuidanceIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<AvpmPauseType, std::string> avpm_pause_strmap = {
                {AvpmPauseType::NONE_0, "NONE[0]"},
                {AvpmPauseType::USER_REQ_1, "USER_REQ[1]"},
                {AvpmPauseType::SYS_FAULT_2, "SYS_FAULT[2]"},
                {AvpmPauseType::VEH_COND_3, "VEH_COND[3]"},
                {AvpmPauseType::SENSOR_UNAVAIL_4, "SENSOR_UNAVAIL[4]"},
            };
            inline const std::map<AvpmSuccessType, std::string> avpm_success_strmap = {
                {AvpmSuccessType::NONE_0, "NONE[0]"},
                {AvpmSuccessType::DATA_VALID_1, "DATA_VALID[1]"},
                {AvpmSuccessType::MAP_SAVED_2, "MAP_SAVED[2]"},
            };
            inline const std::map<AvpmFailType, std::string> avpm_fail_strmap = {
                {AvpmFailType::NONE_0, "NONE[0]"},
                {AvpmFailType::SYS_FAULT_1, "SYS_FAULT[1]"},
                {AvpmFailType::SENSOR_FAIL_2, "SENSOR_FAIL[2]"},
                {AvpmFailType::INVALID_DATA_3, "INVALID_DATA[3]"},
                {AvpmFailType::STORAGE_FAIL_4, "STORAGE_FAIL[4]"},
                {AvpmFailType::USER_CANCEL_5, "USER_CANCEL[5]"},
                {AvpmFailType::TIMEOUT_6, "TIMEOUT[6]"},
            };
            inline const std::map<AvpmExitType, std::string> avpm_exit_strmap = {
                {AvpmExitType::NONE_0, "NONE[0]"},
                {AvpmExitType::SUCCESS_1, "SUCCESS[1]"},
                {AvpmExitType::FAILURE_2, "FAILURE[2]"},
                {AvpmExitType::USER_REQ_3, "USER_REQ[3]"},
                {AvpmExitType::SYS_FAULT_4, "SYS_FAULT[4]"},
                {AvpmExitType::VEH_COND_5, "VEH_COND[5]"},
            };

        } // namespace parking
    } // namespace function
} // namespace structure
