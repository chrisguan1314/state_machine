#pragma once
#include "apa_event_map.h"
#include "../../parking_event_manager.h"
#include "../../../../log_base.h"

namespace parking
{
/**
 * @brief 将通用停车事件名称格式化为可显示文本。
 * @param value 停车事件名称。
 * @return 对应的格式化文本。
 */
inline std::string EventFormator(const std::string &value)
{
    return Format(value, parking_event_strmap);
}
/**
 * @brief 保存和查询 APA 事件。
 *
 * @details
 * 该类以 APA 专用枚举实例化 ParkingEventManager，统一维护激活、激活抑制、
 * 控车激活、控车激活抑制、暂停、成功、失败和退出事件。事件变更时，
 * LogEventChange() 将具体枚举值转换为字符串并输出日志；查询接口则返回
 * 当前通用事件类别及其 APA 专用事件名称。
 */
class ApaEventManager : public ParkingEventManager<ApaActvType, ApaActvIhbtType, ApaGuidanceType,
                                         ApaGuidanceIhbtType, ApaPauseType, ApaSuccessType,
                                         ApaFailType, ApaExitType>
{
protected:
    /**
     * @brief 记录 APA 事件值的变化。
     * @param event_type 发生变化的通用停车事件类别。
     * @param value 对应 APA 事件枚举的底层整数值。
     * @details 将值转换为对应 APA 枚举后查询字符串映射；未找到映射时不输出日志。
     */
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
    /**
     * @brief 获取当前已设置的 APA 通用事件类别名称。
     * @return 由 parking_event_strmap 格式化的事件类别名称。
     */
    static std::string GetEventName() noexcept 
    {
        return parking_event_strmap.at(GetEventType());
    }

    /**
     * @brief 获取当前已设置的 APA 具体事件名称。
     * @return 当前事件类别对应的 APA 具体枚举名称；未设置任何事件时返回 "NONE"。
     */
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
