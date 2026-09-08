#pragma once

#include "../../parking_event_manager.h"

namespace parking
{

    class ApoEventManager : public ParkingEventManager
    {
    protected:

        void LogEventChange(ParkingEventType event_type, int value) noexcept override
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
                log(actv_strmap, "ACTV", static_cast<PrkgFuncActvType>(value));
                break;
            case ParkingEventType::ACTV_IHBT_2:
                log(actv_ihbt_strmap, "ACTV_IHBT", static_cast<PrkgFuncActvIhbtType>(value));
                break;
            case ParkingEventType::GUIDANCE_3:
                log(guidance_strmap, "GUIDANCE", static_cast<PrkgFuncGuidanceType>(value));
                break;
            case ParkingEventType::GUIDANCE_IHBT_4:
                log(guidance_ihbt_strmap, "GUIDANCE_IHBT", static_cast<PrkgFuncGuidanceIhbtType>(value));
                break;
            case ParkingEventType::PAUSE_5:
                log(pause_strmap, "PAUSE", static_cast<PrkgFuncPauseType>(value));
                break;
            case ParkingEventType::SUCCESS_6:
                log(success_strmap, "SUCCESS", static_cast<PrkgFuncSuccessType>(value));
                break;
            case ParkingEventType::FAIL_7:
                log(fail_strmap, "FAIL", static_cast<PrkgFuncFailType>(value));
                break;
            case ParkingEventType::EXIT_8:
                log(exit_strmap, "EXIT", static_cast<PrkgFuncExitType>(value));
                break;
            case ParkingEventType::NONE_0:
            default:
                break;
            }
        }
    };

} // namespace parking
