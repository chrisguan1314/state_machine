#pragma once

#include <map>
#include <string>

#include "avm_event_enum.h"

namespace structure
{
    namespace function
    {
        namespace parking
        {

            inline const std::map<AvmActvType, std::string> avm_actv_strmap = {
                {AvmActvType::NONE_0, "NONE[0]"},
                {AvmActvType::BTN_1, "BTN[1]"},
                {AvmActvType::KEY_2, "KEY[2]"},
                {AvmActvType::APP_3, "APP[3]"},
                {AvmActvType::AUTO_4, "AUTO[4]"},
            };
            inline const std::map<AvmActvIhbtType, std::string> avm_actv_ihbt_strmap = {
                {AvmActvIhbtType::NONE_0, "NONE[0]"},
                {AvmActvIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {AvmActvIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<AvmGuidanceType, std::string> avm_guidance_strmap = {
                {AvmGuidanceType::NONE_0, "NONE[0]"},
                {AvmGuidanceType::ACTIVE_1, "ACTIVE[1]"},
            };
            inline const std::map<AvmGuidanceIhbtType, std::string> avm_guidance_ihbt_strmap = {
                {AvmGuidanceIhbtType::NONE_0, "NONE[0]"},
                {AvmGuidanceIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {AvmGuidanceIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<AvmPauseType, std::string> avm_pause_strmap = {
                {AvmPauseType::NONE_0, "NONE[0]"},
                {AvmPauseType::USER_REQ_1, "USER_REQ[1]"},
                {AvmPauseType::SYS_FAULT_2, "SYS_FAULT[2]"},
                {AvmPauseType::VEH_COND_3, "VEH_COND[3]"},
                {AvmPauseType::SENSOR_UNAVAIL_4, "SENSOR_UNAVAIL[4]"},
            };
            inline const std::map<AvmSuccessType, std::string> avm_success_strmap = {
                {AvmSuccessType::NONE_0, "NONE[0]"},
                {AvmSuccessType::DATA_VALID_1, "DATA_VALID[1]"},
                {AvmSuccessType::RESULT_SAVED_2, "RESULT_SAVED[2]"},
            };
            inline const std::map<AvmFailType, std::string> avm_fail_strmap = {
                {AvmFailType::NONE_0, "NONE[0]"},
                {AvmFailType::SYS_FAULT_1, "SYS_FAULT[1]"},
                {AvmFailType::SENSOR_FAIL_2, "SENSOR_FAIL[2]"},
                {AvmFailType::INVALID_DATA_3, "INVALID_DATA[3]"},
                {AvmFailType::STORAGE_FAIL_4, "STORAGE_FAIL[4]"},
                {AvmFailType::USER_CANCEL_5, "USER_CANCEL[5]"},
                {AvmFailType::TIMEOUT_6, "TIMEOUT[6]"},
            };
            inline const std::map<AvmExitType, std::string> avm_exit_strmap = {
                {AvmExitType::NONE_0, "NONE[0]"},
                {AvmExitType::SUCCESS_1, "SUCCESS[1]"},
                {AvmExitType::FAILURE_2, "FAILURE[2]"},
                {AvmExitType::USER_REQ_3, "USER_REQ[3]"},
                {AvmExitType::SYS_FAULT_4, "SYS_FAULT[4]"},
                {AvmExitType::VEH_COND_5, "VEH_COND[5]"},
            };

        } // namespace parking
    } // namespace function
} // namespace structure
