#pragma once

#include "../../../state_machine_param_base.h"

#include <iostream>

namespace parking
{
/**
 * @brief 管理 APA 状态机使用的功能参数。
 *
 * @details
 * 该参数对象提供遥控泊车辅助（RPA）使能标志的全局读写接口。
 * ApaStateSwitcher 使用该标志决定能否从 PREPARED_4 切换至
 * RPA_PREPARED_5。
 *
 * @note rpa_enable_ 为进程内静态状态；调用 SetRpaEnable() 后会影响所有
 * ApaParam 实例及依赖该标志的状态转换判断。
 */
class ApaParam final : public StateMachineParamBase
{
public:
    /**
     * @brief 初始化 APA 参数模块。
     *
     * @details 当前实现输出初始化日志，参数的默认值由静态成员初始化提供。
     */
    void Init() override
    {
        std::cout << "[StateMachine] Init ApaParam" << std::endl;
    }

    /**
     * @brief 更新 APA 参数数据。
     *
     * @details 当前为空实现，尚未从外部参数源同步 RPA 使能状态或其他参数。
     */
    void UpdateParam() override {}

private:
    /**
     * @brief RPA 功能使能标志，默认关闭。
     */
    inline static bool rpa_enable_{false};
    
public:
    /**
     * @brief 获取 RPA 功能是否启用。
     * @return RPA 已启用时返回 true，否则返回 false。
     */
    static bool IsRpaEnable() noexcept
    {
        return rpa_enable_;
    }
    /**
     * @brief 设置 RPA 功能使能状态。
     * @param enable 为 true 时启用 RPA，为 false 时关闭 RPA。
     */
    static void SetRpaEnable(bool enable = false) noexcept
    {
        rpa_enable_ = enable;
    }
};
}