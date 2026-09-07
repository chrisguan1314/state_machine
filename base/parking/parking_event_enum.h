#pragma once

#include <cstdint>
#include <unordered_map>

namespace parking
{

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

std::unordered_map<ParkingEventType, std::string> parking_event_strmap = {
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