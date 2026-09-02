#pragma once

#include "../../../../enum.h"
#include "../../../state_machine_engine_base.h"
#include "apa_inputer.h"
#include "apa_outputer.h"
#include "apa_param.h"
#include "apa_switcher.h"

namespace parking
{
class ApaStateMachineEngine : public StateMachineEngineBase<ApaStateType, ApaParam, ApaInputer, ApaStateSwitcher, ApaOutputer>
{
public:
    ApaStateMachineEngine() : StateMachineEngineBase<ApaStateType, ApaParam, ApaInputer, ApaStateSwitcher, ApaOutputer>("Apa") {}
};
}