#pragma once

#include <map>
#include <string>

#include "rpa_event_enum.h"

namespace structure
{
    namespace function
    {
        namespace parking
        {

            inline const std::map<RpaActvType, std::string> rpa_actv_strmap =
                {
                    {RpaActvType::NONE_0, "NONE[0]"},
                    {RpaActvType::BTN_1, "BTN[1]"},
                    {RpaActvType::KEY_2, "KEY[2]"},
                    {RpaActvType::APP_3, "APP[3]"},
                    {RpaActvType::AUTO_4, "AUTO[4]"},
            };
            inline const std::map<RpaActvIhbtType, std::string> rpa_actv_ihbt_strmap = {
                {RpaActvIhbtType::NONE_0, "NONE[0]"},
                {RpaActvIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {RpaActvIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<RpaGuidanceType, std::string> rpa_guidance_strmap = {
                {RpaGuidanceType::NONE_0, "NONE[0]"},
                {RpaGuidanceType::ACTIVE_1, "ACTIVE[1]"},
            };
            inline const std::map<RpaGuidanceIhbtType, std::string> rpa_guidance_ihbt_strmap = {
                {RpaGuidanceIhbtType::NONE_0, "NONE[0]"},
                {RpaGuidanceIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {RpaGuidanceIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };
            inline const std::map<RpaPauseType, std::string> rpa_pause_strmap = {
                {RpaPauseType::NONE_0, "NONE[0]"},
                {RpaPauseType::USER_REQ_1, "USER_REQ[1]"},
                {RpaPauseType::SYS_FAULT_2, "SYS_FAULT[2]"},
                {RpaPauseType::VEH_COND_3, "VEH_COND[3]"},
                {RpaPauseType::SENSOR_UNAVAIL_4, "SENSOR_UNAVAIL[4]"},
            };
            inline const std::map<RpaSuccessType, std::string> rpa_success_strmap = {
                {RpaSuccessType::NONE_0, "NONE[0]"},
                {RpaSuccessType::DATA_VALID_1, "DATA_VALID[1]"},
                {RpaSuccessType::RESULT_SAVED_2, "RESULT_SAVED[2]"},
            };
            inline const std::map<RpaFailType, std::string> rpa_fail_strmap = {
                {RpaFailType::NONE_0, "NONE[0]"},
                {RpaFailType::SYS_FAULT_1, "SYS_FAULT[1]"},
                {RpaFailType::SENSOR_FAIL_2, "SENSOR_FAIL[2]"},
                {RpaFailType::INVALID_DATA_3, "INVALID_DATA[3]"},
                {RpaFailType::STORAGE_FAIL_4, "STORAGE_FAIL[4]"},
                {RpaFailType::USER_CANCEL_5, "USER_CANCEL[5]"},
                {RpaFailType::TIMEOUT_6, "TIMEOUT[6]"},
            };
            inline const std::map<RpaExitType, std::string> rpa_exit_strmap = {
                {RpaExitType::NONE_0, "NONE[0]"},
                {RpaExitType::SUCCESS_1, "SUCCESS[1]"},
                {RpaExitType::FAILURE_2, "FAILURE[2]"},
                {RpaExitType::USER_REQ_3, "USER_REQ[3]"},
                {RpaExitType::SYS_FAULT_4, "SYS_FAULT[4]"},
                {RpaExitType::VEH_COND_5, "VEH_COND[5]"},
            };

        } // namespace parking
    } // namespace function
} // namespace structure
