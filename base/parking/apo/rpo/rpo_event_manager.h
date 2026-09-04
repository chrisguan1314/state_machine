#pragma once

#include "rpo_event_map.h"
#include "../../parking_event_manager.h"

namespace parking
{

/** @brief RPO 事件类型。 */
/** @brief 保存和查询 RPO 事件。 */
class RpoEventManager : public ParkingEventManager<RpoActvType, RpoActvIhbtType, RpoGuidanceType,
                                         RpoGuidanceIhbtType, RpoPauseType, RpoSuccessType,
                                         RpoFailType, RpoExitType>
{
protected:
    void UpdateEvent() noexcept override {}

    void LogEventChange(ParkingEventType event_type, int value) const noexcept override
    {
        const auto log = [](const auto& strmap, const char* event_name, auto event_value) {
            const auto it = strmap.find(event_value);
            if (it != strmap.end()) std::clog << "RpoEventManager: " << event_name << " = " << it->second << std::endl;
        };
        switch (event_type)
        {
            case ParkingEventType::ACTV_1: log(rpo_actv_strmap, "ACTV", static_cast<RpoActvType>(value)); break;
            case ParkingEventType::ACTV_IHBT_2: log(rpo_actv_ihbt_strmap, "ACTV_IHBT", static_cast<RpoActvIhbtType>(value)); break;
            case ParkingEventType::GUIDANCE_3: log(rpo_guidance_strmap, "GUIDANCE", static_cast<RpoGuidanceType>(value)); break;
            case ParkingEventType::GUIDANCE_IHBT_4: log(rpo_guidance_ihbt_strmap, "GUIDANCE_IHBT", static_cast<RpoGuidanceIhbtType>(value)); break;
            case ParkingEventType::PAUSE_5: log(rpo_pause_strmap, "PAUSE", static_cast<RpoPauseType>(value)); break;
            case ParkingEventType::SUCCESS_6: log(rpo_success_strmap, "SUCCESS", static_cast<RpoSuccessType>(value)); break;
            case ParkingEventType::FAIL_7: log(rpo_fail_strmap, "FAIL", static_cast<RpoFailType>(value)); break;
            case ParkingEventType::EXIT_8: log(rpo_exit_strmap, "EXIT", static_cast<RpoExitType>(value)); break;
            case ParkingEventType::NONE_0: default: break;
        }
    }
};

}  // namespace parking
