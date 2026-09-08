#pragma once

#include "avm_event_map.h"
#include "../parking_event_manager.h"

namespace structure
{
namespace function
{
namespace parking
{

/** @brief 保存和查询 AVM 事件。 */
class AvmEventManager : public ::parking::ParkingEventManager
{
protected:
    void LogEventChange(::parking::ParkingEventType event_type, int value) noexcept override
    {
        const auto log = [](const auto& strmap, const char* event_name, auto event_value) {
            const auto it = strmap.find(event_value);
            if (it != strmap.end()) std::clog << "AvmEventManager: " << event_name << " = " << it->second << std::endl;
        };
        switch (event_type)
        {
            case ParkingEventType::ACTV_1: log(avm_actv_strmap, "ACTV", static_cast<AvmActvType>(value)); break;
            case ParkingEventType::ACTV_IHBT_2: log(avm_actv_ihbt_strmap, "ACTV_IHBT", static_cast<AvmActvIhbtType>(value)); break;
            case ParkingEventType::GUIDANCE_3: log(avm_guidance_strmap, "GUIDANCE", static_cast<AvmGuidanceType>(value)); break;
            case ParkingEventType::GUIDANCE_IHBT_4: log(avm_guidance_ihbt_strmap, "GUIDANCE_IHBT", static_cast<AvmGuidanceIhbtType>(value)); break;
            case ParkingEventType::PAUSE_5: log(avm_pause_strmap, "PAUSE", static_cast<AvmPauseType>(value)); break;
            case ParkingEventType::SUCCESS_6: log(avm_success_strmap, "SUCCESS", static_cast<AvmSuccessType>(value)); break;
            case ParkingEventType::FAIL_7: log(avm_fail_strmap, "FAIL", static_cast<AvmFailType>(value)); break;
            case ParkingEventType::EXIT_8: log(avm_exit_strmap, "EXIT", static_cast<AvmExitType>(value)); break;
            case ParkingEventType::NONE_0: default: break;
        }
    }
};

}  // namespace parking
}  // namespace function
}  // namespace structure
