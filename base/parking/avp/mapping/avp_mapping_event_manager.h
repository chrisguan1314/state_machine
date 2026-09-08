#pragma once

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
    class AvpMappingEventManager : public ParkingEventManager
    {
    protected:
        void LogEventChange(ParkingEventType event_type, int value) noexcept override
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
