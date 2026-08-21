#pragma once

#include <map>
#include <string>

#include "apo_event_enum.h"

namespace structure
{
    namespace function
    {
        namespace parking
        {

            inline const std::map<ApoActvType, std::string> apo_actv_strmap = {
                {ApoActvType::NONE_0, "NONE[0]"},
                {ApoActvType::BTN_1, "BTN[1]"},
                {ApoActvType::KEY_2, "KEY[2]"},
                {ApoActvType::APP_3, "APP[3]"},
                {ApoActvType::AUTO_4, "AUTO[4]"},
            };
            inline const std::map<ApoActvIhbtType, std::string> apo_actv_ihbt_strmap = {
                {ApoActvIhbtType::NONE_0, "NONE[0]"},
                {ApoActvIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {ApoActvIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<ApoGuidanceType, std::string> apo_guidance_strmap = {
                {ApoGuidanceType::NONE_0, "NONE[0]"},
                {ApoGuidanceType::ACTIVE_1, "ACTIVE[1]"},
            };
            inline const std::map<ApoGuidanceIhbtType, std::string> apo_guidance_ihbt_strmap = {
                {ApoGuidanceIhbtType::NONE_0, "NONE[0]"},
                {ApoGuidanceIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {ApoGuidanceIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<ApoPauseType, std::string> apo_pause_strmap = {
                {ApoPauseType::NONE_0, "NONE[0]"},
                {ApoPauseType::USER_REQ_1, "USER_REQ[1]"},
                {ApoPauseType::SYS_FAULT_2, "SYS_FAULT[2]"},
                {ApoPauseType::VEH_COND_3, "VEH_COND[3]"},
                {ApoPauseType::SENSOR_UNAVAIL_4, "SENSOR_UNAVAIL[4]"},
            };
            inline const std::map<ApoSuccessType, std::string> apo_success_strmap = {
                {ApoSuccessType::NONE_0, "NONE[0]"},
                {ApoSuccessType::DATA_VALID_1, "DATA_VALID[1]"},
                {ApoSuccessType::RESULT_SAVED_2, "RESULT_SAVED[2]"},
            };
            inline const std::map<ApoFailType, std::string> apo_fail_strmap = {
                {ApoFailType::NONE_0, "NONE[0]"},
                {ApoFailType::SYS_FAULT_1, "SYS_FAULT[1]"},
                {ApoFailType::SENSOR_FAIL_2, "SENSOR_FAIL[2]"},
                {ApoFailType::INVALID_DATA_3, "INVALID_DATA[3]"},
                {ApoFailType::STORAGE_FAIL_4, "STORAGE_FAIL[4]"},
                {ApoFailType::USER_CANCEL_5, "USER_CANCEL[5]"},
                {ApoFailType::TIMEOUT_6, "TIMEOUT[6]"},
            };
            inline const std::map<ApoExitType, std::string> apo_exit_strmap = {
                {ApoExitType::NONE_0, "NONE[0]"},
                {ApoExitType::SUCCESS_1, "SUCCESS[1]"},
                {ApoExitType::FAILURE_2, "FAILURE[2]"},
                {ApoExitType::USER_REQ_3, "USER_REQ[3]"},
                {ApoExitType::SYS_FAULT_4, "SYS_FAULT[4]"},
                {ApoExitType::VEH_COND_5, "VEH_COND[5]"},
            };

        } // namespace parking
    } // namespace function
} // namespace structure
