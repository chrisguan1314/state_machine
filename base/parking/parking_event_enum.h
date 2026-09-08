#pragma once

#include <cstdint>
#include <unordered_map>

namespace parking
{

    /** @brief 功能 激活来源。 */
enum class PrkgFuncActvType : std::uint8_t
{
    NONE_0,
    BTN_1,
    KEY_2,
    APP_3,
    AUTO_4,
};

/** @brief 功能 激活抑制原因。 */
enum class PrkgFuncActvIhbtType : std::uint8_t
{
    NONE_0,
    UNKNOWN_1,
    SYS_FAULT_2,
};

/** @brief 功能 控车激活来源。 */
enum class PrkgFuncGuidanceType : std::uint8_t
{
    NONE_0,
    BTN_1,
    KEY_2,
    APP_3,
    LEVER_4,
    AUTO_5,
};

/** @brief 功能 控车激活抑制原因。 */
enum class PrkgFuncGuidanceIhbtType : std::uint8_t
{
    NONE_0,
    UNKNOWN_1,
    SYS_FAULT_2,
};

/** @brief 功能 暂停条件。 */
enum class PrkgFuncPauseType : std::uint8_t
{
    NONE_0,
    USER_REQ_1,
    SYS_FAULT_2,
    VEH_COND_3,
    SENSOR_UNAVAIL_4,
};

/** @brief 功能 成功条件。 */
enum class PrkgFuncSuccessType : std::uint8_t
{
    NONE_0,
    DATA_VALID_1,
    RESULT_SAVED_2,
};

/** @brief 功能 失败条件。 */
enum class PrkgFuncFailType : std::uint8_t
{
    NONE_0,
    SYS_FAULT_1,
    SENSOR_FAIL_2,
    INVALID_DATA_3,
    STORAGE_FAIL_4,
    USER_CANCEL_5,
    TIMEOUT_6,
};

/** @brief 功能 退出条件。 */
enum class PrkgFuncExitType : std::uint8_t
{
    NONE_0,
    SUCCESS_1,
    FAILURE_2,
    USER_REQ_3,
    SYS_FAULT_4,
    VEH_COND_5,
};

/** @brief APA 激活来源到字符串的映射。 */
    inline const std::unordered_map<PrkgFuncActvType, std::string> actv_strmap = {
        {PrkgFuncActvType::NONE_0, "NONE[0]"},
        {PrkgFuncActvType::BTN_1, "BTN[1]"},
        {PrkgFuncActvType::KEY_2, "KEY[2]"},
        {PrkgFuncActvType::APP_3, "APP[3]"},
        {PrkgFuncActvType::AUTO_4, "AUTO[4]"},
    };

