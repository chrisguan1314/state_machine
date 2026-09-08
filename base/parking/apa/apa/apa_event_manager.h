#pragma once
#include "../../parking_event_manager.h"
#include "../../../../log_base.h"

namespace parking
{
/**
 * @brief 将通用停车事件枚举名称转换为显示文本。
 * @param value 停车事件名称。
 * @return 对应的显示文本。
 */
inline std::string EventFormator(const std::string &value)
{
    return Format(value, parking_event_strmap);
}

/**
 * @brief 管理 APA 停车功能事件。
 *
 * 基于 ParkingEventManager 保存激活、激活抑制、控车激活、控车激活抑制、
 * 暂停、成功、失败和退出事件，并提供当前事件类别及具体事件名称的查询接口。
 */
class ApaEventManager : public ParkingEventManager
{
protected:
    /**
     * @brief 输出 APA 事件的变更日志。
     * @param event_type 发生变化的通用停车事件类别。
     * @param value 对应 APA 事件枚举的底层整数值。
     *
     * 将值转换为对应的 APA 枚举并查询字符串映射；没有匹配项时不输出日志。
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
            case ParkingEventType::ACTV_1: log(actv_strmap, "ACTV", static_cast<PrkgFuncActvType>(value)); break;
            case ParkingEventType::ACTV_IHBT_2: log(actv_ihbt_strmap, "ACTV_IHBT", static_cast<PrkgFuncActvIhbtType>(value)); break;
            case ParkingEventType::GUIDANCE_3: log(guidance_strmap, "GUIDANCE", static_cast<PrkgFuncGuidanceType>(value)); break;
            case ParkingEventType::GUIDANCE_IHBT_4: log(guidance_ihbt_strmap, "GUIDANCE_IHBT", static_cast<PrkgFuncGuidanceIhbtType>(value)); break;
            case ParkingEventType::PAUSE_5: log(pause_strmap, "PAUSE", static_cast<PrkgFuncPauseType>(value)); break;
            case ParkingEventType::SUCCESS_6: log(success_strmap, "SUCCESS", static_cast<PrkgFuncSuccessType>(value)); break;
            case ParkingEventType::FAIL_7: log(fail_strmap, "FAIL", static_cast<PrkgFuncFailType>(value)); break;
            case ParkingEventType::EXIT_8: log(exit_strmap, "EXIT", static_cast<PrkgFuncExitType>(value)); break;
            case ParkingEventType::NONE_0: default: break;
        }
    }
public:
    /**
    * @brief 获取当前事件的通用类别名称。
    * @return 由 parking_event_strmap 映射得到的类别名称。
     */
    static std::string GetEventName() noexcept 
    {
        return parking_event_strmap.at(GetEventType());
    }

    /**
        * @brief 获取当前事件的 APA 具体名称。
        *
        * 事件类别由基类按固定优先级确定；未设置任何事件时返回 "NONE"。
        *
        * @return 当前事件类别对应的具体枚举名称，或 "NONE"。
     */
    static std::string GetEventTypeName() noexcept
    {
        switch (GetEventType())
        {
            case ParkingEventType::ACTV_1: return actv_strmap.at(GetActv());
            case ParkingEventType::ACTV_IHBT_2: return actv_ihbt_strmap.at(GetActvInhibited());
            case ParkingEventType::GUIDANCE_3: return guidance_strmap.at(GetGuidance());
            case ParkingEventType::GUIDANCE_IHBT_4: return guidance_ihbt_strmap.at(GetGuidanceInhibited());
            case ParkingEventType::PAUSE_5: return pause_strmap.at(GetPause());
            case ParkingEventType::SUCCESS_6: return success_strmap.at(GetSuccess());
            case ParkingEventType::FAIL_7: return fail_strmap.at(GetFail());
            case ParkingEventType::EXIT_8: return exit_strmap.at(GetExit());
            case ParkingEventType::NONE_0:
            default: return "NONE";
        }
    }
};

}  // namespace parking
