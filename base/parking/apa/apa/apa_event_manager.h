#pragma once
#include "apa_event_map.h"
#include "../../parking_event_manager.h"

namespace parking
{

/**
 * @brief 保存和查询 APA 事件。
 */
class ApaEventManager : public ParkingEventManager<ApaActvType, ApaActvIhbtType, ApaGuidanceType,
                                         ApaGuidanceIhbtType, ApaPauseType, ApaSuccessType,
                                         ApaFailType, ApaExitType>
{
protected:
    void UpdateEvent() noexcept override {}

    void LogEventChange(ParkingEventType event_type, int value) const noexcept override
    {
        const auto log = [](const auto& strmap, const char* event_name, auto event_value) {
            const auto it = strmap.find(event_value);
            if (it != strmap.end())
            {
                std::clog << "ApaEventManager: " << event_name << " = " << it->second << std::endl;
            }
        };
        switch (event_type)
        {
            case ParkingEventType::ACTV_1: log(apa_actv_strmap, "ACTV", static_cast<ApaActvType>(value)); break;
            case ParkingEventType::ACTV_IHBT_2: log(apa_actv_ihbt_strmap, "ACTV_IHBT", static_cast<ApaActvIhbtType>(value)); break;
            case ParkingEventType::GUIDANCE_3: log(apa_guidance_strmap, "GUIDANCE", static_cast<ApaGuidanceType>(value)); break;
            case ParkingEventType::GUIDANCE_IHBT_4: log(apa_guidance_ihbt_strmap, "GUIDANCE_IHBT", static_cast<ApaGuidanceIhbtType>(value)); break;
            case ParkingEventType::PAUSE_5: log(apa_pause_strmap, "PAUSE", static_cast<ApaPauseType>(value)); break;
            case ParkingEventType::SUCCESS_6: log(apa_success_strmap, "SUCCESS", static_cast<ApaSuccessType>(value)); break;
            case ParkingEventType::FAIL_7: log(apa_fail_strmap, "FAIL", static_cast<ApaFailType>(value)); break;
            case ParkingEventType::EXIT_8: log(apa_exit_strmap, "EXIT", static_cast<ApaExitType>(value)); break;
            case ParkingEventType::NONE_0: default: break;
        }
    }
};

}  // namespace parking
