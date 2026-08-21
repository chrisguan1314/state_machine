#pragma once

#include <cstdint>

namespace structure
{
namespace function
{
namespace parking
{
template <typename ActvType,
          typename ActvIhbtType,
          typename GuidanceType,
          typename GuidanceIhbtType,
          typename PauseType,
          typename SuccessType,
          typename FailType,
          typename ExitType>
struct ParkingEventBase
{
    /** @brief 激活事件成员。 */
    ActvType actv_{static_cast<ActvType>(0)};
    /** @brief 激活抑制事件成员。 */
    ActvIhbtType actv_inhibited_{static_cast<ActvIhbtType>(0)};
    /** @brief 控车激活事件成员。 */
    GuidanceType guidance_{static_cast<GuidanceType>(0)};
    /** @brief 控车激活抑制事件成员。 */
    GuidanceIhbtType guidance_inhibited_{static_cast<GuidanceIhbtType>(0)};
    /** @brief 暂停事件成员。 */
    PauseType pause_{static_cast<PauseType>(0)};
    /** @brief 成功事件成员。 */
    SuccessType success_{static_cast<SuccessType>(0)};
    /** @brief 失败事件成员。 */
    FailType fail_{static_cast<FailType>(0)};
    /** @brief 退出事件成员。 */
    ExitType exit_{static_cast<ExitType>(0)};
};
}  // namespace parking
}  // namespace function
}  // namespace structure