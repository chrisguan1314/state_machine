#pragma once

#include "apa_event.h"
#include "apa_param.h"
#include "../../../state_machine_inputer_base.h"

#include <iostream>

namespace parking
{
class ApaInputer : public StateMachineInputerBase
{
public:
    ApaInputer() : StateMachineInputerBase(std::make_shared<ApaEvent>()) {}

    void InitReaders() override
    {
        std::cout << "[StateMachine] Init ApaInputer Readers" << std::endl;
    }

    void UpdateEvent() override {}
};
}