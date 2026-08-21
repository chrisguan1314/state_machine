#pragma once

#include <map>
#include <string>

#include "rpo_event_enum.h"

namespace structure
{
    namespace function
    {
        namespace parking
        {

            inline const std::map<RpoActvType, std::string> rpo_actv_strmap = {
                {RpoActvType::NONE_0, "NONE[0]"},
                {RpoActvType::BTN_1, "BTN[1]"},
                {RpoActvType::KEY_2, "KEY[2]"},
                {RpoActvType::APP_3, "APP[3]"},
                {RpoActvType::AUTO_4, "AUTO[4]"},
            };
            inline const std::map<RpoActvIhbtType, std::string> rpo_actv_ihbt_strmap = {
                {RpoActvIhbtType::NONE_0, "NONE[0]"},
                {RpoActvIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {RpoActvIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<RpoGuidanceType, std::string> rpo_guidance_strmap = {
                {RpoGuidanceType::NONE_0, "NONE[0]"},
                {RpoGuidanceType::ACTIVE_1, "ACTIVE[1]"},
            };
            inline const std::map<RpoGuidanceIhbtType, std::string> rpo_guidance_ihbt_strmap = {
                {RpoGuidanceIhbtType::NONE_0, "NONE[0]"},
                {RpoGuidanceIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {RpoGuidanceIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<RpoPauseType, std::string> rpo_pause_strmap = {
                {RpoPauseType::NONE_0, "NONE[0]"},
                {RpoPauseType::USER_REQ_1, "USER_REQ[1]"},
                {RpoPauseType::SYS_FAULT_2, "SYS_FAULT[2]"},
                {RpoPauseType::VEH_COND_3, "VEH_COND[3]"},
                {RpoPauseType::SENSOR_UNAVAIL_4, "SENSOR_UNAVAIL[4]"},
            };
            inline const std::map<RpoSuccessType, std::string> rpo_success_strmap = {
                {RpoSuccessType::NONE_0, "NONE[0]"},
                {RpoSuccessType::DATA_VALID_1, "DATA_VALID[1]"},
                {RpoSuccessType::RESULT_SAVED_2, "RESULT_SAVED[2]"},
            };
            inline const std::map<RpoFailType, std::string> rpo_fail_strmap = {
                {RpoFailType::NONE_0, "NONE[0]"},
                {RpoFailType::SYS_FAULT_1, "SYS_FAULT[1]"},
                {RpoFailType::SENSOR_FAIL_2, "SENSOR_FAIL[2]"},
                {RpoFailType::INVALID_DATA_3, "INVALID_DATA[3]"},
                {RpoFailType::STORAGE_FAIL_4, "STORAGE_FAIL[4]"},
                {RpoFailType::USER_CANCEL_5, "USER_CANCEL[5]"},
                {RpoFailType::TIMEOUT_6, "TIMEOUT[6]"},
            };
            inline const std::map<RpoExitType, std::string> rpo_exit_strmap = {
                {RpoExitType::NONE_0, "NONE[0]"},
                {RpoExitType::SUCCESS_1, "SUCCESS[1]"},
                {RpoExitType::FAILURE_2, "FAILURE[2]"},
                {RpoExitType::USER_REQ_3, "USER_REQ[3]"},
                {RpoExitType::SYS_FAULT_4, "SYS_FAULT[4]"},
                {RpoExitType::VEH_COND_5, "VEH_COND[5]"},
            };

        } // namespace parking
    } // namespace function
} // namespace structure
