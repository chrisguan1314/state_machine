#pragma once

#include "../enum.h"
#include "../str_map.h"
#include "../base/state_machine_base.h"
#include "avp_cruising_param.h"
#include "avp_cruising_inputer.h"
#include "avp_cruising_switcher.h"
#include "avp_cruising_outputer.h"

namespace avp_cruising
{
class AvpCruisingStateMachine : public StateMachineBase<AvpCruisingStateType>
{
public:
    static std::unique_ptr<AvpCruisingStateMachine>& GetInstance()
    {
        static std::unique_ptr<AvpCruisingStateMachine> avp_sm_uptr_(new AvpCruisingStateMachine);
        return avp_sm_uptr_;
    }
private: 
    AvpCruisingStateMachine() : StateMachineBase<AvpCruisingStateType>("AvpCruising", std::make_shared<AvpCruisingParam>(), std::make_shared<AvpCruisingInputer>(), std::make_shared<AvpCruisingStateSwitcher>(), std::make_shared<AvpCruisingOutputer>())
    {
        
    }
};
};
