#pragma once

#include <cstdint>
#include "parking_event_enum.h"

namespace parking
{
struct ParkingEventBase
{
    /** @brief 激活事件成员。 */
    PrkgFuncActvType actv_{static_cast<PrkgFuncActvType>(0)};
    /** @brief 激活抑制事件成员。 */
    PrkgFuncActvIhbtType actv_inhibited_{static_cast<PrkgFuncActvIhbtType>(0)};
    /** @brief 控车激活事件成员。 */
    PrkgFuncGuidanceType guidance_{static_cast<PrkgFuncGuidanceType>(0)};
    /** @brief 控车激活抑制事件成员。 */
    PrkgFuncGuidanceIhbtType guidance_inhibited_{static_cast<PrkgFuncGuidanceIhbtType>(0)};
    /** @brief 暂停事件成员。 */
    PrkgFuncPauseType pause_{static_cast<PrkgFuncPauseType>(0)};
    /** @brief 成功事件成员。 */
    PrkgFuncSuccessType success_{static_cast<PrkgFuncSuccessType>(0)};
    /** @brief 失败事件成员。 */
    PrkgFuncFailType fail_{static_cast<PrkgFuncFailType>(0)};
    /** @brief 退出事件成员。 */
    PrkgFuncExitType exit_{static_cast<PrkgFuncExitType>(0)};
};
}  // namespace parking