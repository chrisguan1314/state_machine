#pragma once

#include "rpa_event_map.h"
#include "../../parking_event_manager.h"

namespace structure
{
namespace function
{
namespace parking
{

/**
 * @brief 保存和查询 RPA 事件。
 */
class RpaEventManager : public ::parking::ParkingEventManager
{
protected:
    void LogEventChange(::parking::ParkingEventType event_type, int value) noexcept override
    {
        const auto log = [](const auto& strmap, const char* event_name, auto event_value) {
            const auto it = strmap.find(event_value);
            if (it != strmap.end()) std::clog << "RpaEventManager: " << event_name << " = " << it->second << std::endl;
        };
        switch (event_type)
        {
            case ParkingEventType::ACTV_1: log(rpa_actv_strmap, "ACTV", static_cast<RpaActvType>(value)); break;
            case ParkingEventType::ACTV_IHBT_2: log(rpa_actv_ihbt_strmap, "ACTV_IHBT", static_cast<RpaActvIhbtType>(value)); break;
            case ParkingEventType::GUIDANCE_3: log(rpa_guidance_strmap, "GUIDANCE", static_cast<RpaGuidanceType>(value)); break;
            case ParkingEventType::GUIDANCE_IHBT_4: log(rpa_guidance_ihbt_strmap, "GUIDANCE_IHBT", static_cast<RpaGuidanceIhbtType>(value)); break;
            case ParkingEventType::PAUSE_5: log(rpa_pause_strmap, "PAUSE", static_cast<RpaPauseType>(value)); break;
            case ParkingEventType::SUCCESS_6: log(rpa_success_strmap, "SUCCESS", static_cast<RpaSuccessType>(value)); break;
            case ParkingEventType::FAIL_7: log(rpa_fail_strmap, "FAIL", static_cast<RpaFailType>(value)); break;
            case ParkingEventType::EXIT_8: log(rpa_exit_strmap, "EXIT", static_cast<RpaExitType>(value)); break;
            case ParkingEventType::NONE_0: default: break;
        }
    }
};

}  // namespace parking
}  // namespace function
}  // namespace structure
