#pragma once

#include <cstdint>

namespace structure
{
namespace function
{
namespace parking
{

/** @brief APA 激活来源。 */
enum class ApaActvType : std::uint8_t
{
    NONE_0,
    BTN_1,
    KEY_2,
    APP_3,
    AUTO_4,
};

/** @brief APA 激活抑制原因。 */
enum class ApaActvIhbtType : std::uint8_t
{
    NONE_0,
    UNKNOWN_1,
    SYS_FAULT_2,
};

/** @brief APA 控车激活状态。 */
enum class ApaGuidanceType : std::uint8_t
{
    NONE_0,
    ACTIVE_1,
};

/** @brief APA 控车激活抑制原因。 */
enum class ApaGuidanceIhbtType : std::uint8_t
{
    NONE_0,
    UNKNOWN_1,
    SYS_FAULT_2,
};

/** @brief APA 暂停条件。 */
enum class ApaPauseType : std::uint8_t
{
    NONE_0,
    USER_REQ_1,
    SYS_FAULT_2,
    VEH_COND_3,
    SENSOR_UNAVAIL_4,
};

/** @brief APA 成功条件。 */
enum class ApaSuccessType : std::uint8_t
{
    NONE_0,
    DATA_VALID_1,
    RESULT_SAVED_2,
};

/** @brief APA 失败条件。 */
enum class ApaFailType : std::uint8_t
{
    NONE_0,
    SYS_FAULT_1,
    SENSOR_FAIL_2,
    INVALID_DATA_3,
    STORAGE_FAIL_4,
    USER_CANCEL_5,
    TIMEOUT_6,
};

/** @brief APA 退出条件。 */
enum class ApaExitType : std::uint8_t
{
    NONE_0,
    SUCCESS_1,
    FAILURE_2,
    USER_REQ_3,
    SYS_FAULT_4,
    VEH_COND_5,
};

}
}
}