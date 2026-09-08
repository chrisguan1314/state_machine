#pragma once

#include "ra_event_map.h"
#include "../parking_event_manager.h"

namespace structure
{
namespace function
{
namespace parking
{

/** @brief 保存和查询 RA 事件。 */
class RaEventManager : public ::parking::ParkingEventManager
{
protected:
    void LogEventChange(::parking::ParkingEventType event_type, int value) noexcept override
    {
        const auto log = [](const auto& strmap, const char* event_name, auto event_value) {
            const auto it = strmap.find(event_value);
            if (it != strmap.end()) std::clog << "RaEventManager: " << event_name << " = " << it->second << std::endl;
        };
        switch (event_type)
        {
            case ParkingEventType::ACTV_1: log(ra_actv_strmap, "ACTV", static_cast<RaActvType>(value)); break;
            case ParkingEventType::ACTV_IHBT_2: log(ra_actv_ihbt_strmap, "ACTV_IHBT", static_cast<RaActvIhbtType>(value)); break;
            case ParkingEventType::GUIDANCE_3: log(ra_guidance_strmap, "GUIDANCE", static_cast<RaGuidanceType>(value)); break;
            case ParkingEventType::GUIDANCE_IHBT_4: log(ra_guidance_ihbt_strmap, "GUIDANCE_IHBT", static_cast<RaGuidanceIhbtType>(value)); break;
            case ParkingEventType::PAUSE_5: log(ra_pause_strmap, "PAUSE", static_cast<RaPauseType>(value)); break;
            case ParkingEventType::SUCCESS_6: log(ra_success_strmap, "SUCCESS", static_cast<RaSuccessType>(value)); break;
            case ParkingEventType::FAIL_7: log(ra_fail_strmap, "FAIL", static_cast<RaFailType>(value)); break;
            case ParkingEventType::EXIT_8: log(ra_exit_strmap, "EXIT", static_cast<RaExitType>(value)); break;
            case ParkingEventType::NONE_0: default: break;
        }
    }
};

}  // namespace parking
}  // namespace function
}  // namespace structure
