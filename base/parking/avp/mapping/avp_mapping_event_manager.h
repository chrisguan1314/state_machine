#pragma once

#include "avp_mapping_event_map.h"
#include "../../parking_event_manager.h"

namespace parking
{

    /**
     * @brief 保存和查询 AVP 建图事件。
     *
     * 建图激活使用枚举保存激活来源和激活抑制原因，打开和打开抑制使用
     * 布尔事件标志，其余事件使用专用条件枚举保存。该类不负责判定条件、
     * 执行建图或驱动外部状态机。
     */
    class AvpMappingEventManager : public ParkingEventManager<AvpmActvType, AvpmActvIhbtType, AvpmGuidanceType,
                                                              AvpmGuidanceIhbtType, AvpmPauseType, AvpmSuccessType,
                                                              AvpmFailType, AvpmExitType>
    {
    protected:
        void LogEventChange(ParkingEventType event_type, int value) const noexcept override
        {
            const auto log = [](const auto &strmap, const char *event_name, auto event_value)
            {
                const auto it = strmap.find(event_value);
                if (it != strmap.end())
                    std::clog << "AvpMappingEventManager: " << event_name << " = " << it->second << std::endl;
            };
            switch (event_type)
            {
            case ParkingEventType::ACTV_1:
                log(avpm_actv_strmap, "ACTV", static_cast<AvpmActvType>(value));
                break;
            case ParkingEventType::ACTV_IHBT_2:
                log(avpm_actv_ihbt_strmap, "ACTV_IHBT", static_cast<AvpmActvIhbtType>(value));
                break;
            case ParkingEventType::GUIDANCE_3:
                log(avpm_guidance_strmap, "GUIDANCE", static_cast<AvpmGuidanceType>(value));
                break;
            case ParkingEventType::GUIDANCE_IHBT_4:
                log(avpm_guidance_ihbt_strmap, "GUIDANCE_IHBT", static_cast<AvpmGuidanceIhbtType>(value));
                break;
            case ParkingEventType::PAUSE_5:
                log(avpm_pause_strmap, "PAUSE", static_cast<AvpmPauseType>(value));
                break;
            case ParkingEventType::SUCCESS_6:
                log(avpm_success_strmap, "SUCCESS", static_cast<AvpmSuccessType>(value));
                break;
            case ParkingEventType::FAIL_7:
                log(avpm_fail_strmap, "FAIL", static_cast<AvpmFailType>(value));
                break;
            case ParkingEventType::EXIT_8:
                log(avpm_exit_strmap, "EXIT", static_cast<AvpmExitType>(value));
                break;
            case ParkingEventType::NONE_0:
            default:
                break;
            }
        }
    };
} // namespace parking
