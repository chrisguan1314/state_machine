#pragma once

#include "apo_event.h"
#include "apo_param.h"
#include "../../../state_machine_inputer_base.h"

#include <iostream>

namespace parking
{
    class ApoInputer : public StateMachineInputerBase<ApoParam>
    {
    public:
        ApoInputer() : StateMachineInputerBase<ApoParam>(std::make_shared<ApoEvent>()) {}

        void InitReaders() override
        {
            std::cout << "Init ApoInputer Readers" << std::endl;
        }

        void UpdateEvent(std::shared_ptr<ApoParam>) override {}
    };
}