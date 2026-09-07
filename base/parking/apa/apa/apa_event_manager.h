#pragma once
#include "apa_event_map.h"
#include "../../parking_event_manager.h"
#include "../../../../log_base.h"

namespace parking
{
inline std::string EventFormator(const std::string &value)
{
    return Format(value, parking_event_strmap);
}
/**
 * @brief 保存和查询 APA 事件。
 */
class ApaEventManager : public ParkingEventManager<ApaActvType, ApaActvIhbtType, ApaGuidanceType,
                                         ApaGuidanceIhbtType, ApaPauseType, ApaSuccessType,
                                         ApaFailType, ApaExitType>
{
protected:
    void LogEventChange(ParkingEventType event_type, int value) noexcept override
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
public:
    static std::string GetEventName() noexcept 
    {
        return parking_event_strmap.at(GetEventType());
    }
    static std::string GetEventTypeName() noexcept
    {
        switch (GetEventType())
        {
            case ParkingEventType::ACTV_1: return apa_actv_strmap.at(GetActv());
            case ParkingEventType::ACTV_IHBT_2: return apa_actv_ihbt_strmap.at(GetActvInhibited());
            case ParkingEventType::GUIDANCE_3: return apa_guidance_strmap.at(GetGuidance());
            case ParkingEventType::GUIDANCE_IHBT_4: return apa_guidance_ihbt_strmap.at(GetGuidanceInhibited());
            case ParkingEventType::PAUSE_5: return apa_pause_strmap.at(GetPause());
            case ParkingEventType::SUCCESS_6: return apa_success_strmap.at(GetSuccess());
            case ParkingEventType::FAIL_7: return apa_fail_strmap.at(GetFail());
            case ParkingEventType::EXIT_8: return apa_exit_strmap.at(GetExit());
            case ParkingEventType::NONE_0:
            default: return "NONE";
        }
    }
};

}  // namespace parking
