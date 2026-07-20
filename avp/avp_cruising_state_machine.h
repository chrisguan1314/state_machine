#pragma once

#include "../enum.h"
#include "../str_map.h"
#include "../state_machine_base.h"
#include "avp_cruising_param.h"
#include "avp_cruising_input.h"
#include "avp_cruising_switch.h"
#include "avp_cruising_output.h"

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
    AvpCruisingStateMachine() :  
    StateMachineBase<AvpCruisingStateType>("AvpCruising", std::make_shared<AvpCruisingParam>(), std::make_shared<AvpCruisingInput>(), std::make_shared<AvpCruisingStateSwitch>(), std::make_shared<AvpCruisingOutput>())
    {
        
    }
};
};
