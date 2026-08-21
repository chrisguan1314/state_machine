#pragma once

#include "../../../../enum.h"
#include "../../../../str_map.h"
#include "../../../state_machine_engine_base.h"
#include "avp_cruising_param.h"
#include "avp_cruising_inputer.h"
#include "avp_cruising_switcher.h"
#include "avp_cruising_outputer.h"

namespace parking
{
class AvpCruisingStateMachineEngine : public StateMachineEngineBase<AvpCruisingStateType, AvpCruisingParam, AvpCruisingInputer, AvpCruisingStateSwitcher, AvpCruisingOutputer>
{
public: 
    AvpCruisingStateMachineEngine() : StateMachineEngineBase<AvpCruisingStateType, AvpCruisingParam, AvpCruisingInputer, AvpCruisingStateSwitcher, AvpCruisingOutputer>("AvpCruising")
    {
        
    }
};
};
