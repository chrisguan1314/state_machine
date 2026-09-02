#pragma once

#include "apa_event.h"
#include "apa_param.h"
#include "../../../state_machine_inputer_base.h"

#include <iostream>

namespace parking
{
class ApaInputer : public StateMachineInputerBase<ApaParam>
{
public:
    ApaInputer() : StateMachineInputerBase<ApaParam>(std::make_shared<ApaEvent>()) {}

    void InitReaders() override
    {
        std::cout << "Init ApaInputer Readers" << std::endl;
    }

    void UpdateEvent(std::shared_ptr<ApaParam> param) override {}
};
}