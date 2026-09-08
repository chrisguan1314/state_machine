#pragma once

#include "straight_summon_event_map.h"
#include "../../parking_event_manager.h"

namespace parking
{

/** @brief 保存和查询直线召唤事件。 */
class StraightSummonEventManager : public ParkingEventManager
{
protected:
    void LogEventChange(ParkingEventType event_type, int value) noexcept override
    {
        const auto log = [](const auto& strmap, const char* event_name, auto event_value) {
            const auto it = strmap.find(event_value);
            if (it != strmap.end()) std::clog << "StraightSummonEventManager: " << event_name << " = " << it->second << std::endl;
        };
        switch (event_type)
        {
            case ParkingEventType::ACTV_1: log(straight_summon_actv_strmap, "ACTV", static_cast<StraightSummonActvType>(value)); break;
            case ParkingEventType::ACTV_IHBT_2: log(straight_summon_actv_ihbt_strmap, "ACTV_IHBT", static_cast<StraightSummonActvIhbtType>(value)); break;
            case ParkingEventType::GUIDANCE_3: log(straight_summon_guidance_strmap, "GUIDANCE", static_cast<StraightSummonGuidanceType>(value)); break;
            case ParkingEventType::GUIDANCE_IHBT_4: log(straight_summon_guidance_ihbt_strmap, "GUIDANCE_IHBT", static_cast<StraightSummonGuidanceIhbtType>(value)); break;
            case ParkingEventType::PAUSE_5: log(straight_summon_pause_strmap, "PAUSE", static_cast<StraightSummonPauseType>(value)); break;
            case ParkingEventType::SUCCESS_6: log(straight_summon_success_strmap, "SUCCESS", static_cast<StraightSummonSuccessType>(value)); break;
            case ParkingEventType::FAIL_7: log(straight_summon_fail_strmap, "FAIL", static_cast<StraightSummonFailType>(value)); break;
            case ParkingEventType::EXIT_8: log(straight_summon_exit_strmap, "EXIT", static_cast<StraightSummonExitType>(value)); break;
            case ParkingEventType::NONE_0: default: break;
        }
    }
};

}  // namespace parking