    /** @brief APA 激活抑制原因到字符串的映射。 */
    inline const std::unordered_map<PrkgFuncActvIhbtType, std::string> actv_ihbt_strmap = {
        {PrkgFuncActvIhbtType::NONE_0, "NONE[0]"},
        {PrkgFuncActvIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
        {PrkgFuncActvIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
    };

    /** @brief APA 控车激活来源到字符串的映射。 */
    inline const std::unordered_map<PrkgFuncGuidanceType, std::string> guidance_strmap = {
        {PrkgFuncGuidanceType::NONE_0, "NONE[0]"},
        {PrkgFuncGuidanceType::BTN_1, "BTN[1]"},
        {PrkgFuncGuidanceType::KEY_2, "KEY[2]"},
        {PrkgFuncGuidanceType::APP_3, "APP[3]"},
        {PrkgFuncGuidanceType::LEVER_4, "LEVER[4]"},
        {PrkgFuncGuidanceType::AUTO_5, "AUTO[5]"},
    };

    /** @brief APA 控车激活抑制原因到字符串的映射。 */
    inline const std::unordered_map<PrkgFuncGuidanceIhbtType, std::string> guidance_ihbt_strmap = {
        {PrkgFuncGuidanceIhbtType::NONE_0, "NONE[0]"},
        {PrkgFuncGuidanceIhbtType::UNKNOWN_1, "UNKNOWN[1]"},
        {PrkgFuncGuidanceIhbtType::SYS_FAULT_2, "SYS_FAULT[2]"},
    };

    /** @brief APA 暂停条件到字符串的映射。 */
    inline const std::unordered_map<PrkgFuncPauseType, std::string> pause_strmap = {
        {PrkgFuncPauseType::NONE_0, "NONE[0]"},
        {PrkgFuncPauseType::USER_REQ_1, "USER_REQ[1]"},
        {PrkgFuncPauseType::SYS_FAULT_2, "SYS_FAULT[2]"},
        {PrkgFuncPauseType::VEH_COND_3, "VEH_COND[3]"},
        {PrkgFuncPauseType::SENSOR_UNAVAIL_4, "SENSOR_UNAVAIL[4]"},
    };

    /** @brief APA 成功条件到字符串的映射。 */
    inline const std::unordered_map<PrkgFuncSuccessType, std::string> success_strmap = {
        {PrkgFuncSuccessType::NONE_0, "NONE[0]"},
        {PrkgFuncSuccessType::DATA_VALID_1, "DATA_VALID[1]"},
        {PrkgFuncSuccessType::RESULT_SAVED_2, "RESULT_SAVED[2]"},
    };

    /** @brief APA 失败条件到字符串的映射。 */
    inline const std::unordered_map<PrkgFuncFailType, std::string> fail_strmap = {
        {PrkgFuncFailType::NONE_0, "NONE[0]"},
        {PrkgFuncFailType::SYS_FAULT_1, "SYS_FAULT[1]"},
        {PrkgFuncFailType::SENSOR_FAIL_2, "SENSOR_FAIL[2]"},
        {PrkgFuncFailType::INVALID_DATA_3, "INVALID_DATA[3]"},
        {PrkgFuncFailType::STORAGE_FAIL_4, "STORAGE_FAIL[4]"},
        {PrkgFuncFailType::USER_CANCEL_5, "USER_CANCEL[5]"},
        {PrkgFuncFailType::TIMEOUT_6, "TIMEOUT[6]"},
    };

    /** @brief APA 退出条件到字符串的映射。 */
    inline const std::unordered_map<PrkgFuncExitType, std::string> exit_strmap = {
        {PrkgFuncExitType::NONE_0, "NONE[0]"},
        {PrkgFuncExitType::SUCCESS_1, "SUCCESS[1]"},
        {PrkgFuncExitType::FAILURE_2, "FAILURE[2]"},
        {PrkgFuncExitType::USER_REQ_3, "USER_REQ[3]"},
        {PrkgFuncExitType::SYS_FAULT_4, "SYS_FAULT[4]"},
        {PrkgFuncExitType::VEH_COND_5, "VEH_COND[5]"},
    };

/**
 * @brief 停车功能通用事件类型。
 *
 * 业务事件类负责自己的强类型条件枚举和业务语义；本类只负责通用的
 * NONE_0 到 EXIT_8 事件标志，避免各功能重复实现相同的数组、查询、
 * 设置和重置逻辑。
 *
 * @tparam EventType 业务事件枚举类型，其底层值必须是 0 到 8。
 */
/** @brief 通用停车事件类型，供 ParkingEventManager 使用。 */
enum class ParkingEventType : std::uint8_t
{
    NONE_0,
    ACTV_1,
    ACTV_IHBT_2,
    GUIDANCE_3,
    GUIDANCE_IHBT_4,
    PAUSE_5,
    SUCCESS_6,
    FAIL_7,
    EXIT_8,
};

inline const std::unordered_map<ParkingEventType, std::string> parking_event_strmap = {
    {ParkingEventType::NONE_0, "NONE[0]"},
    {ParkingEventType::ACTV_1, "ACTV[1]"},
    {ParkingEventType::ACTV_IHBT_2, "ACTV_IHBT[2]"},
    {ParkingEventType::GUIDANCE_3, "GUIDANCE[3]"},
    {ParkingEventType::GUIDANCE_IHBT_4, "GUIDANCE_IHBT[4]"},
    {ParkingEventType::PAUSE_5, "PAUSE[5]"},
    {ParkingEventType::SUCCESS_6, "SUCCESS[6]"},
    {ParkingEventType::FAIL_7, "FAIL[7]"},
    {ParkingEventType::EXIT_8, "EXIT[8]"},
};
}  // namespace parking