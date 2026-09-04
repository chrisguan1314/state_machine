#pragma once

#include "../../../../enum.h"
#include "../../../state_machine_engine_base.h"
#include "apo_inputer.h"
#include "apo_outputer.h"
#include "apo_param.h"
#include "apo_switcher.h"

namespace parking
{
    class ApoStateMachineEngine
        : public StateMachineEngineBase<ApoStateType, ApoParam, ApoInputer, ApoStateSwitcher, ApoOutputer>
    {
    public:
        ApoStateMachineEngine()
            : StateMachineEngineBase<ApoStateType, ApoParam, ApoInputer, ApoStateSwitcher, ApoOutputer>("Apo") {}
    };
}