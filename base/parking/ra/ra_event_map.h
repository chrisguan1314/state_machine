#pragma once

#include <map>
#include <string>

#include "ra_event_enum.h"

namespace structure
{
    namespace function
    {
        namespace parking
        {

            inline const std::map<RaActvType, std::string> ra_actv_strmap = {
                {RaActvType::NONE_0, "NONE[0]"},
                {RaActvType::BTN_1, "BTN[1]"},
                {RaActvType::KEY_2, "KEY[2]"},
                {RaActvType::APP_3, "APP[3]"},
                {RaActvType::AUTO_4, "AUTO[4]"},
            };
            inline const std::map<RaActvIhbtType, std::string> ra_actv_ihbt_strmap = {
                {RaActvIhbtType::NONE_0, "NONE[0]"},
                {RaActvIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {RaActvIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<RaGuidanceType, std::string> ra_guidance_strmap = {
                {RaGuidanceType::NONE_0, "NONE[0]"},
                {RaGuidanceType::ACTIVE_1, "ACTIVE[1]"},
            };
            inline const std::map<RaGuidanceIhbtType, std::string> ra_guidance_ihbt_strmap = {
                {RaGuidanceIhbtType::NONE_0, "NONE[0]"},
                {RaGuidanceIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {RaGuidanceIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<RaPauseType, std::string> ra_pause_strmap = {
                {RaPauseType::NONE_0, "NONE[0]"},
                {RaPauseType::USER_REQ_1, "USER_REQ[1]"},
                {RaPauseType::SYS_FAULT_2, "SYS_FAULT[2]"},
                {RaPauseType::VEH_COND_3, "VEH_COND[3]"},
                {RaPauseType::SENSOR_UNAVAIL_4, "SENSOR_UNAVAIL[4]"},
            };
            inline const std::map<RaSuccessType, std::string> ra_success_strmap = {
                {RaSuccessType::NONE_0, "NONE[0]"},
                {RaSuccessType::DATA_VALID_1, "DATA_VALID[1]"},
                {RaSuccessType::RESULT_SAVED_2, "RESULT_SAVED[2]"},
            };
            inline const std::map<RaFailType, std::string> ra_fail_strmap = {
                {RaFailType::NONE_0, "NONE[0]"},
                {RaFailType::SYS_FAULT_1, "SYS_FAULT[1]"},
                {RaFailType::SENSOR_FAIL_2, "SENSOR_FAIL[2]"},
                {RaFailType::INVALID_DATA_3, "INVALID_DATA[3]"},
                {RaFailType::STORAGE_FAIL_4, "STORAGE_FAIL[4]"},
                {RaFailType::USER_CANCEL_5, "USER_CANCEL[5]"},
                {RaFailType::TIMEOUT_6, "TIMEOUT[6]"},
            };
            inline const std::map<RaExitType, std::string> ra_exit_strmap = {
                {RaExitType::NONE_0, "NONE[0]"},
                {RaExitType::SUCCESS_1, "SUCCESS[1]"},
                {RaExitType::FAILURE_2, "FAILURE[2]"},
                {RaExitType::USER_REQ_3, "USER_REQ[3]"},
                {RaExitType::SYS_FAULT_4, "SYS_FAULT[4]"},
                {RaExitType::VEH_COND_5, "VEH_COND[5]"},
            };

        } // namespace parking
    } // namespace function
} // namespace structure
