#pragma once

#include "apo_event_map.h"
#include "../../parking_event_manager.h"

namespace parking
{

    class ApoEventManager : public ParkingEventManager<ApoActvType, ApoActvIhbtType, ApoGuidanceType,
                                                       ApoGuidanceIhbtType, ApoPauseType, ApoSuccessType,
                                                       ApoFailType, ApoExitType>
    {
    protected:
        void UpdateEvent() noexcept override {}

        void LogEventChange(ParkingEventType event_type, int value) const noexcept override
        {
            const auto log = [](const auto &strmap, const char *event_name, auto event_value)
            {
                const auto it = strmap.find(event_value);
                if (it != strmap.end())
                    std::clog << "ApoEventManager: " << event_name << " = " << it->second << std::endl;
            };
            switch (event_type)
            {
            case ParkingEventType::ACTV_1:
                log(apo_actv_strmap, "ACTV", static_cast<ApoActvType>(value));
                break;
            case ParkingEventType::ACTV_IHBT_2:
                log(apo_actv_ihbt_strmap, "ACTV_IHBT", static_cast<ApoActvIhbtType>(value));
                break;
            case ParkingEventType::GUIDANCE_3:
                log(apo_guidance_strmap, "GUIDANCE", static_cast<ApoGuidanceType>(value));
                break;
            case ParkingEventType::GUIDANCE_IHBT_4:
                log(apo_guidance_ihbt_strmap, "GUIDANCE_IHBT", static_cast<ApoGuidanceIhbtType>(value));
                break;
            case ParkingEventType::PAUSE_5:
                log(apo_pause_strmap, "PAUSE", static_cast<ApoPauseType>(value));
                break;
            case ParkingEventType::SUCCESS_6:
                log(apo_success_strmap, "SUCCESS", static_cast<ApoSuccessType>(value));
                break;
            case ParkingEventType::FAIL_7:
                log(apo_fail_strmap, "FAIL", static_cast<ApoFailType>(value));
                break;
            case ParkingEventType::EXIT_8:
                log(apo_exit_strmap, "EXIT", static_cast<ApoExitType>(value));
                break;
            case ParkingEventType::NONE_0:
            default:
                break;
            }
        }
    };

} // namespace parking
