#pragma once

#include "avp_cruising_event_map.h"
#include "../../parking_event_manager.h"

namespace parking
{

    /**
     * @brief 保存和查询 AVP 巡航事件。
     *
     * 巡航激活使用枚举保存激活来源和激活抑制原因，打开和打开抑制使用
     * 布尔事件标志，其余事件使用专用条件枚举保存。该类不负责判定条件、
     * 执行巡航或驱动外部状态机。
     */
    class AvpCruisingEventManager : public ParkingEventManager<AvpcActvType, AvpcActvIhbtType, AvpcGuidanceType,
                                                               AvpcGuidanceIhbtType, AvpcPauseType, AvpcSuccessType,
                                                               AvpcFailType, AvpcExitType>
    {
    public:
        static void LogEventChange(ParkingEventType event_type, int value) noexcept 
        {
            const auto log = [](const auto &strmap, const char *event_name, auto event_value)
            {
                const auto it = strmap.find(event_value);
                if (it != strmap.end())
                    std::clog << "AvpCruisingEventManager: " << event_name << " = " << it->second << std::endl;
            };
            switch (event_type)
            {
            case ParkingEventType::ACTV_1:
                log(avpc_actv_strmap, "ACTV", static_cast<AvpcActvType>(value));
                break;
            case ParkingEventType::ACTV_IHBT_2:
                log(avpc_actv_ihbt_strmap, "ACTV_IHBT", static_cast<AvpcActvIhbtType>(value));
                break;
            case ParkingEventType::GUIDANCE_3:
                log(avpc_guidance_strmap, "GUIDANCE", static_cast<AvpcGuidanceType>(value));
                break;
            case ParkingEventType::GUIDANCE_IHBT_4:
                log(avpc_guidance_ihbt_strmap, "GUIDANCE_IHBT", static_cast<AvpcGuidanceIhbtType>(value));
                break;
            case ParkingEventType::PAUSE_5:
                log(avpc_pause_strmap, "PAUSE", static_cast<AvpcPauseType>(value));
                break;
            case ParkingEventType::SUCCESS_6:
                log(avpc_success_strmap, "SUCCESS", static_cast<AvpcSuccessType>(value));
                break;
            case ParkingEventType::FAIL_7:
                log(avpc_fail_strmap, "FAIL", static_cast<AvpcFailType>(value));
                break;
            case ParkingEventType::EXIT_8:
                log(avpc_exit_strmap, "EXIT", static_cast<AvpcExitType>(value));
                break;
            case ParkingEventType::NONE_0:
            default:
                break;
            }
        }
    };

} // namespace parking
