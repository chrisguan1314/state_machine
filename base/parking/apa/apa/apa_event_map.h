#pragma once

#include <map>
#include <string>

#include "apa_event_enum.h"

namespace structure
{
    namespace function
    {
        namespace parking
        {

            /** @brief APA 激活来源到字符串的映射。 */
            inline const std::map<ApaActvType, std::string> apa_actv_strmap = {
                {ApaActvType::NONE_0, "NONE[0]"},
                {ApaActvType::BTN_1, "BTN[1]"},
                {ApaActvType::KEY_2, "KEY[2]"},
                {ApaActvType::APP_3, "APP[3]"},
                {ApaActvType::AUTO_4, "AUTO[4]"},
            };

            /** @brief APA 激活抑制原因到字符串的映射。 */
            inline const std::map<ApaActvIhbtType, std::string> apa_actv_ihbt_strmap = {
                {ApaActvIhbtType::NONE_0, "NONE[0]"},
                {ApaActvIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {ApaActvIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };

            /** @brief APA 控车激活状态到字符串的映射。 */
            inline const std::map<ApaGuidanceType, std::string> apa_guidance_strmap = {
                {ApaGuidanceType::NONE_0, "NONE[0]"},
                {ApaGuidanceType::ACTIVE_1, "ACTIVE[1]"},
            };

            /** @brief APA 控车激活抑制原因到字符串的映射。 */
            inline const std::map<ApaGuidanceIhbtType, std::string> apa_guidance_ihbt_strmap = {
                {ApaGuidanceIhbtType::NONE_0, "NONE[0]"},
                {ApaGuidanceIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
                {ApaGuidanceIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
            };

            /** @brief APA 暂停条件到字符串的映射。 */
            inline const std::map<ApaPauseType, std::string> apa_pause_strmap = {
                {ApaPauseType::NONE_0, "NONE[0]"},
                {ApaPauseType::USER_REQ_1, "USER_REQ[1]"},
                {ApaPauseType::SYS_FAULT_2, "SYS_FAULT[2]"},
                {ApaPauseType::VEH_COND_3, "VEH_COND[3]"},
                {ApaPauseType::SENSOR_UNAVAIL_4, "SENSOR_UNAVAIL[4]"},
            };

            /** @brief APA 成功条件到字符串的映射。 */
            inline const std::map<ApaSuccessType, std::string> apa_success_strmap = {
                {ApaSuccessType::NONE_0, "NONE[0]"},
                {ApaSuccessType::DATA_VALID_1, "DATA_VALID[1]"},
                {ApaSuccessType::RESULT_SAVED_2, "RESULT_SAVED[2]"},
            };

            /** @brief APA 失败条件到字符串的映射。 */
            inline const std::map<ApaFailType, std::string> apa_fail_strmap = {
                {ApaFailType::NONE_0, "NONE[0]"},
                {ApaFailType::SYS_FAULT_1, "SYS_FAULT[1]"},
                {ApaFailType::SENSOR_FAIL_2, "SENSOR_FAIL[2]"},
                {ApaFailType::INVALID_DATA_3, "INVALID_DATA[3]"},
                {ApaFailType::STORAGE_FAIL_4, "STORAGE_FAIL[4]"},
                {ApaFailType::USER_CANCEL_5, "USER_CANCEL[5]"},
                {ApaFailType::TIMEOUT_6, "TIMEOUT[6]"},
            };

            /** @brief APA 退出条件到字符串的映射。 */
            inline const std::map<ApaExitType, std::string> apa_exit_strmap = {
                {ApaExitType::NONE_0, "NONE[0]"},
                {ApaExitType::SUCCESS_1, "SUCCESS[1]"},
                {ApaExitType::FAILURE_2, "FAILURE[2]"},
                {ApaExitType::USER_REQ_3, "USER_REQ[3]"},
                {ApaExitType::SYS_FAULT_4, "SYS_FAULT[4]"},
                {ApaExitType::VEH_COND_5, "VEH_COND[5]"},
            };

        } // namespace parking
    } // namespace function
} // namespace structure