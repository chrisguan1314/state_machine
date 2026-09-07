#pragma once

#include "../../../../enum.h"
#include "../../../state_machine_engine_base.h"
#include "apa_inputer.h"
#include "apa_outputer.h"
#include "apa_param.h"
#include "apa_switcher.h"

namespace parking
{
/**
 * @brief 组装并运行 APA 状态机的引擎。
 *
 * @details
 * 该引擎将 ApaParam、ApaInputer、ApaStateSwitcher 和 ApaOutputer 组合为
 * 完整的 APA 状态机。生命周期控制、后台调度线程及组件初始化顺序由
 * StateMachineEngineBase 提供。
 *
 * @note 调用 Init() 完成组件与线程初始化后，调用 Start() 启动状态机调度。
 */
class ApaStateMachineEngine final : public StateMachineEngineBase<ApaStateType, ApaParam, ApaInputer, ApaStateSwitcher, ApaOutputer>
{
public:
    /**
     * @brief 构造名称为 "Apa" 的 APA 状态机引擎。
     * @details 使用 StateMachineEngineBase 的默认调度频率。
     */
    ApaStateMachineEngine() : StateMachineEngineBase<ApaStateType, ApaParam, ApaInputer, ApaStateSwitcher, ApaOutputer>("Apa") {}
};
}