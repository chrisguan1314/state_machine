#pragma once

#include <map>
#include <string>

#include "avp_cruising_event_enum.h"

namespace structure
{
    namespace function
    {
        namespace parking
        {

            inline const std::map<AvpcActvType, std::string> avpc_actv_strmap = {
                {AvpcActvType::NONE_0, "NONE[0]"},
                {AvpcActvType::BTN_1, "BTN[1]"},
                {AvpcActvType::KEY_2, "KEY[2]"},
                {AvpcActvType::APP_3, "APP[3]"},
                {AvpcActvType::AUTO_4, "AUTO[4]"},
            };
            inline const std::map<AvpcActvIhbtType, std::string> avpc_actv_ihbt_strmap = {
                {AvpcActvIhbtType::NONE_0, "NONE[0]"},
                {AvpcActvIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {AvpcActvIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<AvpcGuidanceType, std::string> avpc_guidance_strmap = {
                {AvpcGuidanceType::NONE_0, "NONE[0]"},
                {AvpcGuidanceType::ACTIVE_1, "ACTIVE[1]"},
            };
            inline const std::map<AvpcGuidanceIhbtType, std::string> avpc_guidance_ihbt_strmap = {
                {AvpcGuidanceIhbtType::NONE_0, "NONE[0]"},
                {AvpcGuidanceIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {AvpcGuidanceIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<AvpcPauseType, std::string> avpc_pause_strmap = {
                {AvpcPauseType::NONE_0, "NONE[0]"},
                {AvpcPauseType::USER_REQ_1, "USER_REQ[1]"},
                {AvpcPauseType::SYS_FAULT_2, "SYS_FAULT[2]"},
                {AvpcPauseType::VEH_COND_3, "VEH_COND[3]"},
                {AvpcPauseType::SENSOR_UNAVAIL_4, "SENSOR_UNAVAIL[4]"},
            };
            inline const std::map<AvpcSuccessType, std::string> avpc_success_strmap = {
                {AvpcSuccessType::NONE_0, "NONE[0]"},
                {AvpcSuccessType::DATA_VALID_1, "DATA_VALID[1]"},
                {AvpcSuccessType::RESULT_SAVED_2, "RESULT_SAVED[2]"},
            };
            inline const std::map<AvpcFailType, std::string> avpc_fail_strmap = {
                {AvpcFailType::NONE_0, "NONE[0]"},
                {AvpcFailType::SYS_FAULT_1, "SYS_FAULT[1]"},
                {AvpcFailType::SENSOR_FAIL_2, "SENSOR_FAIL[2]"},
                {AvpcFailType::INVALID_DATA_3, "INVALID_DATA[3]"},
                {AvpcFailType::STORAGE_FAIL_4, "STORAGE_FAIL[4]"},
                {AvpcFailType::USER_CANCEL_5, "USER_CANCEL[5]"},
                {AvpcFailType::TIMEOUT_6, "TIMEOUT[6]"},
            };
            inline const std::map<AvpcExitType, std::string> avpc_exit_strmap = {
                {AvpcExitType::NONE_0, "NONE[0]"},
                {AvpcExitType::SUCCESS_1, "SUCCESS[1]"},
                {AvpcExitType::FAILURE_2, "FAILURE[2]"},
                {AvpcExitType::USER_REQ_3, "USER_REQ[3]"},
                {AvpcExitType::SYS_FAULT_4, "SYS_FAULT[4]"},
                {AvpcExitType::VEH_COND_5, "VEH_COND[5]"},
            };

        } // namespace parking
    } // namespace function
} // namespace structure
