#pragma once

#include "../../enum.h"
#include "../../str_map.h"
#include "../../base/state_machine_engine_base.h"
#include "avp_cruising_param.h"
#include "avp_cruising_inputer.h"
#include "avp_cruising_switcher.h"
#include "avp_cruising_outputer.h"

namespace parking
{
class AvpCruisingStateMachineEngine : public StateMachineEngineBase<AvpCruisingStateType>
{
public:
    static std::unique_ptr<AvpCruisingStateMachineEngine>& GetInstance()
    {
        static std::unique_ptr<AvpCruisingStateMachineEngine> avp_sm_uptr_(new AvpCruisingStateMachineEngine);
        return avp_sm_uptr_;
    }
private: 
    AvpCruisingStateMachineEngine() : StateMachineEngineBase<AvpCruisingStateType>("AvpCruising", std::make_shared<AvpCruisingParam>(), std::make_shared<AvpCruisingInputer>(), std::make_shared<AvpCruisingStateSwitcher>(), std::make_shared<AvpCruisingOutputer>())
    {
        
    }
};
};
