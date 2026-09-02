#pragma once

#include "../../../../enum.h"
#include "../../../../str_map.h"
#include "../../../state_machine_engine_base.h"
#include "avp_mapping_param.h"
#include "avp_mapping_inputer.h"
#include "avp_mapping_switcher.h"
#include "avp_mapping_outputer.h"

/**
 * @brief AVP 建图状态机的聚合入口。
 *
 * 负责组合建图参数、输入、状态切换和输出动作模块。
 */
namespace parking
{
/**
 * @brief AVP 建图状态机引擎。
 */
class AvpMappingStateMachineEngine : public StateMachineEngineBase<AvpMappingStateType, AvpMappingParam, AvpMappingInputer, AvpMappingStateSwitcher, AvpMappingOutputer>
{
public: 
    /**
     * @brief 创建并配置 AVP 建图状态机。
     */
    AvpMappingStateMachineEngine() : StateMachineEngineBase<AvpMappingStateType, AvpMappingParam, AvpMappingInputer, AvpMappingStateSwitcher, AvpMappingOutputer>("AvpMapping")
    {
        
    }
};
};
